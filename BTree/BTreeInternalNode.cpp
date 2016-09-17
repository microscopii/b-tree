//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeInternalNode.h"
#include "BinarySearch.h"

BTreeInternalNode::BTreeInternalNode() : BTreeNode(false) {

    keys     = new int[BTree::MAX_KEYS];
    children = new BTreeNode*[BTree::MAX_KEYS + 1];
}



BTreeInternalNode::~BTreeInternalNode() {

    delete[] keys;
    delete[] children;
}



bool BTreeInternalNode::isFull() {

    return nKeys == BTree::MAX_KEYS;
}



void BTreeInternalNode::addKey(int key) {}



void BTreeInternalNode::addKey(int key, BTreeNode* child) {

    int idx = 0;

    if (nKeys > 0) {
        idx = BinarySearch::findGT(keys, nKeys, key);
    }


    int nKeysMoved = nKeys - idx;

    if (nKeysMoved > 0) {
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



int BTreeInternalNode::removeKey(int idx) {

    int removedKey = keys[idx];


    int nKeysMoved = nKeys - 1 - idx;

    if (nKeysMoved > 0) {
        // Shift keys to the left
        std::copy_n(keys + idx + 1, nKeysMoved, keys + idx);

        // Shift children to the left
        std::copy_n(children + idx + 2, nKeysMoved, children + idx + 1);
    }

    // Decrement number of keys
    nKeys--;


    return removedKey;
}



void BTreeInternalNode::split(BTreeNode* parent) {

    // Median key
    int medianKey = this->keys[BTree::MIN_DEGREE];

    // Create right child
    BTreeInternalNode* rightChild = new BTreeInternalNode();


    // Index of split
    int t = BTree::MIN_DEGREE + 1;

    int nKeysMoved = BTree::MAX_KEYS - t;

    // Copy 2nd half of keys from left child
    std::copy_n(this->keys + t, nKeysMoved, rightChild->keys);

    // Copy 2nd half of children from left child
    std::copy_n(this->children + t, nKeysMoved + 1, rightChild->children);


    // Adjust the number of keys
    this->nKeys       -= nKeysMoved + 1;
    rightChild->nKeys += nKeysMoved;


    // Link siblings
    ListNode::link(this, rightChild, this->next());

    parent->addKey(medianKey, rightChild);
}
