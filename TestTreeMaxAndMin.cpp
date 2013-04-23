// TestTreeMaxAndMin.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test the Tree Max() and Min() functions.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Todo Turn this into a unit test.

//#define DbgOutput(Msg)  { std::cout << Msg << std::endl << std::flush; }
#define IfFail(Msg)     { if (!Pass) { std::cout << Msg << std::endl << std::flush; } }
#define Summary(Msg)    { std::cout << Msg << std::endl << std::flush; }

#include "TreeTest.hpp"

//////////////////////////////////////////////////////////////////////

bool TestTreeMax(tTree &Tree, tTraversalOrder Order, int ExpectedKey)
    {
    DbgOutput("    Tree.Max(" << OrderStrings[Order] << ")");
    int ActualKey = INT_MAX;
    tNode *pMax = Tree.Max(Order);
    if (pMax)
        ActualKey = pMax->KV.first;
    bool Pass = (ActualKey == ExpectedKey);
    IfFail("****Failed: TestTreeMaxAndMin: TestTreeMax(" << OrderStrings[Order] << "); Tree.Max returned " << ActualKey << "; expected " << ExpectedKey);
    return Pass;
    }                                   // TestTestMax()

//////////////////////////////////////////////////////////////////////

bool TestTreeMin(tTree &Tree, tTraversalOrder Order, int ExpectedKey)
    {
    DbgOutput("    Tree.Min(" << OrderStrings[Order] << ")");
    int ActualKey = INT_MAX;
    tNode *pMin = Tree.Min(Order);
    if (pMin)
        ActualKey = pMin->KV.first;
    bool Pass = (ActualKey == ExpectedKey);
    IfFail("****Failed: TestTreeMaxAndMin: TestTreeMin(" << OrderStrings[Order] << "); Tree.Min returned " << ActualKey << "; expected " << ExpectedKey);
    return Pass;
    }                                   // TestTestMin()

//////////////////////////////////////////////////////////////////////

int TestTreeMaxAndMin(tTree &Tree, tExpectedKeys &ExpectedKeys)
    {
    int Passed = 0;
    int Run    = 0;

    ++Run;  Passed += (int) TestTreeMax(Tree,  eBreadthFirstFast, ExpectedKeys.pBreadthFirst[Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,       eInOrderFast, ExpectedKeys.pInOrder     [Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,     ePostOrderFast, ExpectedKeys.pPostOrder   [Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,      ePreOrderFast, ExpectedKeys.pPreOrder    [Tree.size() - 1]);

    ++Run;  Passed += (int) TestTreeMax(Tree, eBreadthFirstSmall, ExpectedKeys.pBreadthFirst[Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,      eInOrderSmall, ExpectedKeys.pInOrder     [Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,    ePostOrderSmall, ExpectedKeys.pPostOrder   [Tree.size() - 1]);
    ++Run;  Passed += (int) TestTreeMax(Tree,     ePreOrderSmall, ExpectedKeys.pPreOrder    [Tree.size() - 1]);

    ++Run;  Passed += (int) TestTreeMin(Tree,  eBreadthFirstFast, ExpectedKeys.pBreadthFirst[0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,       eInOrderFast, ExpectedKeys.pInOrder     [0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,     ePostOrderFast, ExpectedKeys.pPostOrder   [0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,      ePreOrderFast, ExpectedKeys.pPreOrder    [0]);

    ++Run;  Passed += (int) TestTreeMin(Tree, eBreadthFirstSmall, ExpectedKeys.pBreadthFirst[0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,      eInOrderSmall, ExpectedKeys.pInOrder     [0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,    ePostOrderSmall, ExpectedKeys.pPostOrder   [0]);
    ++Run;  Passed += (int) TestTreeMin(Tree,     ePreOrderSmall, ExpectedKeys.pPreOrder    [0]);

    Summary("TestTreeMaxAndMin: " << Run << " tests run; " << Passed << " passed");
    return Passed;
    }
