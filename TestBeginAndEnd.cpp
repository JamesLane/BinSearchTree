// TestBeginAndEnd.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test the tree begin() and end() functions, and iterator equality and dereference
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
    DbgOutput("Iterator begin(), end(), and equality for " << OrderStrings[Order]);

    int  ActualValue   = 0;
    int  Count         = 0;
    int  ExpectedValue = 0;
    bool Pass          = false;
    int  Run           = 0;

    tIter Begin  = Tree.begin(Order);
    tIter End    = Tree.end(  Order);
    tIter Uninit;

    ++Run;
    ActualValue   = Begin->first;
    ExpectedValue = pSeq[0];
    Pass          = (ActualValue == ExpectedValue);
    Count        += (int) Pass;
    IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", Begin->first is " << ActualValue << ", expected " << ExpectedValue);

    // cout << "    Begin  is "; Begin .Dump(); cout << endl << flush;
    // cout << "    End    is "; End   .Dump(); cout << endl << flush;
    // cout << "    Uninit is "; Uninit.Dump(); cout << endl << flush;

    ++Run; Pass = (Begin == Begin            ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", Begin != Begin"       );
    ++Run; Pass = (Begin == Tree.begin(Order)); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", Begin != Tree.begin()");
    ++Run; Pass = (Begin != Uninit           ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", Begin == Uninit"      );
    ++Run; Pass = (End   == End              ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", End != End"           );
    ++Run; Pass = (End   == Tree.end(Order)  ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", End != Tree.end()"    );
    ++Run; Pass = (End   != Uninit           ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", End == Uninit"        );
    ++Run; Pass = (Begin != End              ); Count += Pass; IfFail("****Failed: TestBeginAndEnd(" << OrderStrings[Order] << "); Count " << Count << ", Begin == End"         );

    Tried += Run;
    DbgOutput("    " << Run << " tests run, " << Count << " passed.");
    return Count;
    }                                   // Test()

//////////////////////////////////////////////////////////////////////

int TestBeginAndEnd(tTree &Tree, tExpectedKeys &ExpectedKeys)
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

    Summary("TestBeginAndEnd: " << Tried << " tests run; " << Passed << " passed");
    return (Passed == Tried);
    }                                   // TestBeginAndEnd()
