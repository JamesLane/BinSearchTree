// MakeTree.cpp
// Temporary debugging support for BinSearchTree.hpp.
// Test Tree.add().
// Copyright (C) 2013 by James Lane
// Copyright (C) 2013 by Novelty Hill Software, Inc.

// Todo Turn this into a unit test.

//#define DbgOutput(Msg)  { std::cout << Msg << std::endl << std::flush; }
#define Summary(Msg)    { std::cout << Msg << std::endl << std::flush; }

#include "TreeTest.hpp"

// These functions return "Pass" if the size of the constructed tree is correct.
// Subsequent tests will fail if the content of the tree is wrong.

//////////////////////////////////////////////////////////////////////

// Create a 1 node test tree, with a positive key and a negative payload.

/*                                                          */
/*                  .........100.........                   */
/*                //                     \\                 */
/*             null                       null              */

bool MakeTree1(tTree &Tree)
    {
    DbgOutput("Make a 1 node tree");
    Tree.Add(17, -17);

    // Tree.Dump();
    bool Pass = (Tree.size() == 1);
    if (!Pass) { DbgOutput("    Tree1 size() is " << Tree.size() << ", expected 1"); }
    return Pass;
    }                                   // MakeTree1()

//////////////////////////////////////////////////////////////////////

// Create a 16 node test tree, with positive keys and negative payloads.

/*                                                          */
/*                  .........100.........                   */
/*                //                     \\                 */
/*           ...060...                 ...130...            */
/*         //         \\             //         \\          */
/*       040           080         120           150        */
/*     //   \\       //   \\     //            //   \\      */
/*   010     050   070     090 110           140     160    */
/*      \\                                                  */
/*       030                                                */
/*     //                                                   */
/*   020                                                    */

bool MakeTree16(tTree &Tree)
    {
    DbgOutput("Make a 16 node tree");

    Tree.Add(100, -100);
    Tree.Add( 60,  -60);
    Tree.Add(130, -130);
    Tree.Add( 40,  -40);
    Tree.Add( 80,  -80);
    Tree.Add(120, -120);
    Tree.Add(150, -150);
    Tree.Add( 10,  -10);
    Tree.Add( 50,  -50);
    Tree.Add( 70,  -70);
    Tree.Add( 90,  -90);
    Tree.Add(110, -110);
    Tree.Add(140, -140);
    Tree.Add(160, -160);
    Tree.Add( 30,  -30);
    Tree.Add( 20,  -20);

    // Tree.Dump();
    bool Pass = (Tree.size() == 16);
    if (!Pass) { DbgOutput("    Tree16 size() is " << Tree.size() << ", expected 16"); }
    return Pass;
    }                                   // MakeTree16()
