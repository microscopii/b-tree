//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_BTREE_H
#define BTREETEST_BTREE_H


#include "List.h"

class BTreeNode;

class BTree {

public:
    static const int MAX_DEPTH = 10;
    static const int MIN_LEAF_DEGREE = 4;
    static const int MAX_LEAF_KEYS = (2 * MIN_LEAF_DEGREE);
    static const int MIN_DEGREE = 2;
    static const int MAX_KEYS = (2 * MIN_DEGREE) + 1;

private:
    int depth;
    BTreeNode* root;
    List* nodes[MAX_DEPTH];

public:
    BTree();
    ~BTree();

    BTreeNode* findLeafWithFirstKey(BTreeNode* node);
    BTreeNode* findLeafWithLastKey(BTreeNode* node);
    BTreeNode* findLeaf(int key);

    void insertKey(int key);
    bool deleteKey(int key);

    void dump();
    void dumpLeafNodesAsc();
    void dumpLeafNodesDesc();

private:
    BTreeNode* createRootLeafNode();
    BTreeNode* createRootNode();
    void insertNonFull(BTreeNode* node, int key);
    void dump(BTreeNode* node, int level);
    void dumpLeaf(BTreeNode* node, int level);
    void indent(int n);
};


#endif //BTREETEST_BTREE_H
