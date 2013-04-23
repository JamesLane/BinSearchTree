// TestTreeFind.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test the Tree Find() function.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Todo Turn this into a unit test.

//#define DbgOutput(Msg)  { std::cout << Msg << std::endl << std::flush; }
#define IfFail(Msg)     { if (!Pass) { std::cout << Msg << std::endl << std::flush; } }
#define Summary(Msg)    { std::cout << Msg << std::endl << std::flush; }

#include "TreeTest.hpp"

//////////////////////////////////////////////////////////////////////

bool TestFind(tTree &Tree, int Key, int Value)
    {
    DbgOutput("TestTreeFind(" << Key << ", " << Value << ")");
    int *pFound = Tree.Find(Key);
    bool Pass = ((!pFound && (Value == -1)) || (pFound && (*pFound == Value)));
    IfFail("****Failed: TestTreeFind(" << Key << "); Tree.Find() returned " << pFound << ", *return is " << (pFound ? *pFound : INT_MAX));
    return Pass;
    }                                   // TestFind()

//////////////////////////////////////////////////////////////////////

int TestTreeFind(tTree &Tree)
    {
    int Passed = 0;
    int Run    = 0;

    ++Run;  Passed += (int) TestFind(Tree,  10,   -10);
    ++Run;  Passed += (int) TestFind(Tree,  20,   -20);
    ++Run;  Passed += (int) TestFind(Tree,  30,   -30);
    ++Run;  Passed += (int) TestFind(Tree,  40,   -40);
    ++Run;  Passed += (int) TestFind(Tree,  50,   -50);
    ++Run;  Passed += (int) TestFind(Tree,  60,   -60);
    ++Run;  Passed += (int) TestFind(Tree,  70,   -70);
    ++Run;  Passed += (int) TestFind(Tree,  80,   -80);
    ++Run;  Passed += (int) TestFind(Tree,  90,   -90);
    ++Run;  Passed += (int) TestFind(Tree, 100,  -100);
    ++Run;  Passed += (int) TestFind(Tree, 110,  -110);
    ++Run;  Passed += (int) TestFind(Tree, 120,  -120);
    ++Run;  Passed += (int) TestFind(Tree, 130,  -130);
    ++Run;  Passed += (int) TestFind(Tree, 140,  -140);
    ++Run;  Passed += (int) TestFind(Tree, 150,  -150);
    ++Run;  Passed += (int) TestFind(Tree, 160,  -160);

    ++Run;  Passed += (int) TestFind(Tree, 999,   -1);
    ++Run;  Passed += (int) TestFind(Tree,  -1,   -1);

    Summary("TestTreeFind: " << Run << " tests run; " << Passed << " passed");
    return Passed;
    }                                   // TestTreeFind()
