// Main.cpp
// Copyright (C) 2009 by James Lane
// Copyright (C) 2009 by Novelty Hill Software, Inc.

#include <vector>
#include <string>
#include <stdlib.h>
#include <cstring>

#include "Main.hpp"
#include "Entry.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Convert the command line arguments, if any, from ASCII (or UTF-8) to
// wstrings, and then call the effective entry point at "Entry()".

int main(int nArgs, char **ppArgs)
    {
    wstring              Arg0;
    size_t               ArgLen;
    std::vector<wstring> cArgs;
    size_t               BufLen  = 1024;
    int                  RetVal  = 0;
    wchar_t             *pArgBuf = new wchar_t[BufLen];

    for (int i = 0; i < nArgs; ++i)
        {
        ArgLen = strlen(*ppArgs) + sizeof(wchar_t);
        if (ArgLen > BufLen)
            {
            delete pArgBuf;
            BufLen = ArgLen;
            pArgBuf = new wchar_t[BufLen + 1];
            }

        mbstowcs(pArgBuf, *ppArgs++, ArgLen);
        if (!i) { Arg0 = wstring(pArgBuf);  }
        else    { cArgs.push_back(pArgBuf); }
        }                               // for (int i = 0; i < nArgs; ++i)

    delete pArgBuf;
    RetVal = Entry(Arg0, cArgs);

    exit(RetVal);                       // Harder to exploit than "return".
    }                                   // main()
