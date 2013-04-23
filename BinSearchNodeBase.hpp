// BinSearchNodeBase.hpp
// Part of BinSeatchTree, a basic non-balanced binary searh tree.
// Non-template class defining the basic structure and code of a binary tree node.
// Making this a non-template class to reduce template code bloat.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-symbol NoveltyHillSoftware period commercial

#ifndef BinSearchNodeBase_hpp
#define BinSearchNodeBase_hpp

// The -Fast  traversals are O(N) space and O(1) speed.
// The -Small traversals are O(1) space and O(N log N) (in-order, pre-order, post-order) or O(N^2) (breadth-first) speed.
typedef enum
    {
    eDefault,
    eBreadthFirstFast,
    eBreadthFirstSmall,
    eInOrderFast,
    eInOrderSmall,
    ePostOrderFast,
    ePostOrderSmall,
    ePreOrderFast,
    ePreOrderSmall
    } tTraversalOrder;

//////////////////////////////////////////////////////////////////////
// Exported definitions.

class tBinSearchNodeBase;
void DumpSubTreeBase(             tBinSearchNodeBase *pNode, int Indent, char const *pPrefix);
tBinSearchNodeBase *MaxSmall(     tBinSearchNodeBase *pNode, tTraversalOrder Order);
tBinSearchNodeBase *MinSmall(     tBinSearchNodeBase *pNode, tTraversalOrder Order);
tBinSearchNodeBase *NextNodeSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order);
tBinSearchNodeBase *PrevNodeSmall(tBinSearchNodeBase *pNode, tTraversalOrder Order);

//////////////////////////////////////////////////////////////////////
// Simple utility functions.

inline bool IsFastOrder( tTraversalOrder Order)
    { return ((Order == eBreadthFirstFast ) || (Order == eInOrderFast ) || (Order == ePostOrderFast ) || (Order == ePreOrderFast )); }
inline bool IsSmallOrder(tTraversalOrder Order)
    { return ((Order == eBreadthFirstSmall) || (Order == eInOrderSmall) || (Order == ePostOrderSmall) || (Order == ePreOrderSmall)); }

//////////////////////////////////////////////////////////////////////
// One node in a binary search tree.
//////////////////////////////////////////////////////////////////////

class tBinSearchNodeBase
    {
  public:

    tBinSearchNodeBase()                                { }
    tBinSearchNodeBase(tBinSearchNodeBase       &Right) { pLeft = Right.pLeft; pRight = Right.pRight; pUp = Right.pUp; }
    tBinSearchNodeBase(tBinSearchNodeBase const &Right) { pLeft = Right.pLeft; pRight = Right.pRight; pUp = Right.pUp; }
    tBinSearchNodeBase(tBinSearchNodeBase *pL, tBinSearchNodeBase *pR, tBinSearchNodeBase *pU)
        { pLeft = pL; pRight = pR; pUp = pU; }

    virtual ~tBinSearchNodeBase()                       { }     // User is responsible for the subtrees.

    //////////
    // Data.

    tBinSearchNodeBase *pLeft  = nullptr;
    tBinSearchNodeBase *pRight = nullptr;
    tBinSearchNodeBase *pUp    = nullptr;
    };                                  // class tBinSearchNodeBase
#endif                                  // #ifndef BinSearchNodeBase_hpp
