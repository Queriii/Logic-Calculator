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

	case PROPOSITION_REQUEST_INIT_FAILURE:
	{
		szMessage = ".-. What happened?\nCode - PROPOSITION_REQUEST_INIT_FAILURE (0x0002)";
		break;
	}

	case PARSING_FAILURE:
	{
		szMessage = ".-. What happened?\nCode - PARSING_FAILURE (0x0003)";
		break;
	}

	case PROPOSITION_REQUEST_INVALID_PARENTHESIS:
	{
		szMessage = ".-. What happened?\nCode - PROPOSITION_REQUEST_INVALID_PARENTHESIS (0x0004)";
		break;
	}

	default:
	{
		szMessage = ".-. What happened?\nCode - UNKNOWN_EXCEPTION (0x0000)";
		break;
	}

	}

	MessageBoxA(nullptr, szMessage, "Yggdrasil", MB_OK | MB_TOPMOST);

	exit(-1);
}