//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeInternalNode.h"
#include "BTreeLeafNode.h"
#include "BinarySearch.h"

BTree::BTree() {

    depth = -1;
    root = createRootLeafNode();
}



BTree::~BTree() {

    for (int i = 0; i <= depth; i++)
        delete nodes[i];
}



BTreeNode* BTree::createRootLeafNode() {

    BTreeLeafNode* node = new BTreeLeafNode();

    depth++;
    nodes[depth] = new List(node);

    return node;
}



BTreeNode* BTree::createRootNode() {

    BTreeInternalNode* node = new BTreeInternalNode();

    depth++;
    nodes[depth] = new List(node);

    return node;
}



/**
 * Find leaf node with first key in the specified subtree
 *
 * @param node  1st node in subtree
 * @return leaf node
 */
BTreeNode* BTree::findLeafWithFirstKey(BTreeNode* node) {

    while (!node->isLeaf)
        node = node->children[0];

    return node;
}



/**
 * Find leaf node with last key in the specified subtree
 *
 * @param node  1st node in subtree
 * @return leaf node
 */
BTreeNode* BTree::findLeafWithLastKey(BTreeNode* node) {

    while (!node->isLeaf)
        node = node->children[node->nKeys];

    return node;
}



/**
 * Find leaf node with the specified key in this b-tree
 *
 * @param key  key to find
 * @return leaf node
 */
BTreeNode* BTree::findLeaf(int key) {

    BTreeNode* node = root;

    while (!node->isLeaf) {
        int idx = BinarySearch::findGT(node->keys, node->nKeys, key);
        node = node->children[idx];
    }

    return node;
}



/**
 * Insert a key into this b-tree
 *
 * @param key  key to insert
 */
void BTree::insertKey(int key) {

    BTreeNode* r = root;

    if (r->isFull()) {

        BTreeNode* s = createRootNode();
        s->children[0] = r;

        root = s;

        s->splitChild(0);
        insertNonFull(s, key);

    } else {

        insertNonFull(r, key);
    }

}



void BTree::insertNonFull(BTreeNode* node, int key) {

    if (node->isLeaf) {
        node->addKey(key);
        return;
    }


    int idx = BinarySearch::findGT(node->keys, node->nKeys, key);

    if (node->children[idx]->isFull()) {

        node->splitChild(idx);

        if (key > node->keys[idx])
            idx++;
    }

    insertNonFull(node->children[idx], key);
}



/**
 * Delete a key from this b-tree. Return true if successful.
 *
 * @param key  key to delete
 * @return true or false
 */
bool BTree::deleteKey(int key) {

    BTreeNode* node = root;
    int idx = 0;


    while (!node->isLeaf) {

        idx = BinarySearch::findGE(node->keys, node->nKeys, key);

        if (key == node->keys[idx]) {
            break;
        }

        node = node->children[idx];
    }


    if (node->isLeaf) {

        idx = BinarySearch::findEQ(node->keys, node->nKeys, key);

        if (idx > 0) {
            node->removeKey(idx);
            return true;
        }
        else {
            return false;
        }

    }


    // Find the first key in the right subtree and remove
    BTreeNode* leaf = findLeafWithFirstKey(node->children[idx + 1]);
    leaf->removeFirstKey();

    node->keys[idx] = leaf->firstKey();

    return true;
}



/**
 * Dump structure of this b-tree
 */
void BTree::dump() {

    printf("Depth: %d\n", depth);

    if (root->isLeaf)
        dumpLeaf(root, 0);
    else
        dump(root, 0);

    printf("\n");
}



void BTree::dump(BTreeNode* node, int level) {

    for (int i = 0; i <= node->nKeys; i++) {

        BTreeNode* child = node->children[i];

        if (child->isLeaf)
            dumpLeaf(child, level + 1);
        else
            dump(child, level + 1);

        if (i < node->nKeys) {
            indent(level);
            printf("%d\n", node->keys[i]);
        }

    }

}



void BTree::dumpLeaf(BTreeNode* node, int level) {

    indent(level);
    printf("%s\n", node->toString().c_str());
}



void BTree::indent(int n) {

    for (int i = 0; i < n; i++)
        printf("\t");
}



/**
 * Dump leaf nodes in ascending order
 */
void BTree::dumpLeafNodesAsc() {

    ListNode* node = nodes[0]->first();

    while (node->hasNext()) {
        BTreeNode* leaf = dynamic_cast<BTreeNode*>(node);
        printf("%s, ", leaf->toString().c_str());

        node = node->next();
    }

    printf("\n\n");
}



/**
 * Dump leaf nodes in descending order
 */
void BTree::dumpLeafNodesDesc() {

    ListNode* node = nodes[0]->last();

    while (node->hasPrev()) {
        BTreeNode* leaf = dynamic_cast<BTreeNode*>(node);
        printf("%s, ", leaf->toStringReversed().c_str());

        node = node->prev();
    }

    printf("\n\n");
}
