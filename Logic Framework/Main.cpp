#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"

int main()
{
	PropositionRequest Test("(A|B)&!C");

	std::cout << Test.pRequestTree->cSymbol << '\n';

	std::cout << Test.pRequestTree->pLeft->cSymbol << '\n';
	std::cout << Test.pRequestTree->pRight->cSymbol << '\n';
	std::cout << Test.pRequestTree->pRight->pLeft->cSymbol << '\n';

	std::cout << Test.pRequestTree->pLeft->pLeft->cSymbol << '\n';
	std::cout << Test.pRequestTree->pLeft->pRight->cSymbol << '\n';
}