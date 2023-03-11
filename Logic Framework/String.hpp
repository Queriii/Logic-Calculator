#pragma once

#define SIZE_T_NEG			(size_t)(-1)
#define UNSIGNED_INT_NEG	(unsigned int)(-1)

class String		//Ascii 
{
private:
	static size_t	StringLength	(const char* szString);
	static bool		StringCopy		(char* szTarget, size_t cbTargetSize, const char* szBuffer);
	static bool		StringAppend	(char* szTarget, size_t cbTargetSize, const char* szBuffer);
	static bool		StringAppend	(char* szTarget, size_t cbTargetSize, char cBuffer);


private:
//public:
	size_t	ullLength	= SIZE_T_NEG;
	size_t	cbBuffer	= NULL;
	char*	szString	= nullptr;


public:
	String	(const char* szString);
	~String	();

	const char*		Get				();
	bool			Paste			(String* pString);

	bool			Append			(const char* szString);
	bool			Append			(String* pString);
	unsigned int	ScanPattern		(const char* szPattern, bool bCaseSensitive = true);
	unsigned int	ScanPattern		(String* pString, bool bCaseSensitive = true);
	bool			InitialCut		(unsigned int uiIndex);
	bool			SequentialCut	(unsigned int uiIndex);
	bool			SegmentCut		(unsigned int uiStartIndex, unsigned int uiEndIndex);


public:
	friend	std::ostream&	operator<<(std::ostream& pStream, const String& pObj);
			String&			operator+=(const char* szString);
			char			operator[](unsigned int uiIndex);
};