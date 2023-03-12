#include "String.hpp"
#include "SLinkedList.hpp"



class PropositionRequest
{
private:
public:
	String				Request;
	String				ParsedRequest;
	SLinkedList<char>	Variables;

public:
	PropositionRequest(const char* szRequest);
};