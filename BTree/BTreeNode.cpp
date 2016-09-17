//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTreeNode.h"

BTreeNode::BTreeNode(bool isLeaf) {

    this->isLeaf = isLeaf;
    this->nKeys  = 0;
}



BTreeNode::~BTreeNode() {}



int BTreeNode::firstKey() {

    return keys[0];
}



int BTreeNode::lastKey() {

    return keys[nKeys - 1];
}



int BTreeNode::removeFirstKey() {

    return removeKey(0);
}



int BTreeNode::removeLastKey() {

    return removeKey(nKeys - 1);
}



void BTreeNode::splitChild(int idx) {

    children[idx]->split(this);
}



std::string BTreeNode::toString() {

    std::string str = "";

    for (int i = 0; i < nKeys - 1; i++) {
        str += std::to_string(keys[i]);
        str += ", ";
    }

    str += std::to_string(keys[nKeys - 1]);

    return str;
}



std::string BTreeNode::toStringReversed() {

    std::string str = "";

    for (int i = nKeys - 1; i > 0; i--) {
        str += std::to_string(keys[i]);
        str += ", ";
    }

    str += std::to_string(keys[0]);

    return str;
}
