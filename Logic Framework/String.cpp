#include "stdafx.hpp"

#include "String.hpp"
#include "ExceptionCodes.hpp"



//Static
size_t String::Strlen(const char* szString)
{
	if (!szString)
	{
		return SIZE_T_NEG;
	}

	for (size_t ullLength = 0; ; ullLength++)
	{
		if (*(szString + ullLength) == '\0')
		{
			return ullLength;
		}
	}
}



//Instantiation
String::String(const char* szString)
{
	if (!szString)
	{
		throw STRING_INIT_FAILURE;
	}

	size_t ullLength = String::Strlen(szString);
	if (ullLength == SIZE_T_NEG)
	{
		throw STRING_INIT_FAILURE;
	}

	this->szString = new char[ullLength + 1];
	if (!this->szString)
	{
		throw STRING_INIT_FAILURE;
	}

	for (size_t i = 0; i < ullLength; i++)
	{
		this->szString[i] = szString[i];
	}
	this->szString[ullLength] = '\0';

	this->ullLength = ullLength;
}

String::String(String& Str)
{
	size_t ullLength	= Str.ullLength;
	this->szString		= new char[ullLength + 1] {};
	if (!this->szString)
	{
		throw STRING_INIT_FAILURE;
	}

	for (size_t i = 0; i < ullLength; i++)
	{
		this->szString[i] = Str.Get()[i];
	}
	this->szString[ullLength] = '\0';

	this->ullLength = ullLength;
}

String::~String()
{


	if (this->szString)
	{
		printf("String | Deconstructor.\n");
		delete[] this->szString;
		this->szString	= nullptr;
	}
}




//Utility
const char* String::Get()
{
	return this->szString;
}

size_t	String::Length()
{
	return this->ullLength;
}

size_t String::Scan(const char* szPattern)
{
	if (!szPattern)
	{
		return SIZE_T_NEG;
	}

	for (size_t i = 0, j = 0; i < this->ullLength; i++)
	{
		if (this->szString[i] == szPattern[j])
		{	
			j++;
			if (j == String::Strlen(szPattern))
			{
				return (i + 1) - String::Strlen(szPattern);
			}
		}
		else
		{
			j = 0;
		}
	}
	
	return SIZE_T_NEG;
}

bool String::Insert(size_t ullIndex, const char* szInsertion)
{
	if (!szInsertion || ullIndex > this->ullLength)
	{
		return false;
	}

	size_t ullInsertionLength = String::Strlen(szInsertion);
	if (ullInsertionLength == SIZE_T_NEG)
	{
		return false;
	}

	size_t ullNewSize = ullInsertionLength + this->ullLength + 1;
	char* szNew			= new char[ullNewSize] {};
	if (!szNew)
	{
		return false;
	}

	for (size_t i = ullIndex, j = 0; j < ullInsertionLength; i++, j++)
	{
		szNew[i] = szInsertion[j];
	}
	for (size_t i = 0, j = 0; i < (ullNewSize - 1); i++)
	{
		if (szNew[i] == NULL)
		{
			szNew[i] = this->szString[j];
			j++;
		}
	}
	szNew[ullNewSize - 1] = '\0';

	delete[] this->szString;
	this->ullLength = ullNewSize - 1;
	this->szString	= szNew;

	return true;
}

bool String::Append(const char* szAppension)
{
	return (this->Insert(this->ullLength, szAppension));
}

bool String::Prepend(const char* szPrepension)
{
	return (this->Insert(0, szPrepension));
}

bool String::Cut(size_t ullBeginIndex, size_t ullEndIndex)
{
	if ((ullBeginIndex > ullEndIndex) || ullEndIndex >= this->ullLength)
	{
		return false;
	}

	size_t ullNewSize = this->ullLength - (ullEndIndex - ullBeginIndex);
	char* szNew			= new char[ullNewSize] {};
	if (!szNew)
	{
		return false;
	}

	for (size_t i = 0, j = 0; i < this->ullLength; i++)
	{
		if (!(i >= ullBeginIndex && i <= ullEndIndex))
		{
			szNew[j] = this->szString[i];		//Ignore overrun warning...
			j++;
		}
	}
	szNew[ullNewSize - 1] = '\0';

	delete[] this->szString;

	this->ullLength = ullNewSize - 1;
	this->szString	= szNew;

	return true;
}

bool String::RemoveFirst()
{
	return (this->Cut(0, 0));
}

bool String::RemoveLast()
{
	return (this->Cut(this->ullLength - 1, this->ullLength - 1));
}