//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_BTREENODE_H
#define BTREETEST_BTREENODE_H


#include <string>
#include "ListNode.h"

class BTreeNode : public ListNode {

public:
    bool        isLeaf;
    int         nKeys;
    int*        keys;
    BTreeNode** children;

public:
    BTreeNode(bool isLeaf);
    ~BTreeNode();

    virtual bool isFull() = 0;
    virtual void addKey(int key) = 0;
    virtual void addKey(int key, BTreeNode* child) = 0;
    virtual int removeKey(int idx) = 0;
    virtual void split(BTreeNode* parent) = 0;

    int firstKey();
    int lastKey();

    int removeFirstKey();
    int removeLastKey();

    void splitChild(int idx);

    std::string toString();
    std::string toStringReversed();
};


#endif //BTREETEST_BTREENODE_H
