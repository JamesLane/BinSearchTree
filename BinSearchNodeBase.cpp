// BinSearchNodeBase.cpp
// Code related to the tBinSearchNodeBase class.
char *BinSearchNodeBase = "    BinSearchNodeBase.cpp v20130422    \n"
                          "    Copyright (C) 2013 by James Lane    \n"
                          "    Copyright (C) 2013 by Novelty Hill Software, Inc.    \n"
                          "    Contact: jlane at-symbol NoveltyHillSoftware period commercial    \n"
                          "    \n";

#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "BinSearchNodeBase.hpp"

//////////////////////////////////////////////////////////////////////
// Local support functions to get the first and last node with a subtree.
// Small (and slow) versions.
// These routines work relative to a specified node, not necessarily to the root of a Tree.
// Return nullptr if the subtree contains no nodes.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Breadth-first first and last node in a subtree.

struct tLastNodeAndDepth
    {
    size_t MaxDepth = 0;
    tBinSearchNodeBase *pLastNode = nullptr;
    };                                  // struct tLastNodeAndDepth

static void BfMaxHelper(tBinSearchNodeBase *pNode, size_t CurDepth, tLastNodeAndDepth *pMaxSoFar)
    {
    if (!pNode)
        return;

    if (CurDepth >= pMaxSoFar->MaxDepth)
        {
        pMaxSoFar->MaxDepth  = CurDepth;
        pMaxSoFar->pLastNode = pNode;
        }

    BfMaxHelper(pNode->pLeft,  CurDepth + 1, pMaxSoFar);
    BfMaxHelper(pNode->pRight, CurDepth + 1, pMaxSoFar);
    }                                   // BfMaxHelper()

static tBinSearchNodeBase *BreadthFirstMaxSmall(tBinSearchNodeBase *pNode)
    {
    tLastNodeAndDepth LastNodeAndDepth;

    BfMaxHelper(pNode, 0, &LastNodeAndDepth);
    return LastNodeAndDepth.pLastNode;
    }                                   // BreadthFirstMaxSmall(pNode)

static tBinSearchNodeBase *BreadthFirstMinSmall(tBinSearchNodeBase *pNode)
    { return pNode; }

//////////////////////////////////////////////////////////////////////
// In-order first and last node in a subtree.

static tBinSearchNodeBase *InOrderMaxSmall(tBinSearchNodeBase *pNode)
    {
    if (pNode)
        while (pNode->pRight)
            pNode = pNode->pRight;

    return pNode;
    }                                   // InOrderMaxSmall(pNode)

static tBinSearchNodeBase *InOrderMinSmall(tBinSearchNodeBase *pNode)
    {
    if (pNode)
        while (pNode->pLeft)
            pNode = pNode->pLeft;

    return pNode;
    }                                   // InOrderMinSmall(pNode)

//////////////////////////////////////////////////////////////////////
// Post-order first and last node in a subtree.

static tBinSearchNodeBase *PostOrderMaxSmall(tBinSearchNodeBase *pNode)
    { return pNode; }

static tBinSearchNodeBase *PostOrderMinSmall(tBinSearchNodeBase *pNode)
    {
    tBinSearchNodeBase *pLast;

    while (pNode)
        {
        pLast = pNode;

        if (pNode->pLeft)   pNode = pNode->pLeft;
        else                pNode = pNode->pRight;
        }

    return pLast;
    }                                   // PostOrderMinSmall(pNode)

//////////////////////////////////////////////////////////////////////
// Pre-order first and last node in a subtree.

static tBinSearchNodeBase *PreOrderMaxSmall(tBinSearchNodeBase *pNode)
    {
    tBinSearchNodeBase *pLast;

    while (pNode)
        {
        pLast = pNode;

        if (pNode->pRight)  pNode = pNode->pRight;
        else                pNode = pNode->pLeft;
        }

    return pLast;
    }                                   // PreOrderMaxSmall(pNode)

static tBinSearchNodeBase *PreOrderMinSmall(tBinSearchNodeBase *pNode)
    { return pNode; }

