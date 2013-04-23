// BinSearchTree.hpp
// A basic non-balanced binary search tree.
// Originally written as an exercise.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

// Caveats
//  Unfinished.
//  Only lightly tested.
//  Not thread safe.
//  The caller is responsible for managing the memory used by the Keys and Values.
//  Keys and Values must support an assignment operator ('=' or operator=()).
//  The Key must support a relational operator (stl::less<> or equivalent).
//  Calls new and delete; might throw bad_alloc.

// Roughly similar to the STL map<>, but
//  The API is similar, but not (yet) identical.
//  map<> is a subclass of the stl_tree.h (red-black tree) template class. This class can be used as
//      a base class for other kinds of binary search trees, e.g., AVL trees, red-black trees, tries.
//  This class provides all of the standard traversals (pre-order, in-order, post-order, and breadth-first).

// Todo, in no particular order, not necessarily in this class:
//  Various items marked "Todo" in the rest of this file and the other BinSearch{Node|Tree}* files.
//  A unit test; more complete testing in general.
//  Encapsulate in one or more namespaces.
//  The rest of the STL map<> API.
//  Make it a header-only library.
//  Balanced trees.
//  Binary non-search trees.
//  N-ary trees.
//  Tries.
//  Serialize/deserialize the Key/Value pairs to/from STL string/iostream.

#ifndef BinSearchTree_hpp
#define BinSearchTree_hpp

#include <functional>

#include "BinSearchNode.hpp"
#include "BinSearchTreeBase.hpp"

template <typename _tK, typename _tV> class tIterator;

//////////////////////////////////////////////////////////////////////
// The root of a binary search tree.
//////////////////////////////////////////////////////////////////////

