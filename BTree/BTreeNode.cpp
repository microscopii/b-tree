//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeNode.h"
#include "BTreeLeafNode.h"
#include "BTreeInternalNode.h"

BTreeNode::BTreeNode(bool isLeaf)
{
    this->isLeaf = isLeaf;
    this->nKeys  = 0;
}



BTreeNode::~BTreeNode() {}



bool BTreeNode::isFull()
{
    return nKeys == BTree::MAX_KEYS;
}



int BTreeNode::firstKey()
{
    return keys[0];
}



int BTreeNode::lastKey()
{
    return keys[nKeys - 1];
}



int BTreeNode::removeFirstKey()
{
    return removeKey(0);
}



int BTreeNode::removeLastKey()
{
    return removeKey(nKeys - 1);
}



void BTreeNode::splitChild(BTreeNode* parent, int idx)
{
    BTreeNode* leftChild = parent->children[idx];

    // Create right child
    BTreeNode* rightChild = leftChild->isLeaf ? (BTreeNode*) new BTreeLeafNode() : (BTreeNode*) new BTreeInternalNode();


    // Median key
    int medianKey = leftChild->keys[BTree::MIN_DEGREE - 1];


    // Index of split
    int t = BTree::MIN_DEGREE;

    int nKeysMoved = BTree::MAX_KEYS - t;

    // Copy 2nd half of keys/children from left child to right child
    std::copy_n(leftChild->keys + t, nKeysMoved, rightChild->keys);

    if (!leftChild->isLeaf)
        std::copy_n(leftChild->children + t, nKeysMoved + 1, rightChild->children);


    // Adjust the number of keys
    leftChild->nKeys  -= nKeysMoved + 1;
    rightChild->nKeys += nKeysMoved;


    // Link siblings
    ListNode::link(leftChild, rightChild, leftChild->next());

    parent->addKey(medianKey, rightChild);
}



void BTreeNode::mergeChildren(BTreeNode* parent, int idx)
{
    int medianKey = parent->keys[idx];

    BTreeNode* leftChild  = parent->children[idx];
    BTreeNode* rightChild = parent->children[idx + 1];


    // Copy keys from right child to left child
    std::copy_n(rightChild->keys, BTree::MIN_DEGREE - 1, leftChild->keys + BTree::MIN_DEGREE);

    if (!leftChild->isLeaf)
        std::copy_n(rightChild->children, BTree::MIN_DEGREE, leftChild->children + BTree::MIN_DEGREE);


    // Add median key
    leftChild->keys[BTree::MIN_DEGREE - 1] = medianKey;

    // Adjust the number of keys
    leftChild->nKeys = BTree::MAX_KEYS;


    // Link siblings
    ListNode::link(leftChild, rightChild->next());

    parent->removeKey(idx);
}



void BTreeNode::rotateLeft(BTreeNode* parent, int idx)
{
    BTreeNode* leftChild  = parent->children[idx];
    BTreeNode* rightChild = parent->children[idx + 1];


    // Rotate left through key of parent
    int key = rightChild->keys[0];

    std::copy_n(rightChild->keys + 1, rightChild->nKeys - 1, rightChild->keys);

    if (!leftChild->isLeaf)
        std::copy_n(rightChild->children + 1, rightChild->nKeys, rightChild->children);

    leftChild->keys[leftChild->nKeys] = parent->keys[idx];
    parent->keys[idx] = key;


    // Adjust the number of keys
    leftChild->nKeys  += 1;
    rightChild->nKeys -= 1;
}



void BTreeNode::rotateRight(BTreeNode* parent, int idx)
{
    BTreeNode* leftChild  = parent->children[idx - 1];
    BTreeNode* rightChild = parent->children[idx];


    // Rotate right through key of parent
    std::copy_n(rightChild->keys, rightChild->nKeys, rightChild->keys + 1);

    if (!rightChild->isLeaf)
        std::copy_n(rightChild->children, rightChild->nKeys + 1, rightChild->children + 1);

    rightChild->keys[0] = parent->keys[idx - 1];
    parent->keys[idx - 1] = leftChild->keys[leftChild->nKeys - 1];


    // Adjust the number of keys
    leftChild->nKeys  -= 1;
    rightChild->nKeys += 1;
}



std::string BTreeNode::toString()
{
    std::string str = "";

    for (int i = 0; i < nKeys - 1; i++)
    {
        str += keys[i];
        str += ", ";
    }

    str += keys[nKeys - 1];

    return str;
}



std::string BTreeNode::toStringReversed()
{
    std::string str = "";

    for (int i = nKeys - 1; i > 0; i--)
    {
        str += keys[i];
        str += ", ";
    }

    str += keys[0];

    return str;
}
