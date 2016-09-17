//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_BTREELEAFNODE_H
#define BTREETEST_BTREELEAFNODE_H


#include "BTreeNode.h"

class BTreeLeafNode : public BTreeNode {

public:
    BTreeLeafNode();
    ~BTreeLeafNode();

private:
    bool isFull() override;
    int removeKey(int idx) override;
    void split(BTreeNode* node) override;

public:
    void addKey(int key) override;
    void addKey(int key, BTreeNode* child) override;
};


#endif //BTREETEST_BTREELEAFNODE_H
