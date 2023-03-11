#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"

int main()
{
	String Test2("Helloas");
	SLinkedList<String> Test;
	Test.Append(Test2);

	Test2.RemoveFirst();

	std::cout << Test.Get(0).Get() << '\n';
}