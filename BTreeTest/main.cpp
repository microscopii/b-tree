//
//  main.cpp
//  BTreeTest
//
//  Created by Mark on 9/17/16.
//  Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"

int main() {

    int keys[] = {
        71, 80, 82, 99, 57,
        31, 26, 79,  0, 15,
        74, 28, 61, 90, 75,
        27, 10, 77, 24, 68,
        11,  3, 17, 97, 96,

         2, 65, 66, 95, 94,
         6, 14, 41, 52, 93,
        63, 86, 32, 42, 72,
        49, 92, 76, 25, 13,
        18,  9, 16, 85, 87,

        56, 60, 45, 46, 88,
        55, 98, 64, 33, 47,
        58, 37, 20, 78, 22,
        51, 44, 53, 54, 40,
        19, 67,  4, 69, 70,

        12,  1, 30, 23, 73,
         7, 21, 83,  8, 81,
        91, 50, 84, 43, 34,
        89, 39, 35, 36, 59,
        48,  5, 29, 62, 38,
    };


    BTree* btree = new BTree();


    // Test insertion algorithm
    int t = BTree::MAX_LEAF_KEYS;

    for (int i = 0; i < t; i++)
        btree->insertKey(keys[i]);

    btree->dump();


    for (int i = t; i < 100; i++)
        btree->insertKey(keys[i]);

    btree->dump();


    // Test deletion algorithm
    btree->deleteKey(25);
    btree->deleteKey(71);
    btree->deleteKey(85);

    btree->dump();


    // Test double-linked leaf nodes
    btree->dumpLeafNodesAsc();
    btree->dumpLeafNodesDesc();


    delete btree;

    return 0;
}
