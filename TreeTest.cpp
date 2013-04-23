// TreeTest.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Todo Add tests on an empty tree, and on a one node tree.
// Todo Turn this into a real unit test.

#include "TreeTest.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

std::string OrderStrings[] =
    {
    "eDefault",
    "eBreadthFirstFast",
    "eBreadthFirstSmall",
    "eInOrderFast",
    "eInOrderSmall",
    "ePostOrderFast",
    "ePostOrderSmall",
    "ePreOrderFast",
    "ePreOrderSmall"
    };

int BreadthFirstKeysTree1[] = {17};
int      InOrderKeysTree1[] = {17};
int    PostOrderKeysTree1[] = {17};
int     PreOrderKeysTree1[] = {17};
tExpectedKeys Tree1Keys = { BreadthFirstKeysTree1, InOrderKeysTree1, PostOrderKeysTree1, PreOrderKeysTree1 };

int BreadthFirstKeysTree16[] = {100,  60, 130,  40,  80, 120, 150,  10,  50,  70,  90, 110, 140, 160,  30,  20};
int      InOrderKeysTree16[] = { 10,  20,  30,  40,  50,  60,  70,  80,  90, 100, 110, 120, 130, 140, 150, 160};
int    PostOrderKeysTree16[] = { 20,  30,  10,  50,  40,  70,  90,  80,  60, 110, 120, 140, 160, 150, 130, 100};
int     PreOrderKeysTree16[] = {100,  60,  40,  10,  30,  20,  50,  80,  70,  90, 130, 120, 110, 150, 140, 160};

tExpectedKeys Tree16Keys = { BreadthFirstKeysTree16, InOrderKeysTree16, PostOrderKeysTree16, PreOrderKeysTree16 };

void TreeTest(vector<wstring> &cArgs)
    {
    int TestsPassed = 0;
    tTree Tree0;                        // An empty tree.
    tTree Tree1;                        // A tree containing exactly one node.
    tTree Tree16;                       // A 16 node tree.

    // Create the test trees.
    TestsPassed += MakeTree1( Tree1);
    TestsPassed += MakeTree16(Tree16);

    // Search for a key.
    TestsPassed += TestTreeFind(Tree16);

    // Tree.Max() and Tree.Min().
    TestsPassed += TestTreeMaxAndMin(Tree16, Tree16Keys);

    // Tree.Next() and Tree.prev().
    TestsPassed += TestNodeNextAndPrev(Tree16, Tree16Keys);

    // begin(), end(), and iterator equality.
    TestsPassed += TestBeginAndEnd(Tree16, Tree16Keys);

    // Iterator dereference.
    TestsPassed += TestIterDeref(Tree16, Tree16Keys);

    // Iterator increment and decrement.
    TestsPassed += TestIterIncAndDec(Tree16, Tree16Keys);

    // Pre-C++11 style iterator sequences.
    TestsPassed += TestOldStyleIter(Tree16, Tree16Keys);

    // cbegin(), rbegin(), etc.
    // Todo.

    // C++11 "ranged for".
    TestsPassed += TestRangedFor(Tree16, Tree16Keys);

    // Remove()
    cout << "Tree.Remove." << endl << flush;
    cout << "    Tree.Remove( 40) returned " << Tree16.Remove( 40) << endl << flush;
    cout << "    Tree.Remove(110) returned " << Tree16.Remove(110) << endl << flush;
    Tree16.Dump();                      // Reminder: check the tree shape.

    // RemoveSubtree(), aka STL map<> clear();
    // Todo.

    // ~tBinSearchTree()
    // Todo.

    // Relationals other than std::less<>
    // Todo.

    }                                   // TreeTest()
