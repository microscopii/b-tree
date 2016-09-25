//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeLeafNode.h"
#include "BinarySearch.h"

BTreeLeafNode::BTreeLeafNode() : BTreeNode(true)
{
    keys     = new int[BTree::MAX_KEYS];
    children = nullptr;
}



BTreeLeafNode::~BTreeLeafNode()
{
    delete[] keys;
}



void BTreeLeafNode::addKey(int key)
{
    int idx = 0;

    if (nKeys > 0)
        idx = BinarySearch::findGT(keys, nKeys, key);


    int nKeysMoved = nKeys - idx;

    if (nKeysMoved > 0)
    {
        // Shift keys to the right
        std::copy_n(keys + idx, nKeysMoved, keys + idx + 1);
    }


    // Insert new key and increment number of keys
    keys[idx] = key;
    nKeys++;
}



void BTreeLeafNode::addKey(int key, BTreeNode* child) {}



int BTreeLeafNode::removeKey(int idx)
{

    int removedKey = keys[idx];


    int nKeysMoved = nKeys - 1 - idx;

    if (nKeysMoved > 0)
    {
        // Shift keys to the left
        std::copy_n(keys + idx + 1, nKeysMoved, keys + idx);
    }

    // Decrement number of keys
    nKeys--;


    return removedKey;
}
