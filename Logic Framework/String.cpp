#include "stdafx.hpp"

#include "String.hpp"



//Static
size_t String::StringLength(const char* szString)
{
	if (!szString)
	{
		return SIZE_T_NEG;
	}

	const char* szIncPtr = szString;
	for (; *szIncPtr != '\0'; szIncPtr++);

	return static_cast<size_t>(szIncPtr - szString);
}

bool String::StringCopy(char* szTarget, size_t cbTargetSize, const char* szBuffer)
{
	if (!szTarget || !cbTargetSize || !szBuffer)
	{
		return false;
	}

	size_t ullBufferLength = String::StringLength(szBuffer);
	if (ullBufferLength == SIZE_T_NEG || ullBufferLength >= cbTargetSize)
	{
		return false;
	}

	for (int i = 0; i < ullBufferLength; i++)
	{
		szTarget[i] = szBuffer[i];
	}
	szTarget[ullBufferLength] = '\0';

	return true;
}

bool String::StringAppend(char* szTarget, size_t cbTargetSize, const char* szBuffer)
{
	if (!szTarget || !cbTargetSize || !szBuffer)
	{
		return false;
	}

	size_t ullBufferLength = String::StringLength(szBuffer);
	size_t ullTargetLength = String::StringLength(szTarget);
	if (ullBufferLength == SIZE_T_NEG || (ullBufferLength + ullTargetLength) >= cbTargetSize)
	{
		return false;
	}

	return (String::StringCopy(szTarget + ullTargetLength, cbTargetSize - ullTargetLength, szBuffer));
}

bool String::StringAppend(char* szTarget, size_t cbTargetSize, char cBuffer)
{
	if (!szTarget || !cbTargetSize)
	{
		return false;
	}

	size_t ullTargetLength = String::StringLength(szTarget);
	if ((ullTargetLength + 1) >= cbTargetSize)
	{
		return false;
	}

	szTarget[ullTargetLength]		= cBuffer;
	szTarget[ullTargetLength + 1]	= '\0';

	return true;
}





//Nonstatic
String::String(const char* szString)
{
	if (!szString)
	{
		return;
	}

	size_t	ullStringLength = String::StringLength(szString);
	this->szString = new char[ullStringLength + 1] {};
	if (!szString)
	{
		return;
	}

	if (!String::StringCopy(this->szString, ullStringLength + 1, szString))
	{
		return;
	}

	this->ullLength = ullStringLength;
	this->cbBuffer = ullStringLength + 1;
}

String::~String()
{
	if (szString)
	{
		delete[] szString;
		szString = nullptr;
	}
}

const char* String::Get()
{
	return this->szString;
}

bool String::Paste(String* pString)
{
	if (!pString)
	{
		return false;
	}
	if (!pString->cbBuffer || !pString->szString)
	{
		return false;
	}

	char* szNewString = new char[pString->cbBuffer] {};
	if (!szNewString)
	{
		return false;
	}

	bool bError = false;
	__try
	{
		for (int i = 0; i < pString->ullLength; i++)
		{
			szNewString[i] = pString->szString[i];
		}
		szNewString[pString->ullLength] = '\0';

		if (this->szString)
		{
			delete[] this->szString;
		}

		this->szString	= szNewString;
		this->ullLength = String::StringLength(this->szString);
		this->cbBuffer	= this->ullLength + 1;
	}
	__finally
	{
		if (bError)
		{
			delete[] szNewString;
		}
	}

	return !bError;
}

bool String::Append(const char* szString)
{
	if (!szString)
	{
		return false;
	}

	size_t ullAppendeeLength = String::StringLength(szString);
	if (ullAppendeeLength == SIZE_T_NEG)
	{
		return false;
	}

	char* szNewString = new char[this->cbBuffer + ullAppendeeLength] {};
	if (!szNewString)
	{
		return false;
	}

	bool bError = false;
	__try
	{
		if (this->szString)
		{
			if (!String::StringCopy(szNewString, this->cbBuffer + ullAppendeeLength, this->szString))
			{
				bError = true;
				__leave;
			}
		}

		if (!String::StringAppend(szNewString, this->cbBuffer + ullAppendeeLength, szString))
		{
			bError = true;
			__leave;
		}

		delete[] this->szString;
		this->szString	= szNewString;
		this->ullLength = this->cbBuffer + ullAppendeeLength - 1;
		this->cbBuffer	= this->cbBuffer + ullAppendeeLength;
	}
	__finally
	{
		if (bError)
		{
			delete[] szNewString;
		}
	}

	return !bError;
}

