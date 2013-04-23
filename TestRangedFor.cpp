// TestRangedFor.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test C++11 "ranged for".
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Todo Turn this into a unit test.

//#define DbgOutput(Msg)  { std::cout << Msg << std::endl << std::flush; }
#define IfFail(Msg)     { if (!Pass) { std::cout << Msg << std::endl << std::flush; } }
#define Summary(Msg)    { std::cout << Msg << std::endl << std::flush; }

#include "TreeTest.hpp"

//////////////////////////////////////////////////////////////////////

static int TestForward(tTree &Tree, int *pSeq, tTraversalOrder Order, int &Tried)
    {
    DbgOutput("'Ranged for' for " << OrderStrings[Order]);

    int   ActualKey     = 0;
    int   Count         = 0;
    int   ExpectedKey   = 0;
    bool  Pass          = true;
    int   Run           = 0;

    ++Run;
    for (auto i: Tree)
        {
        if (Count >= Tree.Size())
            break;

        ActualKey   = i.first;
        ExpectedKey = pSeq[Count];
        Pass        = Pass && (ActualKey == ExpectedKey);
        IfFail("****Failed: TestRangedFor(" << OrderStrings[Order] << "); Count " << Count << ", i.first is " << ActualKey << "; expected " << ExpectedKey);
        ++Count;
        }

    Tried += Run;
    return (int) Pass;
    }                                   // TestForward()

//////////////////////////////////////////////////////////////////////

int TestRangedFor(tTree &Tree, tExpectedKeys &ExpectedKeys)
    {
    int Passed = 0;
    int Tried  = 0;

    Passed += TestForward(Tree, ExpectedKeys.pInOrder,  eInOrderSmall,  Tried);

    Tree.SetDefaultOrder(ePreOrderSmall);
    Passed += TestForward(Tree, ExpectedKeys.pPreOrder, ePreOrderSmall, Tried);

    Tree.SetDefaultOrder(eInOrderSmall);

    Summary("TestRangedFor: " << Tried << " tests run; " << Passed << " passed");
    return (Passed == Tried);
    }                                   // TestRangedFor()
