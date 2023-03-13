#include "stdafx.hpp"

#include "PropositionRequest.hpp"
#include "ExceptionCodes.hpp"



constexpr char PRECEDENCE_ARRAY[] = { '|', '&', '!'};       //Right indicates higher precedence, this is modifiable if so desired (except for negations)...

//Instantiation helpers
bool IsOperator(const char& cCharacter)
{
    for (int i = 0; i < _countof(PRECEDENCE_ARRAY); i++)
    {
        if (cCharacter == PRECEDENCE_ARRAY[i])
        {
            return true;
        }
    }

    return false;
}

bool IsValidSymbol(const char& cCharacter)
{
    if ((cCharacter >= 'A' && cCharacter <= 'Z') || cCharacter == '|' || cCharacter == '&' || cCharacter == '!' || cCharacter == '(' || cCharacter == ')' || cCharacter == '!')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ValidateParenthesis(const char* szRequest)
{
    if (!szRequest)
    {
        return false;
    }

    size_t ullRequestLength = String::Strlen(szRequest);
    if (ullRequestLength == SIZE_T_NEG)
    {
        return false;
    }

    SLinkedList<bool> ParenthesisCheck;
    for (size_t i = 0; i < ullRequestLength; i++)
    {
        if (szRequest[i] == '(')
        {
            ParenthesisCheck.Append(NULL);
        }
        else if (szRequest[i] == ')')
        {
            if (ParenthesisCheck.Length() == 0)
            {
                return false;
            }

            ParenthesisCheck.RemoveLast();
        }
    }

    return (ParenthesisCheck.Length() == 0);
}

bool IsPrecedenceEqualOrHigher(char cCurrent, char cCheck)
{
    for (int i = 0; i < _countof(PRECEDENCE_ARRAY); i++)
    {
        if (PRECEDENCE_ARRAY[i] == cCurrent)
        {
            return true;
        }
        else if (PRECEDENCE_ARRAY[i] == cCheck)
        {
            return false;
        }
    }
}

bool ConvertRequestToPostfix(const char* szInfixRequest, String* pPostfixBuffer)
{
    if (!szInfixRequest || !pPostfixBuffer)
    {
        return false;
    }
    if (pPostfixBuffer->Length())
    {
        return false;
    }

    size_t ullInfixRequestLength = String::Strlen(szInfixRequest);
    if (ullInfixRequestLength == SIZE_T_NEG)
    {
        return false;
    }

    SLinkedList<char> OperatorStack;
    for (size_t i = 0; i < ullInfixRequestLength; i++)
    {
        if (szInfixRequest[i] >= 'A' && szInfixRequest[i] <= 'Z')
        {
            if (!pPostfixBuffer->Append(szInfixRequest[i]))
            {
                return false;
            }
        }
        else
        {
            switch (szInfixRequest[i])
            {

            case '(':
            {
                if (!OperatorStack.Append('('))
                {
;                   return false;
                }
                break;
            }

            case ')':
            {
                char cRemovedOperator;
                for (;;)
                {
                    cRemovedOperator = OperatorStack.RemoveLast();
                    if (cRemovedOperator == NULL)
                    {
                        return false;
                    }

                    if (cRemovedOperator == '(')
                    {
                        break;
                    }

                    if (!pPostfixBuffer->Append(cRemovedOperator))
                    {
                        return false;
                    }
                }
                break;
            }

            default:
            {
                char cRemovedOperator;
                if (OperatorStack.Length())
                {
                    for (;;)
                    {
                        if (OperatorStack.Get(OperatorStack.Length() - 1) == '(')
                        {
                            break;
                        }

                        if (!IsPrecedenceEqualOrHigher(szInfixRequest[i], OperatorStack.Get(OperatorStack.Length() - 1)))
                        {
                            break;
                        }

                        cRemovedOperator = OperatorStack.RemoveLast();
                        if (cRemovedOperator == NULL)
                        {
                            break;
                        }

                        pPostfixBuffer->Append(cRemovedOperator);
                    }

                    OperatorStack.Append(szInfixRequest[i]);
                }
                else
                {
                    OperatorStack.Append(szInfixRequest[i]);
                }
                break;
            }

            }
        }
    }

    while (OperatorStack.Length())
    {
        pPostfixBuffer->Append(OperatorStack.RemoveLast());
    }
}



//Instantiation
PropositionRequest::PropositionRequest(const char* szRequest)
    try : InfixRequest(szRequest), Variables(), PostfixRequest("")
{
    size_t ullRequestLength = String::Strlen(szRequest);
    if (!ullRequestLength || ullRequestLength == SIZE_T_NEG)
    {
        throw PROPOSITION_REQUEST_INIT_FAILURE;
    }

    if (!ValidateParenthesis(szRequest))
    {
        throw PROPOSITION_REQUEST_INVALID_PARENTHESIS;
    }

    for (size_t i = 0; i < ullRequestLength; i++)
    {
        if (!IsValidSymbol(szRequest[i]))
        {
            throw PROPOSITION_REQUEST_INIT_FAILURE;
        }

        if (szRequest[i] >= 'A' && szRequest[i] <= 'Z')
        {
            if (!this->Variables.Lookup(szRequest[i]))
            {
                this->Variables.Append(szRequest[i]);
            }
        }
    }

    if (!ConvertRequestToPostfix(szRequest, &this->PostfixRequest))
    {
        throw PROPOSITION_REQUEST_CONVERSION_FAILURE;
    }

    SLinkedList<Node*>  NodeStack;
    const char*         szPostfixRequest = this->PostfixRequest.Get();
    for (size_t i = 0; i < this->PostfixRequest.Length(); i++)
    {
        if (IsOperator(szPostfixRequest[i]))
        {
            if (szPostfixRequest[i] == '!')
            {
                if (NodeStack.Length() < 1)
                {
                    throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
                }

                Node* pFirst = NodeStack.RemoveLast();
                Node* pCombined = new Node(szPostfixRequest[i], OPERATOR_TYPE, pFirst, nullptr);    //Negation nodes are always to left, right is always null.
                if (!NodeStack.Append(pCombined))
                {
                    throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
                }
            }
            else
            {
                if (NodeStack.Length() < 2)
                {
                    throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
                }

                Node* pFirst    = NodeStack.RemoveLast();
                Node* pSecond   = NodeStack.RemoveLast();
                Node* pCombined = new Node(szPostfixRequest[i], OPERATOR_TYPE, pSecond, pFirst);
                if (!NodeStack.Append(pCombined))
                {
                    throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
                }
            }
        }
        else
        {
            Node* pNewNode = new Node(szPostfixRequest[i], OPERAND_TYPE, nullptr, nullptr);
            if (!pNewNode)
            {
                throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
            }

            if (!NodeStack.Append(pNewNode))
            {
                throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
            }
        }
    }

    if (NodeStack.Length() != 1)
    {
        throw PROPOSITION_REQUEST_TREE_CREATION_FAILURE;
    }

    this->pRequestTree = NodeStack.RemoveLast();
}
catch(int Code)
{
    Handler(Code);
}

void PropositionRequest::Dealloc(Node* pNode)
{
    if (!pNode)
    {
        return;
    }
    else
    {
        Dealloc(pNode->pLeft);
        Dealloc(pNode->pRight);
        delete pNode;
    }
}
PropositionRequest::~PropositionRequest()
{
    Dealloc(this->pRequestTree);
}



//Utility
bool PropositionRequest::Eval(Node* pHead, SLinkedList<ValueAssignment>& TruthValues)
{
    if (!pHead)
    {
        throw PROPOSITION_INVALID_TRUTH_VALUES;
    }

    if (pHead->uiTypeFlag == OPERAND_TYPE)
    {
        int bReturnValue = -1;
        for (size_t i = 0; i < TruthValues.Length(); i++)
        {
            if (TruthValues.Get(i).cVariable == pHead->cSymbol)
            {
                bReturnValue = TruthValues.Get(i).bValue;
            }
        }

        if (bReturnValue == -1)
        {
            throw PROPOSITION_INVALID_TRUTH_VALUES;
        }

        return (static_cast<bool>(bReturnValue));
    }
    else
    {
        switch (pHead->cSymbol)
        {

        case '!':
        {
            bool bResult = Eval(pHead->pLeft, TruthValues);
            return !bResult;
        }

        case '&':
        {
            bool bResult1 = Eval(pHead->pLeft, TruthValues);
            bool bResult2 = Eval(pHead->pRight, TruthValues);
            return bResult1 && bResult2;
        }

        case '|':
        {
            bool bResult1 = Eval(pHead->pLeft, TruthValues);
            bool bResult2 = Eval(pHead->pRight, TruthValues);
            return bResult1 || bResult2;
        }

        default:
        {
            throw PROPOSITION_INVALID_TRUTH_VALUES;
        }

        }
    }
}

bool PropositionRequest::Evaluate(SLinkedList<ValueAssignment>& TruthValues)
{
    if (TruthValues.Length() != this->Variables.Length())
    {
        throw PROPOSITION_INVALID_TRUTH_VALUES;
    }

    return (this->Eval(this->pRequestTree, TruthValues));
}

void PropositionRequest::GenerateTable()
{
    int uiRows = 1;
    String Marker("");
    for (int i = 0; i < this->Variables.Length(); i++)
    {
        Marker.Append("---");
        if (i == this->Variables.Length() - 1)
        {
            Marker.Append('\n');
            printf("%c\n", this->Variables.Get(i));
        }
        else
        {
            printf("%c | ", this->Variables.Get(i));
        }
        uiRows *= 2;
    }
    uiRows -= 1;
    printf(Marker.Get());

    for (; uiRows >= 0; uiRows--)
    {
        SLinkedList<ValueAssignment> TruthValues;

        unsigned int uiRowCopy = uiRows;
        for (size_t i = 0; i < this->Variables.Length(); i++, uiRowCopy >>= 1)
        {
            TruthValues.Prepend({ this->Variables.Get(i), static_cast<bool>(uiRowCopy & 0b1)});
        }

        for (size_t i = 0; i < TruthValues.Length(); i++)
        {
            if (i == TruthValues.Length() - 1)
            {
                printf("%i --> ", TruthValues.Get(i).bValue);
            }
            else
            {
                printf("%i | ", TruthValues.Get(i).bValue);
            }
            
        }
        printf("%i\n", this->Evaluate(TruthValues));
    }
    printf("\n");
}