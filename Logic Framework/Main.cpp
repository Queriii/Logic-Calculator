#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"
#include "AvailableCommands.hpp"



#define MAX_REQUEST 0x100

enum Commands
{
    Help            = 0,
    Table           = 1,
    Tautology       = 2,
    Contradiction   = 3,
    Argument        = 4,
};

typedef struct CommandPair
{
    const char*     szCommand;
    int    uiArgs;
}CommandPair, * PCommandPair;
constexpr CommandPair RECOGNIZED_COMMANDS[] = { {"Yggdrasil.help", 0}, {"Yggdrasil.table ", 1}, {"Yggdrasil.tautology ", 1}, {"Yggdrasil.contradiction ", 1}, {"Yggdrasil.argument ", -2}};       //Commands with no args, don't have a trailing space. Negative indicates minimum required...

typedef struct RequestInfo
{
    int iCommandID;
    int iArgs;
}RequestInfo;

RequestInfo ValidateRequest(String Request)
{
    int     iCommandId = NULL;
    bool    bCommandValid = false;
    bool    bMinimumFlag = false;
    for (int i = 0; i < _countof(RECOGNIZED_COMMANDS); i++)
    {
        if (Request.Scan(RECOGNIZED_COMMANDS[i].szCommand) == 0)
        {
            iCommandId = i;
            if (RECOGNIZED_COMMANDS[i].uiArgs == 0)
            {
                bCommandValid = (Request.Length() == String::Strlen(RECOGNIZED_COMMANDS[i].szCommand));
                if (bCommandValid)
                {
                    return {iCommandId, 0};
                }
                else
                {
                    return { -1, 0 };
                }
            }
            else if (RECOGNIZED_COMMANDS[i].uiArgs < 0)
            {
                bMinimumFlag = true;
                bCommandValid = true;
            }
            else
            {
                bCommandValid = true;
            }

            break;
        }
    }
    if (!bCommandValid)
    {
        return { -1, 0 };
    }

    int     uiArgCount      = 0;
    size_t  ullIndexScan    = 0;
    for (;; uiArgCount++)
    {
        ullIndexScan = Request.ScanFrom(" ", ullIndexScan+1);
        if (ullIndexScan == SIZE_T_NEG)
        {
            break;
        }
    }
    if (bMinimumFlag)
    {
        if (uiArgCount < (RECOGNIZED_COMMANDS[iCommandId].uiArgs * -1))
        {
           
            return { -1, 0 };
        }
    }
    else
    {
        if (uiArgCount != RECOGNIZED_COMMANDS[iCommandId].uiArgs)
        {
            return { -1, 0 };
        }
    }

    return { iCommandId, uiArgCount };
}

void ServiceRequest(String Request, RequestInfo Info)
{
    SLinkedList<String> Args;
    size_t ullStart = 0;
    size_t ullEnd   = Request.Scan(" ");
    for (int i = 0; i < Info.iArgs; i++) 
    {
        if (i == Info.iArgs - 1) 
        {
            ullStart    = ullEnd;
            ullEnd      = Request.Length() - 1;
        }
        else
        {
            ullStart = ullEnd; 
            ullEnd   = Request.ScanFrom(" ", ullStart + 1); 
        }

        String Arg("");
        for (size_t j = ullStart + 1; j <= ullEnd; j++) 
        {
            if (!Arg.Append(Request.Get()[j])) 
            {
                throw REQUEST_HANDLING_FAILED; 
            }
        }

        Args.Append(Arg.Get()); 
    } 

    switch (Info.iCommandID)
    {

    case Commands::Help:
    {
        printf(AvailableCommands);
        break;
    }

    case Commands::Table:
    {
        PropositionRequest Request(Args.Get(0).Get());
        Request.GenerateTable();
        break;
    }

    case Commands::Tautology:
    {
        PropositionRequest Request(Args.Get(0).Get());
        if (Request.IsTautology())
        {
            printf("True\n\n");
        }
        else
        {
            printf("False\n\n");
        }
        break;
    }
    
    case Commands::Contradiction:
    {
        PropositionRequest Request(Args.Get(0).Get());
        if (Request.IsContradiction())
        {
            printf("True\n\n");
        }
        else
        {
            printf("False\n\n");
        }
        break;
    }

    case Commands::Argument:
    {
        String ConvertedArgument("");
        for (size_t i = 0; i < Args.Length(); i++)
        {
            if (i == Args.Length() - 1)
            {
                ConvertedArgument.Append("(");
                ConvertedArgument.Append(Args.Get(i).Get());
                ConvertedArgument.Append(")");
            }
            else
            {
                ConvertedArgument.Append("(");
                ConvertedArgument.Append(Args.Get(i).Get());

                if (i == Args.Length() - 2)
                {
                    ConvertedArgument.Append(")>");
                }
                else
                {
                    ConvertedArgument.Append(")&");
                }
            }
        }

        PropositionRequest Request(ConvertedArgument.Get());
        if (Request.IsTautology())
        {
            printf("Valid argument\n\n");
        }
        else
        {
            printf("Invalid argument\n\n");
        }

        break;
    }

    }
}

int main()
{
    char szInput[MAX_REQUEST]{};

    try
    {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdout == INVALID_HANDLE_VALUE)
        {
            throw STDOUT_HANDLE_REQUEST_FAILED;
        }

        for (;;)
        {
            printf("> "); 
            if (!fgets(szInput, MAX_REQUEST, stdin))
            {
                throw REQUEST_RECEIVAL_FAILED; 
            }
             
            size_t ullInputLength = String::Strlen(szInput); 
            if (ullInputLength == SIZE_T_NEG || ullInputLength == MAX_REQUEST - 1) 
            {
                throw REQUEST_MAX_LENGTH_EXCEEDED; 
            }

            String Input(szInput); 
            Input.RemoveLast();
            if (!Input.Length())
            {
                break;
            }

            RequestInfo Response = ValidateRequest(Input);
            if (Response.iCommandID == -1)
            {
                SetConsoleTextAttribute(hStdout, 4);
                system("CLS");
                printf("Invalid command");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    Sleep(700);
                }
                system("CLS");
                SetConsoleTextAttribute(hStdout, 7);
            }
            else
            {
                SetConsoleTextAttribute(hStdout, 2);
                ServiceRequest(Input, Response);
                SetConsoleTextAttribute(hStdout, 7);
            }

            ZeroMemory(szInput, MAX_REQUEST); 
        }
    }
    catch (int ExceptionCode)
    {
        Handler(ExceptionCode);
    }
}