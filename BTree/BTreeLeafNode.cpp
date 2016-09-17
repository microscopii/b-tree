//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeLeafNode.h"
#include "BinarySearch.h"

BTreeLeafNode::BTreeLeafNode() : BTreeNode(true) {

    keys     = new int[BTree::MAX_LEAF_KEYS];
    children = nullptr;
}



BTreeLeafNode::~BTreeLeafNode() {

    delete[] keys;
}



bool BTreeLeafNode::isFull() {

    return nKeys == BTree::MAX_LEAF_KEYS;
}



void BTreeLeafNode::addKey(int key) {

    int idx = 0;

    if (nKeys > 0) {
        idx = BinarySearch::findGT(keys, nKeys, key);
    }


    int nKeysMoved = nKeys - idx;

    if (nKeysMoved > 0) {
        // Shift keys to the right
        std::copy_n(keys + idx, nKeysMoved, keys + idx + 1);
    }


    // Insert new key and increment number of keys
    keys[idx] = key;
    nKeys++;
}



void BTreeLeafNode::addKey(int key, BTreeNode* child) {}



int BTreeLeafNode::removeKey(int idx) {

    int removedKey = keys[idx];


    int nKeysMoved = nKeys - 1 - idx;

    if (nKeysMoved > 0) {
        // Shift keys to the left
        std::copy_n(keys + idx + 1, nKeysMoved, keys + idx);
    }

    // Decrement number of keys
    nKeys--;


    return removedKey;
}



void BTreeLeafNode::split(BTreeNode* parent) {

    // Median key
    int medianKey = this->keys[BTree::MIN_LEAF_DEGREE];

    // Create right child
    BTreeLeafNode* rightChild = new BTreeLeafNode();


    // Index of split
    int t = BTree::MIN_LEAF_DEGREE;

    int nKeysMoved = BTree::MAX_LEAF_KEYS - t;

    // Copy 2nd half of keys from left child
    std::copy_n(this->keys + t, nKeysMoved, rightChild->keys);


    // Adjust the number of keys
    this->nKeys       -= nKeysMoved;
    rightChild->nKeys += nKeysMoved;


    // Link siblings
    ListNode::link(this, rightChild, this->next());

    parent->addKey(medianKey, rightChild);
}
