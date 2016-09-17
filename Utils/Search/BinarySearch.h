//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_BINARYSEARCH_H
#define BTREETEST_BINARYSEARCH_H


class BinarySearch {

public:
    static int findLT(int* keys, int nKeys, int key);
    static int findGE(int* keys, int nKeys, int key);
    static int findGT(int* keys, int nKeys, int key);
    static int findLE(int* keys, int nKeys, int key);
    static int findEQ(int* keys, int nKeys, int key);
};


#endif //BTREETEST_BINARYSEARCH_H
