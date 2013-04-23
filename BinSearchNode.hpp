// BinSearchNode.hpp
// Part of BinSeatchTree, a basic non-balanced binary searh tree.
// Templated version of the node type.
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.
// Contact: jlane at-sign NoveltyHillSoftware period commercial

#ifndef BinSearchNode_hpp
#define BinSearchNode_hpp

#include <cstring>
#include <functional>
#include <iostream>
#include <iomanip>

#include "BinSearchNodeBase.hpp"

template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> class tBinSearchNode;
template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> void DumpNode   (tBinSearchNode<_tK, _tV, _tRelOp> *pNode);
template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> void DumpSubTree(tBinSearchNode<_tK, _tV, _tRelOp> *pNode, int Indent, char const *pPrefix);
template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> _tV  *GetValue  (tBinSearchNode<_tK, _tV, _tRelOp> *pSubtree, _tK const &Key);

template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> tBinSearchNode<_tK, _tV, _tRelOp>
*FindNode(tBinSearchNode<_tK, _tV, _tRelOp> *pRoot, _tK const &Key, tBinSearchNode<_tK, _tV, _tRelOp> **ppParent);

//////////////////////////////////////////////////////////////////////
// One node in a binary search tree.
//////////////////////////////////////////////////////////////////////

template <typename _tK, typename _tV, typename _tRelOp> class tBinSearchNode: public tBinSearchNodeBase
    {
  public:

    typedef _tK                                 tKey;
    typedef tBinSearchNode<_tK, _tV, _tRelOp>   tNode;
    typedef _tV                                 tValue;
    typedef std::pair<const tKey, tValue>       tKeyValue;

    friend void   DumpNode    <> (tNode *pNode);
    friend void   DumpSubTree <> (tNode *pNode, int Indent, char const *pPrefix);
    friend tNode *FindNode    <> (tNode *pRoot, _tK const &Key, tNode **ppParent);
    friend _tV   *GetValue    <> (tNode *pSubtree, _tK const &Key);

    tBinSearchNode():                 tBinSearchNodeBase()              { }
    tBinSearchNode(tNode const &Src): tBinSearchNodeBase()              { pLeft = Src.pLeft; pRight = Src.pRight; pUp = Src.pUp; KV = Src.KV; }
    tBinSearchNode(_tK K, _tV V):     tBinSearchNodeBase(), KV(K, V)    { }

    virtual ~tBinSearchNode()                       { }

    bool operator==(tBinSearchNode const &Right)    { _tRelOp RelOp; return !RelOp(KV.first, Right.KV.first) && !RelOp(Right.KV.first, KV.first);  }
    bool operator< (tBinSearchNode const &Right)    { _tRelOp RelOp; return  RelOp(      KV.first, Right.KV.first);                                }
    bool operator> (tBinSearchNode const &Right)    { _tRelOp RelOp; return  RelOp(Right.KV.first,       KV.first);                                }

    bool operator!=(tBinSearchNode const &Right)    { return !(*this == Right); }
    bool operator<=(tBinSearchNode const &Right)    { return !(*Right < *this); }
    bool operator>=(tBinSearchNode const &Right)    { return !(*this  < Right); }

    //////////
    // Data.

    tKeyValue KV;
    };                                  // class tBinSearchNode

//////////////////////////////////////////////////////////////////////
// Search a subtree for a specific node.
// Return a pointer to the node, or nullptr if not found.
// If pparent != nullptr, return a pointer to the node's parent, i.e., where the Key should be inserted if not found.
// pParent will be null if pNode is null, or if it is the root of the entire tree.

template<typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> tBinSearchNode<_tK, _tV, _tRelOp>
*FindNode(tBinSearchNode<_tK, _tV, _tRelOp> *pNode, _tK const &Key, tBinSearchNode<_tK, _tV, _tRelOp> **ppParent)
    {
    _tRelOp RelOp;
    tBinSearchNode<_tK, _tV, _tRelOp> *pParent;
    if (pNode)
        pParent = dynamic_cast<tBinSearchNode<_tK, _tV, _tRelOp> *>(pNode->pUp);

    while (pNode)
        {
        if (!RelOp(Key, pNode->KV.first) && !RelOp(pNode->KV.first, Key))
            break;

        pParent = pNode;
        if (RelOp(Key, pNode->KV.first)) pNode = dynamic_cast<tBinSearchNode<_tK, _tV, _tRelOp> *>(pNode->pLeft);
        else                             pNode = dynamic_cast<tBinSearchNode<_tK, _tV, _tRelOp> *>(pNode->pRight);
        }

    if (ppParent)
        *ppParent = pParent;

    return pNode;
    }                               // FindNode()

//////////////////////////////////////////////////////////////////////
// Search a subtree for the Value corresponding to a given Key.
// Return a pointer to the value, or nullptr if not found.

template<typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> _tV *GetValue(tBinSearchNode<_tK, _tV, _tRelOp> *pSubtree, _tK const &Key)
    {
    if (!pSubtree)
        return nullptr;

    tBinSearchNode<_tK, _tV, _tRelOp> *pNode = FindNode(pSubtree, Key, nullptr);
    if (pNode)
        return &(pNode->KV.second);
    return nullptr;
    }                               // GetValue()

//////////////////////////////////////////////////////////////////////
// Utility functions, mostly for debugging support.
//////////////////////////////////////////////////////////////////////

// Making these non-member functions allows pNode to be == nullptr.

template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>> void DumpNode(tBinSearchNode<_tK, _tV, _tRelOp> *pNode)
    {
    std::cout << "tBinSearchNode at " << pNode;
    if (pNode)
        {
        std::cout << "; Key is "        << pNode->KV.first
                  << ", Value is "      << pNode->KV.second
                  << "; pParent is "    << pNode->pUp
                  << ", pLeft is "      << pNode->pLeft
                  << ", pRight is "     << pNode->pRight;
        }
    }                                   // DumpNode()

template <typename _tK, typename _tV, typename _tRelOp = std::less<_tK>>
void DumpSubTree(tBinSearchNode<_tK, _tV, _tRelOp> *pNode, int Indent, char const *pPrefix)
    {
    int Len = (pPrefix ? strlen(pPrefix) : 0);
    std::cout << std::setw(Len + Indent)
              << (pPrefix ? pPrefix : "")
              << std::setw(4)
              << Indent
              << " "
              << std::flush;

    DumpNode(pNode);
    std::cout << std::endl << std::flush;

    if (pNode)
        {
        DumpSubTree(dynamic_cast<tBinSearchNode<_tK, _tV, _tRelOp> *>(pNode->pLeft),  Indent + 1, "Left :");
        DumpSubTree(dynamic_cast<tBinSearchNode<_tK, _tV, _tRelOp> *>(pNode->pRight), Indent + 1, "Right:");
        }
    }                                   // DumpSubTree()

#endif                                  // #ifndef BinSearchNode_hpp
