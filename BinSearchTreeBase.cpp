// BinSearchTreeBase.cpp
// Code related to the tBinSearchTreeBase class.
char *BinSearchTreeBase = "    BinSearchTreeBase.cpp v20130422    \n"
                          "    Copyright (C) 2013 by James Lane    \n"
                          "    Copyright (C) 2013 by Novelty Hill Software, Inc.    \n"
                          "    Contact: jlane at-symbol NoveltyHillSoftware period commercial    \n"
                          "    \n";

#include <cassert>                      // Todo Improve error handling.

#include "BinSearchTreeBase.hpp"

//////////////////////////////////////////////////////////////////////
// Routines to create the sequences of nodes used by the fast iterators.
//////////////////////////////////////////////////////////////////////

void BreadthFirstSeq(tBinSearchTreeBase &Tree)
    {
    if (Tree.ppBreadthFirstSeq)
        return;                         // Nothing to do.

    tBinSearchNodeBase **ppArray = static_cast<tBinSearchNodeBase **>(calloc(Tree.size() + 1, sizeof(tBinSearchNodeBase *)));

    size_t CurIndex  = 0;
    size_t LastIndex = 0;
    ppArray[CurIndex] = Tree.pRoot;
    while (ppArray[CurIndex])
        {
        if (ppArray[CurIndex]->pLeft )    ppArray[++LastIndex] = ppArray[CurIndex]->pLeft;
        if (ppArray[CurIndex]->pRight)    ppArray[++LastIndex] = ppArray[CurIndex]->pRight;
        ++CurIndex;
        }

    Tree.ppBreadthFirstSeq = ppArray;
    }                                   // BreadthFirstSeq(Tree)

////////////////////////////////////////

void InOrderSeqHelper(tBinSearchNodeBase **ppArray, tBinSearchNodeBase *pNode, size_t &Index)
    {
    if (!pNode)
        return;

    InOrderSeqHelper(ppArray, pNode->pLeft,  Index);
    ppArray[Index++] = pNode;
    InOrderSeqHelper(ppArray, pNode->pRight, Index);
    }                                   // InOrderSeqHelper()

void InOrderSeq(tBinSearchTreeBase &Tree)
    {
    if (Tree.ppInOrderSeq)
        return;                         // Nothing to do.

    tBinSearchNodeBase **ppArray = static_cast<tBinSearchNodeBase **>(calloc(Tree.size() + 1, sizeof(tBinSearchNodeBase *)));

    size_t Index = 0;
    InOrderSeqHelper(ppArray, Tree.pRoot, Index);
    Tree.ppInOrderSeq = ppArray;
    }                                   // InOrderSeq(Tree)

////////////////////////////////////////

void PostOrderSeqHelper(tBinSearchNodeBase **ppArray, tBinSearchNodeBase *pNode, size_t &Index)
    {
    if (!pNode)
        return;

    PostOrderSeqHelper(ppArray, pNode->pLeft,  Index);
    PostOrderSeqHelper(ppArray, pNode->pRight, Index);
    ppArray[Index++] = pNode;
    }                                   // PostOrderSeqHelper()

void PostOrderSeq(tBinSearchTreeBase &Tree)
    {
    if (Tree.ppPostOrderSeq)
        return;                         // Nothing to do.

    tBinSearchNodeBase **ppArray = static_cast<tBinSearchNodeBase **>(calloc(Tree.size() + 1, sizeof(tBinSearchNodeBase *)));

    size_t Index = 0;
    PostOrderSeqHelper(ppArray, Tree.pRoot, Index);
    Tree.ppPostOrderSeq = ppArray;
    }                                   // PostOrderSeq(Tree)

////////////////////////////////////////

void PreOrderSeqHelper(tBinSearchNodeBase **ppArray, tBinSearchNodeBase *pNode, size_t &Index)
    {
    if (!pNode)
        return;

    ppArray[Index++] = pNode;
    PreOrderSeqHelper(ppArray, pNode->pLeft,  Index);
    PreOrderSeqHelper(ppArray, pNode->pRight, Index);
    }                                   // PreOrderSeqHelper()

void PreOrderSeq(tBinSearchTreeBase &Tree)
    {
    if (Tree.ppPreOrderSeq)
        return;                         // Nothing to do.

    tBinSearchNodeBase **ppArray = static_cast<tBinSearchNodeBase **>(calloc(Tree.size() + 1, sizeof(tBinSearchNodeBase *)));

    size_t Index = 0;
    PreOrderSeqHelper(ppArray, Tree.pRoot, Index);
    Tree.ppPreOrderSeq = ppArray;
    }                                   // PreOrderSeq(Tree)

//////////////////////////////////////////////////////////////////////
// First and last node in a Tree for a specified traversal order.
// Fast (large data) version.

inline tBinSearchNodeBase **GetSeq(tBinSearchTreeBase &Tree, tTraversalOrder Order)
    {
    if (Order == eDefault)
        Order = Tree.DefaultTraversalOrder;
    assert(Order != eDefault);

    tBinSearchNodeBase **ppFastSeq = nullptr;
    if      (Order == eBreadthFirstFast) { BreadthFirstSeq(Tree); ppFastSeq = Tree.ppBreadthFirstSeq; }
    else if (Order ==      eInOrderFast) {      InOrderSeq(Tree); ppFastSeq = Tree.     ppInOrderSeq; }
    else if (Order ==    ePostOrderFast) {    PostOrderSeq(Tree); ppFastSeq = Tree.   ppPostOrderSeq; }
    else if (Order ==     ePreOrderFast) {     PreOrderSeq(Tree); ppFastSeq = Tree.    ppPreOrderSeq; }

    assert(ppFastSeq);
    return ppFastSeq;
    }                                   // GetSeq(Tree, Order)

//////////////////////////////////////////////////////////////////////
// Return a pointer to a given index position within a specified traversal sequence.
// Fast (large data) version.

tBinSearchNodeBase *GetPtrFast(tBinSearchTreeBase &Tree, tTraversalOrder Order, size_t Index)
    {
    if (Index >= Tree.size())
        return nullptr;

    tBinSearchNodeBase **ppFastSeq = GetSeq(Tree, Order);
    assert(ppFastSeq);
    return ppFastSeq[Index];
    }                                   // GetPtrFast(Tree, )

//////////////////////////////////////////////////////////////////////
// Next and previous node in a specified traversal order.
// Fast (large data) version.

tBinSearchNodeBase *NextNodeFast(tBinSearchTreeBase &Tree, size_t &CurIndex, tTraversalOrder Order)
    {
    if (CurIndex >= Tree.size())
        return nullptr;

    tBinSearchNodeBase **ppFastSeq = GetSeq(Tree, Order);
    assert(ppFastSeq);
    return ppFastSeq[++CurIndex];
    }                                   // NextNodeFast(Tree, )

tBinSearchNodeBase *PrevNodeFast(tBinSearchTreeBase &Tree, size_t &CurIndex, tTraversalOrder Order)
    {
    if (!CurIndex)                  return nullptr;
    if ( CurIndex >= Tree.size())   CurIndex = Tree.size();

    tBinSearchNodeBase **ppFastSeq = GetSeq(Tree, Order);
    assert(ppFastSeq);
    return ppFastSeq[--CurIndex];
    }                                   // PrevNodeFast(Tree, )
