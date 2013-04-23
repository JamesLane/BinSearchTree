// TestOldStyleIter.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test old-style iterators.
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
    DbgOutput("Old style forward iterator for " << OrderStrings[Order]);

    int    ActualKey   = 0;
    size_t Count       = 0;
    int    ExpectedKey = 0;
    bool   Pass        = true;
    int    Run         = 0;

    ++Run;
    for (tIter i = Tree.begin(Order), End = Tree.end(Order); (Count < Tree.size()) && (i != End); ++Count, ++i)
        {
        ActualKey   = i->first;
        ExpectedKey = pSeq[Count];
        Pass        = Pass && (ActualKey == ExpectedKey);
        IfFail("****Failed: TestOldStyleIter: TestForward(" << OrderStrings[Order] << "); Count " << Count << ", i->first is " << ActualKey << "; expected " << ExpectedKey);
        }

    Tried += Run;
    return (int) Pass;
    }                                   // TestForward()

//////////////////////////////////////////////////////////////////////

static int TestBackward(tTree &Tree, int *pSeq, tTraversalOrder Order, int &Tried)
    {
    DbgOutput("Old style backward iterator for " << OrderStrings[Order]);

    int    ActualKey   = 0;
    size_t Count       = 0;
    int    ExpectedKey = 0;
    bool   Pass        = true;
    int    Run         = 0;

    ++Run;
    for (tIter i = --Tree.end(Order), End = Tree.begin(Order); (Count < Tree.size()) && (i != End); ++Count, --i)
        {
        ActualKey   = i->first;
        ExpectedKey = pSeq[Tree.Size() - Count - 1];
        Pass        = Pass && (ActualKey == ExpectedKey);
        IfFail("****Failed: TestOldStyleIter: TestBackward(" << OrderStrings[Order] << "); Count " << Count << ", i->first is " << ActualKey << "; expected " << ExpectedKey);
        }

    Tried += Run;
    return (int) Pass;
    }                                   // TestBackward()

//////////////////////////////////////////////////////////////////////

int TestOldStyleIter(tTree &Tree, tExpectedKeys &ExpectedKeys)
    {
    int Passed = 0;
    int Tried  = 0;

    Passed += TestForward(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstSmall, Tried);
    Passed += TestForward(Tree, ExpectedKeys.     pInOrder,      eInOrderSmall, Tried);
    Passed += TestForward(Tree, ExpectedKeys.   pPostOrder,    ePostOrderSmall, Tried);
    Passed += TestForward(Tree, ExpectedKeys.    pPreOrder,     ePreOrderSmall, Tried);

    Passed += TestForward(Tree, ExpectedKeys.pBreadthFirst,  eBreadthFirstFast, Tried);
    Passed += TestForward(Tree, ExpectedKeys.     pInOrder,       eInOrderFast, Tried);
    Passed += TestForward(Tree, ExpectedKeys.   pPostOrder,     ePostOrderFast, Tried);
    Passed += TestForward(Tree, ExpectedKeys.    pPreOrder,      ePreOrderFast, Tried);

    Passed += TestForward(Tree, ExpectedKeys.     pInOrder,           eDefault, Tried);

    Passed += TestBackward(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstSmall, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.     pInOrder,      eInOrderSmall, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.   pPostOrder,    ePostOrderSmall, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.    pPreOrder,     ePreOrderSmall, Tried);

    Passed += TestBackward(Tree, ExpectedKeys.pBreadthFirst,  eBreadthFirstFast, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.     pInOrder,       eInOrderFast, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.   pPostOrder,     ePostOrderFast, Tried);
    Passed += TestBackward(Tree, ExpectedKeys.    pPreOrder,      ePreOrderFast, Tried);

    Passed += TestBackward(Tree, ExpectedKeys.     pInOrder,           eDefault, Tried);

    Summary("TestOldStyleIter: " << Tried << " tests run; " << Passed << " passed");
    return (Passed == Tried);
    }                                   // TestOldStyleIter()