//////////////////////////////////////////////////////////////////////
// Exported functions to get the first and last node with a subtree.
// These functions are always relative to a specified node; they don't know about Trees.
//////////////////////////////////////////////////////////////////////

tBinSearchNodeBase *MaxSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order)
    {
    if      (Order == eBreadthFirstSmall)   return BreadthFirstMaxSmall(pNode);
    else if (Order ==      eInOrderSmall)   return      InOrderMaxSmall(pNode);
    else if (Order ==    ePostOrderSmall)   return    PostOrderMaxSmall(pNode);
    else if (Order ==     ePreOrderSmall)   return     PreOrderMaxSmall(pNode);
    else                                    assert(1);  // No pointer to a Tree, thus no fast sequences.

    return nullptr;                     // Keep the compiler happy.
    }                                   // MaxSmall(pNode, Order)

tBinSearchNodeBase *MinSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order)
    {
    if      (Order == eBreadthFirstSmall)   return BreadthFirstMinSmall(pNode);
    else if (Order ==      eInOrderSmall)   return      InOrderMinSmall(pNode);
    else if (Order ==    ePostOrderSmall)   return    PostOrderMinSmall(pNode);
    else if (Order ==     ePreOrderSmall)   return     PreOrderMinSmall(pNode);
    else                                    assert(1);  // No pointer to a Tree, thus no fast sequences.

    return nullptr;                     // Keep the compiler happy.
    }                                   // MinSmall(pNode, Order)

//////////////////////////////////////////////////////////////////////
// Local support functions to increment or decrement from one node within
//  a subtree to the next or previous node in the specific traversal order.
// Return nullptr when incrementing past the end of the sequence.
// Small (and slow) versions.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Breadth-first next and previous.
//////////////////////////////////////////////////////////////////////

// Given a pointer to a current node, return a pointer to the next node in the breadth-first sequence.
// O(1) data, O(N^2) time version
tBinSearchNodeBase *BreadthFirstNextSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur)
        return nullptr;                             // No "next" in an empty tree.

    if (!pCur->pUp)
        {                                           // Special case: starting at the root; go down once.
        if      (pCur->pLeft)   return pCur->pLeft;
        else if (pCur->pRight)  return pCur->pRight;
        else                    return nullptr;
        }

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;                               // Not starting at the root; always begin by going up once.
    int Depth = 0;
    bool IncrementedLevel = false;

    while (pCur)
        {
        if (pLast == pCur->pUp)
            {                                       // Going down.
            if      (!++Depth)      return pCur;    // Deep enough.
            pLast = pCur;
            if      (pCur->pLeft)   pCur = pCur->pLeft;
            else if (pCur->pRight)  pCur = pCur->pRight;
            else                    pCur = pCur->pUp;
            }                                       // if (pLast == pCur->pUp)
        else
            {                                       // Going up.
            --Depth;
            if (pLast == pCur->pRight)
                {                                   // Coming up from the right.
                if (pCur->pUp)
                    {                               // Not at the root.
                    pLast = pCur;
                    pCur = pCur->pUp;
                    }
                else
                    {                               // At the root
                    if (IncrementedLevel)           // Entire tree searched; no lower level found.
                        return nullptr;

                    pLast = nullptr;
                    IncrementedLevel = true;
                    Depth -= 2;                     // -1 to change level; -1 to go "down" from nullptr to root.
                    }                               // if (pCur->pUp) else
                }                                   // if (pLast == pCur->pRight)
            else
                {                                   // Coming up from the left.
                pLast = pCur;
                if (pCur->pRight)   pCur = pCur->pRight;
                else                pCur = pCur->pUp;
                }                                   // if (pLast == pCur->pRight) else
            }                                       // if (pLast == pCur->pUp) else
        }                                           // while (pCur)

    return nullptr;                     // Keep the compiler happy.
    }                                   // BreadthFirstNextSmall(pCur)