bool String::Append(String* pString)
{
	if (!pString)
	{
		return false;
	}

	if (!pString->szString || !pString->ullLength)
	{
		return false;
	}

	return this->Append(pString->szString);
}

unsigned int String::ScanPattern(const char* szPattern, bool bCaseSensitive)
{
	if (!szPattern || !this->szString)
	{
		return UNSIGNED_INT_NEG;
	}

	size_t ullPatternLength = String::StringLength(szPattern);
	if (ullPatternLength == SIZE_T_NEG || !ullPatternLength)
	{
		return UNSIGNED_INT_NEG;
	}

	unsigned int uiPatternBeginIndex = UNSIGNED_INT_NEG;
	if (bCaseSensitive)
	{
		for (int i = 0, j = 0; i < this->ullLength; i++)
		{
			if (this->szString[i] == szPattern[j])
			{
				j++;
				if (j == ullPatternLength)
				{
					uiPatternBeginIndex = (i - (ullPatternLength - 1));
					break;
				}
			}
			else
			{
				j = 0;
			}
		}
	}
	else
	{
		for (int i = 0, j = 0; i < this->ullLength; i++)
		{
			char cCaseConvertedString	= szString[i];
			char cCaseConvertedPattern	= szPattern[j];
			if (cCaseConvertedString > 0x40 && cCaseConvertedString < 0x5B)
			{
				cCaseConvertedString += 0x20;
			}
			if (cCaseConvertedPattern > 0x40 && cCaseConvertedPattern < 0x5B)
			{
				cCaseConvertedPattern += 0x20;
			}

			if (cCaseConvertedString == cCaseConvertedPattern)
			{
				j++;
				if (j == ullPatternLength)
				{
					uiPatternBeginIndex = (i - (ullPatternLength - 1));
					break;
				}
			}
			else
			{
				j = 0;
			}
		}
	}
	
	return uiPatternBeginIndex;
}

unsigned int String::ScanPattern(String* pString, bool bCaseSensitive)
{
	if (!pString)
	{
		return UNSIGNED_INT_NEG;
	}

	return (this->ScanPattern(pString->szString, bCaseSensitive));
}

bool String::InitialCut(unsigned int uiIndex)
{
	if (!this->szString || uiIndex >= this->ullLength)
	{
		return false;
	}

	char* szNewString = new char[this->ullLength - uiIndex] {};
	if (!szNewString)
	{
		return false;
	}

	bool bError = false;
	__try
	{
		for (int j = 0, i = (uiIndex + 1); i < this->ullLength; j++, i++)
		{
			szNewString[j] = this->szString[i];
		}
		szNewString[this->ullLength - (uiIndex + 1)] = '\0';

		delete[] this->szString;
		this->szString	= szNewString;
		this->cbBuffer	= this->ullLength - uiIndex;
		this->ullLength = this->cbBuffer - 1;
	}
	__finally
	{
		if (bError)
		{
			delete[] szNewString;
		}
	}

	return !bError;
}

bool String::SequentialCut(unsigned int uiIndex)
{
	if (!this->szString || uiIndex >= this->ullLength)
	{
		return false;
	}

	char* szNewString = new char[uiIndex + 1] {};
	if (!szNewString)
	{
		return false;
	}

	bool bError = false;
	__try
	{
		for (int i = 0; i < uiIndex; i++)
		{
			szNewString[i] = this->szString[i];
		}
		szNewString[uiIndex] = '\0';

		delete[] this->szString;
		this->szString = szNewString;
		this->cbBuffer = uiIndex + 1;
		this->ullLength = uiIndex;
	}
	__finally
	{
		if (bError)
		{
			delete[] szNewString;
		}
	}

	return !bError;
}

bool String::SegmentCut(unsigned int uiStartIndex, unsigned int uiEndIndex)
{
	if (!this->szString || uiStartIndex >= this->ullLength || uiEndIndex >= this->ullLength)
	{
		return false;
	}

	String Temporary(this->szString);

	if (!Temporary.InitialCut(uiStartIndex))
	{
		return false;
	}
	if (!Temporary.SequentialCut(uiEndIndex - (uiStartIndex + 1)))
	{
		return false;
	}

	this->Paste(&Temporary);

	return true;
}





//Overloading
std::ostream& operator<<(std::ostream& OutputStream, const String& Obj)
{
	OutputStream << Obj.szString;
	return OutputStream;
}

String& String::operator+=(const char* szString)
{
	if (!szString)
	{
		return *this;
	}

	this->Append(szString);
	return *this;
}

char String::operator[](unsigned int uiIndex)
{
	if (uiIndex >= this->ullLength)
	{
		return NULL;
	}

	return (this->Get()[uiIndex]);
}