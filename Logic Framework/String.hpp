#pragma once

#define SIZE_T_NEG (size_t)(-1)

class String
{
private:
	size_t	ullLength;
	char*	szString;


	//Statics
public:
	static size_t Strlen(const char* szString);

	
public:
	//Instantiation
	String	(const char* szString);
	String	(String& Str);
	~String	();


	//Utility
	const char* Get			();
	size_t		Length		();
	size_t		Scan		(const char* szPattern);
	size_t		ScanFrom	(const char* szPattern, size_t ullStartIndex);

	bool		Insert		(size_t ullIndex, const char* szInsertion);
	bool		Insert		(size_t ullIndex, char cInsertion);
	bool		Append		(const char* szAppension);
	bool		Append		(char cAppension);
	bool		Prepend		(const char* szPrepension);
	bool		Prepend		(char cPrepension);

	bool		Cut			(size_t ullBeginIndex, size_t ullEndIndex);
	bool		RemoveFirst	();
	bool		RemoveLast	();


	//Overloading
	/*void operator=(const String& Str)
	{
		char* szCopy = new char[Str.ullLength + 1];
		for (size_t i = 0; i < Str.ullLength; i++)
		{
			szCopy[i] = Str.szString[i];
		}
		szCopy[Str.ullLength] = '\0';

		this->szString	= szCopy;
		this->ullLength = Str.ullLength;
	}*/
};