// TestIterIncAndDec.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test iterator ++ and --.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Todo Turn this into a unit test.

//#define DbgOutput(Msg)  { std::cout << Msg << std::endl << std::flush; }
#define IfFail(Msg)     { if (!Pass) { std::cout << Msg << std::endl << std::flush; } }
#define Summary(Msg)    { std::cout << Msg << std::endl << std::flush; }

#include "TreeTest.hpp"

//////////////////////////////////////////////////////////////////////

static int Test(tTree &Tree, int *pSeq, tTraversalOrder Order, int &Tried)
    {
    DbgOutput("Iterator dereference for " << OrderStrings[Order]);

    int   ActualKey   = 0;
    int   Count       = 0;
    int   ExpectedKey = 0;
    tIter Iter;
    bool  Pass        = false;
    int   Run         = 0;

    ++Run;
    Iter        = Tree.begin(Order);
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[0];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Tree.begin() Actual " << ActualKey << ", Expected " << ExpectedKey);

    ++Run;
    ++Iter;
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[1];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Count " << Count << ", ++Iter Actual " << ActualKey << ", Expected " << ExpectedKey);

    ++Run;
    ++Iter;
    ++Iter;
    ++Iter;
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[4];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Count " << Count << ", ++(++(++Iter)) Actual " << ActualKey << ", Expected " << ExpectedKey);

    ++Run;
    Iter++;
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[5];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Count " << Count << ", Iter++ Actual " << ActualKey << ", Expected " << ExpectedKey);

    ++Run;
    --Iter;
    --Iter;
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[3];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Count " << Count << ", --(--Iter) Actual " << ActualKey << ", Expected " << ExpectedKey);

    ++Run;
    Iter--;
    ActualKey   = Iter->first;
    ExpectedKey = pSeq[2];
    Pass        = (ActualKey == ExpectedKey);
    Count      += (int) Pass;
    IfFail("****Failed: TestIterIncAndDec(" << OrderStrings[Order] << "); Count " << Count << ", Iter-- Actual " << ActualKey << ", Expected " << ExpectedKey);

    Tried += Run;
    DbgOutput("    " << Run << " tests run, " << Count << " passed.");
    return Count;
    }                                   // Test()

//////////////////////////////////////////////////////////////////////

int TestIterIncAndDec(tTree &Tree, tExpectedKeys &ExpectedKeys)
    {
    int Passed = 0;
    int Tried  = 0;

    Passed += Test(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstSmall, Tried);
    Passed += Test(Tree, ExpectedKeys.     pInOrder,      eInOrderSmall, Tried);
    Passed += Test(Tree, ExpectedKeys.   pPostOrder,    ePostOrderSmall, Tried);
    Passed += Test(Tree, ExpectedKeys.    pPreOrder,     ePreOrderSmall, Tried);

    Passed += Test(Tree, ExpectedKeys.pBreadthFirst,  eBreadthFirstFast, Tried);
    Passed += Test(Tree, ExpectedKeys.     pInOrder,       eInOrderFast, Tried);
    Passed += Test(Tree, ExpectedKeys.   pPostOrder,     ePostOrderFast, Tried);
    Passed += Test(Tree, ExpectedKeys.    pPreOrder,      ePreOrderFast, Tried);

    Passed += Test(Tree, ExpectedKeys.     pInOrder,           eDefault, Tried);

    Summary("TestIterIncAndDec: " << Tried << " tests run; " << Passed << " passed");
    return (Passed == Tried);
    }                                   // TestIterIncAndDec()
