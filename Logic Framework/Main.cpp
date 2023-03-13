#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"




int main()
{
	SLinkedList<ValueAssignment> Test;
	ValueAssignment A;
	A.bValue = true;
	A.cVariable = 'A';

	ValueAssignment B;
	B.bValue = false;
	B.cVariable = 'B';

	ValueAssignment c;
	c.bValue = true;
	c.cVariable = 'C';
	Test.Append(A);
	Test.Append(B);
	Test.Append(c);


	PropositionRequest Test2("(A|B)&!C");
	std::cout << Test2.Evaluate(Test) << '\n';
}