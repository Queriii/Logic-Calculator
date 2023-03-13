#include "String.hpp"
#include "SLinkedList.hpp"
#include "ValueAssignment.hpp"



#define OPERAND_TYPE    0x1000
#define OPERATOR_TYPE   0x2000
#define UNDEFINED_TYPE  0x3000

class PropositionRequest
{
private:
    class Node
    {
    public:
        char            cSymbol;
        unsigned int    uiTypeFlag;

        Node* pLeft;
        Node* pRight;

        Node()
        {
            this->cSymbol       = NULL;
            this->uiTypeFlag    = UNDEFINED_TYPE;
            this->pLeft         = this->pRight = nullptr;
        }
        Node(char cSymbol, unsigned int uiTypeFlag, Node* pLeft, Node* pRight)
        {
            this->cSymbol       = cSymbol;
            this->uiTypeFlag    = uiTypeFlag;
            this->pLeft         = pLeft;
            this->pRight        = pRight;
        }
    };

    void Dealloc(Node* pNode);      //For use inside destructor only...
    bool Eval   (Node* pHead, SLinkedList<ValueAssignment>& TruthValues);

public:
    String              InfixRequest;
    String              PostfixRequest;
    Node*               pRequestTree;
    SLinkedList<char>   Variables;

public:
    //Instantiation
    PropositionRequest  (const char* szRequest);
    ~PropositionRequest ();


    //Utility
    bool Evaluate       (SLinkedList<ValueAssignment>& TruthValues);
};