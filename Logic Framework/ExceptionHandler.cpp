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

    case PROPOSITION_REQUEST_CONVERSION_FAILURE:
    {
        szMessage = ".-. What happened?\nCode - PROPOSITION_REQUEST_CONVERSION_FAILURE (0x0005)";
        break;
    }

    case PROPOSITION_REQUEST_TREE_CREATION_FAILURE:
    {
        szMessage = ".-. What happened?\nCode - PROPOSITION_REQUEST_TREE_CREATION_FAILURE (0x0006)";
        break;
    }

    case REQUEST_RECEIVAL_FAILED:
    {
        szMessage = ".-. What happened?\nCode - REQUEST_RECEIVAL_FAILED (0x0007)";
        break;
    }

    case REQUEST_MAX_LENGTH_EXCEEDED:
    {
        szMessage = ".-. What happened?\nCode - REQUEST_MAX_LENGTH_EXCEEDED (0x0008)";
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