//
//  main.cpp
//  BTreeTest
//
//  Created by Mark on 9/17/16.
//  Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"

void insertKeys()
{
    char initKeys[] =
    {
        'U', 'V', 'X', 'Y', 'Z',
        'N', 'O', 'P', 'T', 'R',
        'S', 'J', 'K', 'M', 'G',
        'A', 'C', 'D', 'E'
    };


    // Create initial b-tree
    BTree* btree = new BTree();

    for (int i = 0; i < 19; i ++)
        btree->insertKey(initKeys[i]);

    btree->dump();


    // Test insertion algorithm
    char keys[] =
    {
        'B', 'Q', 'L', 'F'
    };

    for (int i = 0; i < 4; i++)
    {
        btree->insertKey(keys[i]);
        btree->dump();
    }


    delete btree;
}



void deleteKeys()
{
    char initKeys[] =
    {
        'E', 'F', 'G', 'J', 'K',
        'M', 'N', 'O', 'L', 'A',
        'B', 'C', 'P', 'Q', 'R',
        'X', 'Y', 'Z', 'T', 'U',
        'V', 'S', 'D'
    };


    // Create initial b-tree
    BTree* btree = new BTree();

    for (int i = 0; i < 23; i ++)
        btree->insertKey(initKeys[i]);

    btree->dump();


    // Test deletion algorithm
    char keys[] =
    {
        'F', 'M', 'G', 'D', 'B'
    };

    for (int i = 0; i < 5; i++)
    {
        btree->deleteKey(keys[i]);
        btree->dump();
    }


    delete btree;
}



int main()
{
    insertKeys();
    deleteKeys();

    return 0;
}