// Given a pointer to a current node, return a pointer to the previous node in the breadth-first sequence.
tBinSearchNodeBase *BreadthFirstPrevSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur || !pCur->pUp)
        return nullptr;                             // No "next" in an empty tree; or if already at the end.

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;
    int Depth = 0;
    bool DecrementedLevel = false;

    while (pCur)                                    // Until fail to find a higher level.
        {
        if (pLast == pCur->pUp)
            {                                       // Going down.
            if      (!++Depth)      return pCur;    // Deep enough.
            pLast = pCur;
            if      (pCur->pRight)  pCur = pCur->pRight;
            else if (pCur->pLeft)   pCur = pCur->pLeft;
            else                    pCur = pCur->pUp;
            }                                       // if (pLast == pCur->pUp)
        else
            {                                       // Going up.
            --Depth;
            if (pLast == pCur->pLeft)
                {                                   // Coming up from the Left.
                if (pCur->pUp)
                    {                               // Not at the root.
                    pLast = pCur;
                    pCur = pCur->pUp;
                    }
                else
                    {                               // At the root
                    if (DecrementedLevel)           // Entire tree searched; no higher level found.
                        return nullptr;

                    pLast = nullptr;
                    DecrementedLevel = true;        // Going "down" from nullptr to the root adjusts Depth.
                    }                               // if (pCur->pUp) else
                }                                   // if (pLast == pCur->pLeft)
            else
                {                                   // Coming up from the right.
                pLast = pCur;
                if (pCur->pLeft)    pCur = pCur->pLeft;
                else                pCur = pCur->pUp;
                }                                   // if (pLast == pCur->pLeft) else
            }                                       // if (pLast == pCur->pUp) else
        }                                           // while (pCur)

    return nullptr;                     // Keep the compiler happy.
    }                                   // BreadthFirstPrevSmall(pCur)

//////////////////////////////////////////////////////////////////////
// In-order next and previous.
//////////////////////////////////////////////////////////////////////

// Given a pointer to a current node, return a pointer to the next node in the in-order sequence.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *InOrderNextSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur)
        return nullptr;

    tBinSearchNodeBase *pLast = pCur;
    if (!pCur->pLeft && !pCur->pRight)
        pCur = pCur->pUp;

    while (pCur)
        {
        if (pLast == pCur->pLeft)
            return pCur;

        if (pCur->pRight && (pLast != pCur->pRight))
            return InOrderMinSmall(pCur->pRight);

        pLast = pCur;
        pCur  = pCur->pUp;
        }

    return pCur;
    }                                   // InOrderNextSmall(pCur)

// Given a pointer to a current node, return a pointer to the previous node in the in-order sequence.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *InOrderPrevSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur)
        return nullptr;

    tBinSearchNodeBase *pLast = pCur;
    if (!pCur->pLeft && !pCur->pRight)
        pCur = pCur->pUp;

    while (pCur)
        {
        if (pLast == pCur->pRight)
            return pCur;

        if (pCur->pLeft && (pLast != pCur->pLeft))
            return InOrderMaxSmall(pCur->pLeft);

        pLast = pCur;
        pCur  = pCur->pUp;
        }

    return pCur;
    }                                   // InOrderPrevSmall(pCur)

///////////////////////////////////////////////////////////////////////
// Post-order next and previous.
//////////////////////////////////////////////////////////////////////

// Given a pointer to a current node, return a pointer to the next node in the post-order sequence.
// Note that this is PreOrderPrevSmall() with pLeft and pRight swapped.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *PostOrderNextSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur)
        return nullptr;

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;

    if (pCur && pCur->pRight && (pLast == pCur->pLeft))
        return PostOrderMinSmall(pCur->pRight);

    return pCur;
    }                                   // PostOrderNextSmall(pCur)

// Given a pointer to a current node, return a pointer to the previous node in the post-order sequence.
// Note that this is PreOrderNextSmall() with pLeft and pRight swapped.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *PostOrderPrevSmall(tBinSearchNodeBase *pCur)
    {
    if      (!pCur)         return nullptr;
    if      (pCur->pRight)  return pCur->pRight;
    else if (pCur->pLeft)  return pCur->pLeft;

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;
    while (pCur)
        {
        if (pCur->pLeft && (pLast == pCur->pRight))
            return pCur->pLeft;

        pLast = pCur;
        pCur = pCur->pUp;
        }

    return pCur;
    }                                   // PostOrderPrevSmall(pCur)

