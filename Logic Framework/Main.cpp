#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"
#include "AvailableCommands.hpp"



#define MAX_REQUEST 0x100

enum Commands
{
    Help    = 0,
    Table   = 1,
};

typedef struct CommandPair
{
    const char*     szCommand;
    unsigned int    uiArgs;
}CommandPair, * PCommandPair;
constexpr CommandPair RECOGNIZED_COMMANDS[] = { {"Yggdrasil.help", 0}, {"Yggdrasil.table ", 1} };       //Commands with no args, don't have a trailing space...

int ValidateRequest(String Request)
{
    int     iCommandId      = NULL;
    bool    bCommandValid   = false;
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
                    return iCommandId;
                }
                else
                {
                    return -1;
                }
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
        return -1;
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
    if (uiArgCount != RECOGNIZED_COMMANDS[iCommandId].uiArgs)
    {
        return -1;
    }

    return iCommandId;
}

void ServiceRequest(String Request, int iCommandId)
{
    SLinkedList<String> Args;
    size_t ullStart = 0;
    size_t ullEnd   = Request.Scan(" ");
    for (int i = 0; i < RECOGNIZED_COMMANDS[iCommandId].uiArgs; i++) 
    {
        if (i == RECOGNIZED_COMMANDS[iCommandId].uiArgs - 1) 
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

    switch (iCommandId)
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

    }
}

int main()
{
    char szInput[MAX_REQUEST]{};

 /*   PropositionRequest Test("A|B&C");
    ValueAssignment A;
    A.bValue = 1;
    A.cVariable = 'A';
    ValueAssignment B;
    B.bValue = 0;
    B.cVariable = 'B';
    ValueAssignment C;
    C.bValue = 0;
    C.cVariable = 'C';

    SLinkedList<ValueAssignment> Test2;
    Test2.Append(A);
    Test2.Append(B);
    Test2.Append(C);
    std::cout << Test.Evaluate(Test2) << '\n';*/

  //  return 0;

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

            int iCommandId = ValidateRequest(Input);
            if (iCommandId == -1)
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
                ServiceRequest(Input, iCommandId);
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