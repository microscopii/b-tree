//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeInternalNode.h"
#include "BinarySearch.h"

BTreeInternalNode::BTreeInternalNode() : BTreeNode(false)
{
    keys     = new int[BTree::MAX_KEYS];
    children = new BTreeNode*[BTree::MAX_KEYS + 1];
}



BTreeInternalNode::~BTreeInternalNode()
{
    delete[] keys;
    delete[] children;
}



void BTreeInternalNode::addKey(int key) {}



void BTreeInternalNode::addKey(int key, BTreeNode* child)
{
    int idx = 0;

    if (nKeys > 0)
        idx = BinarySearch::findGT(keys, nKeys, key);


    int nKeysMoved = nKeys - idx;

    if (nKeysMoved > 0)
    {
        // Shift keys to the right
        std::copy_n(keys + idx, nKeysMoved, keys + idx + 1);

        // Shift children to the right
        std::copy_n(children + idx + 1, nKeysMoved, children + idx + 2);
    }


    // Insert new key and increment number of keys
    keys[idx] = key;
    nKeys++;

    // Insert new child
    children[idx + 1] = child;
}



int BTreeInternalNode::removeKey(int idx)
{
    int removedKey = keys[idx];


    int nKeysMoved = nKeys - 1 - idx;

    if (nKeysMoved > 0)
    {
        // Shift keys to the left
        std::copy_n(keys + idx + 1, nKeysMoved, keys + idx);

        // Shift children to the left
        std::copy_n(children + idx + 2, nKeysMoved, children + idx + 1);
    }

    // Decrement number of keys
    nKeys--;


    return removedKey;
}
