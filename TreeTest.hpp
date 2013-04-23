// TreeTest.hpp
// Debugging support for BinSearchTree.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.

// Todo Turn this into a complete unit test.

#ifndef TreeTest_hpp
#define TreeTest_hpp

#include <cassert>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <vector>

#include "BinSearchTree.hpp"

#ifndef DbgOutput
#define DbgOutput(Msg)
#endif

#ifndef PrintFail
#define PrintFail(Msg)
#endif

#ifndef Summary
#define Summary(Msg)
#endif

typedef tIterator     <int, int> tIter;
typedef tBinSearchNode<int, int> tNode;
typedef tBinSearchTree<int, int> tTree;

using namespace std;

extern int BreadthFirstKeys[];
extern int InOrderKeys     [];
extern int PostOrderKeys   [];
extern int PreOrderKeys    [];

//////////////////////////////////////////////////////////////////////

struct tExpectedKeys
    {
    int *pBreadthFirst;
    int *pInOrder;
    int *pPostOrder;
    int *pPreOrder;
    };

typedef tNode *(*tpfNext)(tTree &Tree, tNode *pCur);

//////////////////////////////////////////////////////////////////////
// Imports.

extern std::string OrderStrings[];

extern void TreeTest(std::vector<wstring> &cArgs);
extern bool MakeTree1( tTree &Tree);
extern bool MakeTree16(tTree &Tree);

extern int  TestBeginAndEnd(    tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestIterDeref(      tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestIterIncAndDec(  tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestNodeNextAndPrev(tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestOldStyleIter(   tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestRangedFor(      tTree &Tree, tExpectedKeys &ExpectedKeys);
extern int  TestTreeFind(       tTree &Tree);
extern int  TestTreeMaxAndMin(  tTree &Tree, tExpectedKeys &ExpectedKeys);

#endif                                  // #ifndef TreeTest_hpp
