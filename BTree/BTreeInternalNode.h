//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_BTREEINTERNALNODE_H
#define BTREETEST_BTREEINTERNALNODE_H


#include "BTreeNode.h"

class BTreeInternalNode : public BTreeNode
{
public:
    BTreeInternalNode();
    ~BTreeInternalNode();

private:
    int removeKey(int idx) override;

public:
    void addKey(int key) override;
    void addKey(int key, BTreeNode* child) override;
};


#endif //BTREETEST_BTREEINTERNALNODE_H