//////////////////////////////////////////////////////////////////////
// Pre-order next and previous.
//////////////////////////////////////////////////////////////////////

// Given a pointer to a current node, return a pointer to the next node in the pre-order sequence.
// Note that this is PostOrderPrevSmall() with pLeft & pRight swapped.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *PreOrderNextSmall(tBinSearchNodeBase *pCur)
    {
    if      (!pCur)         return nullptr;
    if      (pCur->pLeft)   return pCur->pLeft;
    else if (pCur->pRight)  return pCur->pRight;

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;
    while (pCur)
        {
        if (pCur->pRight && (pLast == pCur->pLeft))
            return pCur->pRight;

        pLast = pCur;
        pCur = pCur->pUp;
        }

    return pCur;
    }                                   // PreOrderNextSmall(pCur)

// Given a pointer to a current node, return a pointer to the previous node in the pre-order sequence.
// Note that this is PostOrderNextSmall() with pLeft & pRight swapped.
// O(1) data, O(N log N) time.
tBinSearchNodeBase *PreOrderPrevSmall(tBinSearchNodeBase *pCur)
    {
    if (!pCur)
        return nullptr;

    tBinSearchNodeBase *pLast = pCur;
    pCur = pCur->pUp;
    if (pCur && pCur->pLeft && (pLast == pCur->pRight))
        return PreOrderMaxSmall(pCur->pLeft);

    return pCur;
    }                                   // PreOrderPrevSmall(pCur)

//////////////////////////////////////////////////////////////////////
// General small / slow next node and previous node.
//////////////////////////////////////////////////////////////////////

// Order must be one of the ...Small traversal orders.
// Return nullptr if pNode == nullptr.

tBinSearchNodeBase *NextNodeSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order)
    {
    if (pNode)
        {
        if      (Order == eBreadthFirstSmall)   return BreadthFirstNextSmall(pNode);
        else if (Order ==      eInOrderSmall)   return      InOrderNextSmall(pNode);
        else if (Order ==    ePostOrderSmall)   return    PostOrderNextSmall(pNode);
        else if (Order ==     ePreOrderSmall)   return     PreOrderNextSmall(pNode);
        else                                    assert(1);
        }

    return nullptr;
    }                                   // NextNodeSmall(pNode, Order)

tBinSearchNodeBase *PrevNodeSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order)
    {
    if (pNode)
        {
        if      (Order == eBreadthFirstSmall)   return BreadthFirstPrevSmall(pNode);
        else if (Order ==      eInOrderSmall)   return      InOrderPrevSmall(pNode);
        else if (Order ==    ePostOrderSmall)   return    PostOrderPrevSmall(pNode);
        else if (Order ==     ePreOrderSmall)   return     PreOrderPrevSmall(pNode);
        else                                    assert(1);
        }

    return nullptr;
    }                                   // PrevNodeSmall(pNode, Order)

//////////////////////////////////////////////////////////////////////
// Debugging support.
//////////////////////////////////////////////////////////////////////

// Making these non-member functions allows pNode to be == nullptr.

void DumpNodeBase(tBinSearchNodeBase *pNode)
    {
    std::cout << "tBinSearchNodeBase at " << pNode;
    if (pNode)
        {
        std::cout << "; pParent is "      << pNode->pUp
                  << ", pLeft is "        << pNode->pLeft
                  << ", pRight is "       << pNode->pRight;
        }
    }                                   // DumpNodeBase(pNode)

void DumpSubTreeBase(tBinSearchNodeBase *pNode, int Indent, char const *pPrefix)
    {
    int Len = (pPrefix ? strlen(pPrefix) : 0);
    std::cout << std::setw(Len + Indent)
              << (pPrefix ? pPrefix : "")
              << std::setw(4)
              << Indent
              << " "
              << std::flush;

    DumpNodeBase(pNode);
    std::cout << std::endl << std::flush;

    if (pNode)
        {
        DumpSubTreeBase(pNode->pLeft,  Indent + 1, "Left :");
        DumpSubTreeBase(pNode->pRight, Indent + 1, "Right:");
        }
    }                                   // DumpSubTreeBase(pNode, )
