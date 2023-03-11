#include "stdafx.hpp"

#include "ExceptionCodes.hpp"



void Handler(int Code)
{
	const char* szMessage;

	switch (Code)
	{

	case STRING_INIT_FAILURE:
	{
		szMessage = ".-. What happened?\nCode - STRING_INIT_FAILURE (0x0001)";
		break;
	}

	default:
	{
		szMessage = ".-. What happened?\nCode - UNKNOWN_EXCEPTION (0x0000)";
		break;
	}

	}

	MessageBoxA(nullptr, szMessage, "Yggdrasil", MB_OK);

	exit(-1);
}