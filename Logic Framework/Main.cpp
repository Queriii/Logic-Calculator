#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"

int main()
{
	PropositionRequest Test("(A|B)&C");
	std::cout << Test.PostfixRequest.Get() << '\n';
}