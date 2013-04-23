// BinSearchTreeIter.hpp
// Part of BinSearchTree, a basic non-balanced binary search tree.
// Bidirectional iterator.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

#ifndef BinSearchTreeIter_hpp
#define BinSearchTreeIter_hpp

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <iterator>

#include "BinSearchTree.hpp"

//////////////////////////////////////////////////////////////////////
// tBinSearchTree iterator.
//////////////////////////////////////////////////////////////////////

template <typename _tK, typename _tV> class tIterator: public std::iterator<std::bidirectional_iterator_tag, _tV, ptrdiff_t, _tV *, _tV &>
    {
  public:

    typedef                 _tK             tKey;
    typedef tBinSearchNode< _tK,       _tV> tNode;
    typedef tBinSearchTree< _tK,       _tV> tTree;
    typedef                            _tV  tValue;
    typedef std::pair<      _tK const, _tV> tKeyValue;

    tIterator(tTraversalOrder Ord = eDefault): Order(Ord)                                           { CheckOrder(); }

    tIterator(tIterator       &Src): pTree(Src.pTree), CurPos(Src.CurPos), Order(Src.Order)         { CheckOrder(); }
    tIterator(tIterator const &Src): pTree(Src.pTree), CurPos(Src.CurPos), Order(Src.Order)         { CheckOrder(); }

    tIterator(tTree &Tree,                tTraversalOrder Ord = eDefault): pTree(&Tree), Order(Ord) { CheckOrder(); CurPos = Tree.GetEnd(Order); }
    tIterator(tTree &Tree, tPosition Pos, tTraversalOrder Ord = eDefault): pTree(&Tree), CurPos(Pos), Order(Ord)    { CheckOrder(); }

    virtual ~tIterator()    { }

    tIterator                 &operator= (tIterator const &Right)       { Order = Right.Order; pTree = Right.pTree; CurPos = Right.CurPos; return *this;  }
    std::pair<_tK const, _tV> &operator* ()                             { return   pTree->PtrFromPos(CurPos, Order)->KV;  }
    std::pair<_tK const, _tV> *operator->()                             { return &(pTree->PtrFromPos(CurPos, Order)->KV); }
    bool                       operator==(tIterator const &Right) const { return (pTree == Right.pTree) && (CurPos.pCur == Right.CurPos.pCur); }
    bool                       operator!=(tIterator const &Right) const { return (pTree != Right.pTree) || (CurPos.pCur != Right.CurPos.pCur); }

    tIterator &operator++()     {                           CurPos = pTree->NextPos(CurPos, Order); return *this;   }   // Prefix  operator++()
    tIterator &operator--()     {                           CurPos = pTree->PrevPos(CurPos, Order); return *this;   }   // Prefix  operator--()
    tIterator  operator++(int)  { tIterator RetVal = *this; CurPos = pTree->NextPos(CurPos, Order); return RetVal;  }   // Postfix operator++()
    tIterator  operator--(int)  { tIterator RetVal = *this; CurPos = pTree->PrevPos(CurPos, Order); return RetVal;  }   // Postfix operator--()

    // Ensure that the traversal order is valid.
    void CheckOrder()
        {
        if ((Order == eDefault) && pTree)
            Order = pTree->DefaultTraversalOrder;
        }                               // CheckOrder()

    // Debugging support.
    void Dump() const
        {
        std::cout << "tIterator at " << this << ", pTree is " << pTree << ", Order is " << Order << ", CurPos.Index is " << CurPos.Index;
        if (pTree->PtrFromPos(CurPos, Order))
            {
            std::cout << ": ";
            pTree->PtrFromPos(CurPos, Order)->Dump();
            }
        }                               // Dump()

    tTree          *pTree = nullptr;
    tPosition       CurPos;
    tTraversalOrder Order = eInOrderSmall;  // Default == STL map<>.
    };                                  // class tIterator

#endif                                  // #ifndef BinSearchTreeIter_hpp
