// TestNodeNextAndPrev.cpp
// Temporary debugging support for BinSearchTree.
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

bool TestNodeNext(tTree &Tree, int *pSeq, tTraversalOrder Order)
    {
    DbgOutput("Tree.Next(" << OrderStrings[Order] << ")")
    size_t    Count   = 0;
    tPosition CurPos  = Tree.MinPos(Order);
    tNode    *pNode   = Tree.PtrFromPos(CurPos, Order);
    bool      Pass    = !!pNode;
    int       LastKey = -1;
    while (pNode)
        {
        int ActualKey   = pNode->KV.first;
        int ExpectedKey = pSeq[Count];
        Pass = Pass && (pNode->KV.first == ExpectedKey);
        IfFail("****Failed: TestNodeNext(" << OrderStrings[Order] << "); Count " << Count << ", Tree.NextPos(" << LastKey << ", " << OrderStrings[Order] << ") returned " << ActualKey << "; expected " << ExpectedKey);
        LastKey = ActualKey;
        CurPos  = Tree.NextPos(CurPos, Order);
        pNode   = Tree.PtrFromPos(CurPos, Order);
        ++Count;
        }
    return Pass;
    }                                   // TestNodeNext()

//////////////////////////////////////////////////////////////////////

bool TestNodePrev(tTree &Tree, int *pSeq, tTraversalOrder Order)
    {
    DbgOutput("Tree.Prev(" << OrderStrings[Order] << ")")
    size_t    Count   = 0;
    tPosition CurPos  = Tree.MaxPos(Order);
    tNode    *pNode   = Tree.PtrFromPos(CurPos, Order);
    bool      Pass    = !!pNode;
    int       LastKey = -1;
    while (pNode)
        {
        int ActualKey   = pNode->KV.first;
        int ExpectedKey = pSeq[Tree.size() - Count - 1];
        Pass = Pass && (pNode->KV.first == ExpectedKey);
        IfFail("****Failed: TestNodePrev(" << OrderStrings[Order] << "); Count " << Count << ", Tree.NextPos(" << LastKey << ", " << OrderStrings[Order] << ") returned " << ActualKey << "; expected " << ExpectedKey);
        LastKey = ActualKey;
        CurPos  = Tree.PrevPos(CurPos, Order);
        pNode   = Tree.PtrFromPos(CurPos, Order);
        ++Count;
        }
    return Pass;
    }                                   // TestNodePrev()

//////////////////////////////////////////////////////////////////////

int TestNodeNextAndPrev(tTree &Tree, tExpectedKeys &ExpectedKeys)
    {
    int Passed = 0;
    int Run    = 0;

    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstSmall);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pInOrder,           eInOrderSmall);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pPostOrder,       ePostOrderSmall);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pPreOrder,         ePreOrderSmall);

    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstFast);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pInOrder,           eInOrderFast);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pPostOrder,       ePostOrderFast);
    ++Run;  Passed += (int) TestNodeNext(Tree, ExpectedKeys.pPreOrder,         ePreOrderFast);

    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstSmall);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pInOrder,           eInOrderSmall);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pPostOrder,       ePostOrderSmall);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pPreOrder,         ePreOrderSmall);

    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pBreadthFirst, eBreadthFirstFast);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pInOrder,           eInOrderFast);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pPostOrder,       ePostOrderFast);
    ++Run;  Passed += (int) TestNodePrev(Tree, ExpectedKeys.pPreOrder,         ePreOrderFast);

    Summary("TestNodeNextAndPrev: " << Run << " tests run; " << Passed << " passed");
    return Passed;
    }
