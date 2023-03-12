#include "stdafx.hpp"

#include "PropositionRequest.hpp"
#include "ExceptionCodes.hpp"



bool IsValidSymbol(const char& cCharacter)
{
	if ((cCharacter >= 'A' && cCharacter <= 'Z') || cCharacter == '|' || cCharacter == '&' || cCharacter == '!' || cCharacter == '(' || cCharacter == ')')
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

PropositionRequest::PropositionRequest(const char* szRequest)
	try : Request(szRequest), Variables()
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
}
catch(int Code)
{
	Handler(Code);
}