#include "stdafx.hpp"

#include "Logic.hpp"
#include "ExceptionCodes.hpp"




#define MAX_REQUEST 0x100

int main()
{
    char szInput[MAX_REQUEST]{};

    try
    {
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

            ZeroMemory(szInput, MAX_REQUEST); 
        }
    }
    catch (int ExceptionCode)
    {
        Handler(ExceptionCode);
    }
}