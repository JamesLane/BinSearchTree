// Entry.cpp
// Effective C++ main program.
// Copyright (C) 2009 by James Lane
// Copyright (C) 2009 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

#include <string>
#include <vector>

#include "Entry.hpp"
#include "TreeTest.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

// main() converts args to C++ Strings and then calls Entry().
int Entry(wstring &Arg0, std::vector<wstring> &cArgs)
    {
    TreeTest(cArgs);
    return 0;
    }                                   // main()
