// BinSearchTreeBase.hpp
// Non-template class defining the basic structure and code of a binary tree.
// Making this a non-template class to reduce template code bloat.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-symbol NoveltyHillSoftware period commercial

#ifndef BinSearchTreeBase_hpp
#define BinSearchTreeBase_hpp

#include <cstdlib>

#include "BinSearchNode.hpp"

//////////////////////////////////////////////////////////////////////
// The root of a binary search tree.
//////////////////////////////////////////////////////////////////////

// A "pointer" to a single node.
union tPosition
    {
    size_t Index = (size_t) -1;         // Used for fast  traversal orders.
    tBinSearchNodeBase *pCur;           // Used for small traversal orders.
    };

class tBinSearchTreeBase;
tBinSearchNodeBase *GetPtrFast(  tBinSearchTreeBase &Tree, tTraversalOrder Order, size_t Index);
tBinSearchNodeBase *NextNodeFast(tBinSearchTreeBase &Tree, size_t &CurIndex, tTraversalOrder Order = eDefault);
tBinSearchNodeBase *PrevNodeFast(tBinSearchTreeBase &Tree, size_t &CurIndex, tTraversalOrder Order = eDefault);

class tBinSearchTreeBase
    {
  public:

    tBinSearchTreeBase()                                { }
    // tBinSearchTreeBase(tBinSearchTreeBase const &Right) { }     // Todo (copy constructor)

    virtual ~tBinSearchTreeBase()                       { RemoveSubtreeBase(pRoot); }

    void   Dump()                                       { DumpSubTreeBase(pRoot, 0, "Root :"); }
    bool   Empty()                                      { return !pRoot;    }
    void   SetDefaultOrder(tTraversalOrder Order)       { DefaultTraversalOrder = Order; }  // Allow C++11 "ranged for" with all traversals.
    size_t Size()                                       { return NodeCount; }

    // void   operator= (tBinSearchTreeBase const &Right)  { }     // Todo (copy assignment)

    // Compatibility with STL map<>.
    void   clear()  { RemoveSubtreeBase(pRoot); }
    bool   empty()  { return !pRoot;    }
    size_t size()   { return NodeCount; }

    ////////// tBinSearchTreeBase::PtrFromPos()
    // Return a pointer corresponding to a position in an iteration sequence.

    tBinSearchNodeBase *PtrFromPosBase(tPosition Pos, tTraversalOrder Order)
        {
        if (IsSmallOrder(Order))
            return Pos.pCur;
        return GetPtrFast(*this, Order, Pos.Index);
        }                               // PtrFromPosBase()

    ////////// tBinSearchTreeBase::InvalidateCache()
    // Invalidate the cached values for Max() and Min() and any cached fast sequences.

    void InvalidateCache()
        {
        pBreadthFirstFirst = pBreadthFirstLast = nullptr;
             pInOrderFirst =      pInOrderLast = nullptr;
           pPostOrderFirst =    pPostOrderLast = nullptr;
            pPreOrderFirst =     pPreOrderLast = nullptr;

        if (ppBreadthFirstSeq)  { free(ppBreadthFirstSeq); ppBreadthFirstSeq = nullptr; }
        if (     ppInOrderSeq)  { free(     ppInOrderSeq);      ppInOrderSeq = nullptr; }
        if (   ppPostOrderSeq)  { free(   ppPostOrderSeq);    ppPostOrderSeq = nullptr; }
        if (    ppPreOrderSeq)  { free(    ppPreOrderSeq);     ppPreOrderSeq = nullptr; }
        }                               // InvalidateCache()

    ////////// tBinSearchTreeBase::GetEnd()
    // Return a tPosition representing end().

    tPosition GetEnd(tTraversalOrder Order)
        {
        if (Order == eDefault)  Order = DefaultTraversalOrder;
        if (Order == eDefault)  Order = eInOrderSmall;

        tPosition Pos;
        if (IsSmallOrder(Order))    Pos.pCur = nullptr;
        else                        Pos.Index = Size();

        return Pos;
        }                               // GetEnd()

    ////////// tBinSearchTreeBase::GetMaxSmall() and tBinSearchTreeBase::GetMinSmall()
    // Return a cached value, or get a new value.

    tBinSearchNodeBase *GetMaxSmall(tTraversalOrder Order)
        {
        if      (Order == eBreadthFirstSmall)   { if (!pBreadthFirstLast)   { pBreadthFirstLast = MaxSmall(pRoot, Order); } return pBreadthFirstLast;   }
        else if (Order ==      eInOrderSmall)   { if (!     pInOrderLast)   {      pInOrderLast = MaxSmall(pRoot, Order); } return      pInOrderLast;   }
        else if (Order ==    ePostOrderSmall)   { if (!   pPostOrderLast)   {    pPostOrderLast = MaxSmall(pRoot, Order); } return    pPostOrderLast;   }
        else if (Order ==     ePreOrderSmall)   { if (!    pPreOrderLast)   {     pPreOrderLast = MaxSmall(pRoot, Order); } return     pPreOrderLast;   }
        else assert(1);

        return nullptr;                 // Keep the compiler happy.
        }                               // GetMaxSmall()

    tBinSearchNodeBase *GetMinSmall(tTraversalOrder Order)
        {
        if      (Order == eBreadthFirstSmall)   { if (!pBreadthFirstFirst)  { pBreadthFirstFirst = MinSmall(pRoot, Order); } return pBreadthFirstFirst; }
        else if (Order ==      eInOrderSmall)   { if (!     pInOrderFirst)  {      pInOrderFirst = MinSmall(pRoot, Order); } return      pInOrderFirst; }
        else if (Order ==    ePostOrderSmall)   { if (!   pPostOrderFirst)  {    pPostOrderFirst = MinSmall(pRoot, Order); } return    pPostOrderFirst; }
        else if (Order ==     ePreOrderSmall)   { if (!    pPreOrderFirst)  {     pPreOrderFirst = MinSmall(pRoot, Order); } return     pPreOrderFirst; }
        else assert(1);

        return nullptr;                 // Keep the compiler happy.
        }                               // GetMinSmall()

    ////////// tBinSearchTreeBase::MaxPosBase() and tBinSearchTreeBase::MinPosBase()
    // Return a tPosition representing the last / first node in the tree, by traversal type.
    // The last position is a pointer to the actual last node, which is one before end().

    tPosition MaxPos(tTraversalOrder Order = eDefault)
        {
        if (Order == eDefault)  Order = DefaultTraversalOrder;
        if (Order == eDefault)  Order = eInOrderSmall;

        tPosition Pos;
        if (IsSmallOrder(Order))    Pos.pCur  = GetMaxSmall(Order);
        else                        Pos.Index = Size() - 1;

        return Pos;
        }                               // MaxPos()

    tPosition MinPos(tTraversalOrder Order = eDefault)
        {
        if (Order == eDefault)  Order = DefaultTraversalOrder;
        if (Order == eDefault)  Order = eInOrderSmall;

        tPosition Pos;
        if (IsSmallOrder(Order))    Pos.pCur  = GetMinSmall(Order);
        else                        Pos.Index = 0;

        return Pos;
        }                               // MinPos()

    ////////// tBinSearchTreeBase::NextPos() and tBinSearchTreeBase::PrevPos()
    // Return a tPosition representing the next / previous node in the tree, by traversal type

    tPosition NextPos(tPosition CurPos, tTraversalOrder Order = eDefault)
        {
        if (Order == eDefault)  Order = DefaultTraversalOrder;
        if (Order == eDefault)  Order = eInOrderSmall;

        tPosition NewPos = CurPos;
        if (IsSmallOrder(Order))
            NewPos.pCur = NextNodeSmall(CurPos.pCur, Order);
        else
            {
            if      (NewPos.Index > Size())     NewPos.Index = Size();
            else if (NewPos.Index < Size())   ++NewPos.Index;
            }

        return NewPos;
        }                               // NextPos()

    tPosition PrevPos(tPosition CurPos, tTraversalOrder Order = eDefault)
        {
        if (Order == eDefault)  Order = DefaultTraversalOrder;
        if (Order == eDefault)  Order = eInOrderSmall;

        tPosition NewPos = CurPos;
        if (IsSmallOrder(Order))
            {
            if (!NewPos.pCur)   NewPos      = MaxPos(Order);
            else                NewPos.pCur = PrevNodeSmall(CurPos.pCur, Order);
            }
        else
            {
            if (!NewPos.Index || (NewPos.Index > Size()))   NewPos.Index = Size();
            else                                          --NewPos.Index;
            }

        return NewPos;
        }                               // PrevPos()

    ////////// tBinSearchTreeBase::RemoveBaseOrdered()
    // Remove *pRemove.
    // Although this class does not know about Keys or Values, this function still
    //  still assumes that Left < Parent < Right.
    // Deletes the memory used by the tBinSearchNodeBase.

    bool RemoveBaseOrdered(tBinSearchNodeBase *pRemove)
        {
        if (!pRemove)
            return false;

        tBinSearchNodeBase *pReplacement = nullptr;
        if (pRemove->pLeft)
            {                               // The node to be removed has at least a left child.
            if (pRemove->pRight)
                {                           // The node to be removed has two children.
                // To mostly preserve the shape of the tree, replace the node
                //  to be removed with either it's predecessor or it's successor.
                unsigned Tmp = reinterpret_cast<unsigned>(pRemove);
                Tmp = Tmp + (Tmp >> 4) + (Tmp >> 11) + (Tmp >> 17);
                bool Randomish = (Tmp & (1 << 9));

                if (Randomish)
                    pReplacement = MaxSmall(pRemove->pLeft,  eInOrderSmall);    // Find the predecessor.
                else
                    pReplacement = MinSmall(pRemove->pRight, eInOrderSmall);    // Find the successor.

                if (pReplacement->pUp->pLeft == pReplacement)   pReplacement->pUp->pLeft  = nullptr;
                else                                            pReplacement->pUp->pRight = nullptr;
                }                           // if (pRemove->pRight)
            }                               // if (pRemove->pLeft)
        else if (pRemove->pLeft)
            pReplacement = pRemove->pLeft;  // The node to be removed has only a left child.
        else
            pReplacement = pRemove->pRight; // The node to be removed has only a right child.

        // Clean up.
        if (pRoot == pRemove)                       pRoot                = pReplacement;
        else if (pRemove->pUp->pLeft == pRemove)    pRemove->pUp->pLeft  = pReplacement;
        else                                        pRemove->pUp->pRight = pReplacement;

        InvalidateCache();
        delete pRemove;
        --NodeCount;
        return true;
        }                               // RemoveBaseOrdered()

    ////////// tBinSearchTreeBase::RemoveSubtreeBase()
    // Remove the subtree at *pSubtree.
    // Return true if the subtree was successfully removed.

    bool RemoveSubtreeBase(tBinSearchNodeBase *pSubtree)
        {
        if (!pSubtree)
            return false;

        RemoveSubtreeBase(pSubtree->pLeft);
        RemoveSubtreeBase(pSubtree->pRight);

        if (pSubtree->pUp)
            {
            if (pSubtree->pUp->pLeft == pSubtree)   pSubtree->pUp->pLeft  = nullptr;
            else                                    pSubtree->pUp->pRight = nullptr;
            }

        InvalidateCache();
        delete pSubtree;
        --NodeCount;
        return true;
        }                               // RemoveSubtreeBase()

    //////////
    // Data.

    size_t                       NodeCount = 0;
    tBinSearchNodeBase              *pRoot = nullptr;
    tTraversalOrder  DefaultTraversalOrder = eInOrderSmall;  // Match the order used by the STL map<>.

    // Cached values for use with the small iterators.
    tBinSearchNodeBase *pBreadthFirstFirst = nullptr;
    tBinSearchNodeBase *     pInOrderFirst = nullptr;
    tBinSearchNodeBase *   pPostOrderFirst = nullptr;
    tBinSearchNodeBase *    pPreOrderFirst = nullptr;

    tBinSearchNodeBase *pBreadthFirstLast  = nullptr;
    tBinSearchNodeBase *     pInOrderLast  = nullptr;
    tBinSearchNodeBase *   pPostOrderLast  = nullptr;
    tBinSearchNodeBase *    pPreOrderLast  = nullptr;

    // Cached sequenced for use with the fast iterators.
    // Each array contains one extra pointer to mark the end of the sequence.
    tBinSearchNodeBase **ppBreadthFirstSeq = nullptr;
    tBinSearchNodeBase **     ppInOrderSeq = nullptr;
    tBinSearchNodeBase **   ppPostOrderSeq = nullptr;
    tBinSearchNodeBase **    ppPreOrderSeq = nullptr;
    };                                  // class tBinSearchTreeBase

#endif                                  // #ifndef BinSearchTreeBase_hpp
