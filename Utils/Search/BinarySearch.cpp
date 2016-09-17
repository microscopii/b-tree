//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BinarySearch.h"

/**
 * Find index of first key less than the specified key
 *
 * @param keys   an array of keys
 * @param nKeys  the number of keys
 * @param key    the key to search for
 * @return index of found key
 */
int BinarySearch::findLT(int* keys, int nKeys, int key) {

    int lo = 0;
    int hi = nKeys - 1;

    if (keys[hi] < key) {
        return hi;
    }


    while (hi >= lo) {

        int mid = (lo + hi) >> 1;

        if (keys[mid] < key)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo - 1;
}



/**
 * Find index of first key greater than or equal to the specified key
 *
 * @param keys   an array of keys
 * @param nKeys  the number of keys
 * @param key    the key to search for
 * @return index of found key
 */
int BinarySearch::findGE(int* keys, int nKeys, int key) {

    int lo = 0;
    int hi = nKeys - 1;

    if (keys[lo] >= key) {
        return lo;
    }


    while (hi >= lo) {

        int mid = (lo + hi) >> 1;

        if (keys[mid] >= key)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    return hi + 1;
}



/**
 * Find index of first key greater than the specified key
 *
 * @param keys   an array of keys
 * @param nKeys  the number of keys
 * @param key    the key to search for
 * @return index of found key
 */
int BinarySearch::findGT(int* keys, int nKeys, int key) {

    int lo = 0;
    int hi = nKeys - 1;

    if (keys[lo] > key) {
        return lo;
    }


    while (hi >= lo) {

        int mid = (lo + hi) >> 1;

        if (keys[mid] > key)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    return hi + 1;
}



/**
 * Find index of first key less than or equal to the specified key
 *
 * @param keys   an array of keys
 * @param nKeys  the number of keys
 * @param key    the key to search for
 * @return index of found key
 */
int BinarySearch::findLE(int* keys, int nKeys, int key) {

    int lo = 0;
    int hi = nKeys - 1;

    if (keys[hi] <= key) {
        return hi;
    }


    while (hi >= lo) {

        int mid = (lo + hi) >> 1;

        if (keys[mid] <= key)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo - 1;
}



/**
 * Find index of key equal to the specified key or return -1
 *
 * @param keys   an array of keys
 * @param nKeys  the number of keys
 * @param key    the key to search for
 * @return index of found key
 */
int BinarySearch::findEQ(int* keys, int nKeys, int key) {

    int lo = 0;
    int hi = nKeys - 1;

    if (keys[lo] > key || keys[hi] < key) {
        return -1;
    }


    while (hi >= lo) {

        int mid = (lo + hi) >> 1;

        if (keys[mid] >= key)
            hi = mid - 1;
        else
            lo = mid + 1;
    }


    return (keys[hi + 1] == key) ? hi + 1 : -1;
}
