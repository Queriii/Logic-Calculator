#include "String.hpp"
#include "SLinkedList.hpp"



class PropositionRequest
{
private:
public:
	String				InfixRequest;
	String				PostfixRequest;
	SLinkedList<char>	Variables;

public:
	PropositionRequest(const char* szRequest);
};