template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> class tBinSearchTree: public tBinSearchTreeBase
    {
  public:

    typedef tIterator<_tK, _tV>                 tIter;
    typedef _tK                                 tKey;
    typedef tBinSearchNode<_tK, _tV, _tRelOp>   tNode;
    typedef _tV                                 tValue;
    typedef std::pair<const tKey, tValue>       tKeyValue;

    tBinSearchTree()                                        { }
    // tBinSearchTree(tBinSearchTree const &Right)             { }     // Todo (copy constructor)
    // tBinSearchTree(tIter &Beg, tIter &End)                  { }     // Todo (subtree copy constructor)

    virtual ~tBinSearchTree()                               { tBinSearchTreeBase::RemoveSubtreeBase(pRoot); }

    void   Dump()                                           { DumpSubTree(dynamic_cast<tNode *>(pRoot), 0, "Root :");           }
    tNode *Max(tTraversalOrder Order = eDefault)            { return dynamic_cast<tNode *>(PtrFromPos(MaxPos(Order), Order));   }
    tNode *Min(tTraversalOrder Order = eDefault)            { return dynamic_cast<tNode *>(PtrFromPos(MinPos(Order), Order));   }

    tIter  begin(tTraversalOrder Order = eDefault)          { return tIter(*this, MinPos(Order), Order);    }
    tIter  end(  tTraversalOrder Order = eDefault)          { return tIter(*this, Order);                   }

    // Compatibility with STL map<>.
    // _tV      &at(_tK Key)                                               { }     // Todo
    // tIter     erase(tIter)                                              { }     // Todo
    // tIter     erase(tIter, tIter)                                       { }     // Todo
    // tIter     find(tKey Key)                                            { }     // Todo
    // tIter     insert(       tKeyValue)                                  { }     // Todo
    // tIter     insert(tIter, tIter)                                      { }     // Todo
    // tIter     insert(tIter, tKeyValue)                                  { }     // Todo
    // tIter     lower_bound(tKey Key, tTraversalOrder Order = eDefault)   { }     // Todo
    // size_t    max_size()                                                { }     // Todo
    // tValue    operator[](tKey Key)                                      { }     // Todo
    // tIter     upper_bound(tKey Key, tTraversalOrder Order = eDefault)   { }     // Todo

    // bool      operator==(tBinSearchTree const &Right)                   { }     // Todo
    // bool      operator!=(tBinSearchTree const &Right)                   { }     // Todo
    // bool      operator< (tBinSearchTree const &Right)                   { }     // Todo
    // bool      operator<=(tBinSearchTree const &Right)                   { }     // Todo
    // bool      operator> (tBinSearchTree const &Right)                   { }     // Todo
    // bool      operator>=(tBinSearchTree const &Right)                   { }     // Todo

    // void      operator= (tBinSearchTree const &Right)                   { }     // Todo (copy assignment)

    // tIter      cbegin()                                                 { }     // Todo
    // tIter     crbegin()                                                 { }     // Todo
    // tIter      rbegin()                                                 { }     // Todo

    // tIter      cend()                                                   { }     // Todo
    // tIter     crend()                                                   { }     // Todo
    // tIter      rend()                                                   { }     // Todo

    ////////// tBinSearchTree::PtrFromPos()
    // Return a pointer to the node corresponding to a tPosition.

    tNode *PtrFromPos(tPosition Pos, tTraversalOrder Order)
        {
        if (IsSmallOrder(Order))
            return dynamic_cast<tNode *>(Pos.pCur);
        return dynamic_cast<tNode *>(GetPtrFast(*this, Order, Pos.Index));
        }                               // PtrFromPos()

    ////////// tBinSearchTree::Add()
    // Create a new tBinSearchNode with a specified key and add it to a tree.
    // Return true iff the new node was added.

    bool Add(_tK const &Key, _tV const &Value)
        {
        _tRelOp RelOp;
        tNode *pNew    = nullptr;
        tNode *pParent = nullptr;

        if (!pRoot)
            pNew = new tNode(Key, Value);
        else
            {
            tNode *pNode = dynamic_cast<tNode *>(FindNode(dynamic_cast<tNode *>(pRoot), Key, &pParent));
            if (pNode)
                return false;           // Key is already present in Tree.
            pNew = new tNode(Key, Value);
            }

        if (!pParent)
            pRoot = pNew;
        else
            {
            pNew->pUp = pParent;
            if (RelOp(Key, pParent->KV.first))  pParent->pLeft  = pNew;
            else                                pParent->pRight = pNew;
            }

        InvalidateCache();

        ++NodeCount;
        return true;
        }                               // Add()

    ////////// tBinSearchTree::Find()
    // Find a tBinSearchNode within Tree.
    // Iff found, return true with the value in *pValue.
    // Declaring the Tree parameter const would preclude splay trees.

    _tV *Find(_tK const &Key)
        {
        tNode *pNode = dynamic_cast<tNode *>(FindNode(dynamic_cast<tNode *>(pRoot), Key, static_cast<tNode **>(nullptr)));

        if (!pNode)
            return nullptr;

        return &(pNode->KV.second);
        }                               // Find()

    ////////// tBinSearchTree::Remove()
    // Remove the node whose key == Key.
    // Return true if the node was found and removed.
    // Deletes the memory used by the tBinSearchNodeBase, but not by the Key or Value.

    bool Remove(_tK const &Key)
        {
        tNode *pFound = FindNode(dynamic_cast<tNode *>(pRoot), Key, static_cast<tNode **>(nullptr));
        if (pFound)
            return RemoveBaseOrdered(pFound);
        return false;
        }                               // Remove()

    ////////// tBinSearchTree::RemoveSubtree()
    // Remove the subtree whose key == Key and all of it's children.
    // Return true if the subtree was found and successfully removed.
    // O(number of nodes removed) time.

    bool RemoveSubtree(tBinSearchTree<_tK, _tV> &Tree, _tK &Key)
        {
        tNode *pFound = FindNode(Key, dynamic_cast<tNode *>(pRoot), static_cast<tNode **>(nullptr));
        if (!pFound)
            return false;
        return RemoveSubtreeBase(pFound);
        }                               // RemoveSubtree()
    };                                  // class tBinSearchTree

#include "BinSearchTreeIter.hpp"

#endif                                  // #ifndef BinSearchTree_hpp
