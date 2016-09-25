//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "BTree.h"
#include "BTreeInternalNode.h"
#include "BTreeLeafNode.h"
#include "BinarySearch.h"

BTree::BTree()
{
    depth = -1;
    root = createRootLeafNode();
}



BTree::~BTree()
{
    for (int i = 0; i <= depth; i++)
        delete nodes[i];
}



BTreeNode* BTree::createRootLeafNode()
{
    BTreeLeafNode* node = new BTreeLeafNode();

    depth++;
    nodes[depth] = new List(node);

    return node;
}



BTreeNode* BTree::createRootNode()
{
    BTreeInternalNode* node = new BTreeInternalNode();

    depth++;
    nodes[depth] = new List(node);

    return node;
}



/**
 * Find leaf node with the specified key in this b-tree
 *
 * @param key  key to find
 * @return leaf node
 */
BTreeNode* BTree::findLeaf(int key)
{
    BTreeNode* node = root;

    while (!node->isLeaf)
    {
        int idx = BinarySearch::findGT(node->keys, node->nKeys, key);
        node = node->children[idx];
    }

    return node;
}



/**
 * Find leaf node with first key in the specified subtree
 *
 * @param node  1st node in subtree
 * @return leaf node
 */
BTreeNode* BTree::findLeafWithFirstKey(BTreeNode* node)
{
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
BTreeNode* BTree::findLeafWithLastKey(BTreeNode* node)
{
    while (!node->isLeaf)
        node = node->children[node->nKeys];

    return node;
}



/**
 * Find predecessor key in the specified subtree
 *
 * @param node  1st node in subtree
 * @return leaf node
 */
int BTree::getSuccessor(BTreeNode* node)
{
    while (!node->isLeaf)
        node = node->children[0];

    return node->firstKey();
}



/**
 * Find successor key in the specified subtree
 *
 * @param node  1st node in subtree
 * @return leaf node
 */
int BTree::getPredecessor(BTreeNode* node)
{
    while (!node->isLeaf)
        node = node->children[node->nKeys];

    return node->lastKey();
}



/**
 * Insert a key into this b-tree
 *
 * @param key  key to insert
 */
void BTree::insertKey(int key)
{
    BTreeNode* r = root;

    if (r->isFull())
    {
        BTreeNode* s = createRootNode();
        s->children[0] = r;

        root = s;

        BTreeNode::splitChild(s, 0);
        insertNonFull(s, key);
    }
    else
    {
        insertNonFull(r, key);
    }

}



void BTree::insertNonFull(BTreeNode* node, int key)
{
    if (node->isLeaf)
    {
        node->addKey(key);
        return;
    }


    int idx = BinarySearch::findGT(node->keys, node->nKeys, key);

    if (node->children[idx]->isFull())
    {
        BTreeNode::splitChild(node, idx);

        if (key > node->keys[idx])
            idx++;
    }

    insertNonFull(node->children[idx], key);
}



/**
 * Delete a key from this b-tree.
 *
 * @param key  key to delete
 */
void BTree::deleteKey(int key)
{
    deleteKey(root, key);
}



void BTree::deleteKey(BTreeNode* node, int key)
{
    
    int idx = BinarySearch::findGE(node->keys, node->nKeys, key);


    if (key == node->keys[idx])
    {

        if (node->isLeaf)
            deleteFromLeaf(node, idx);
        else
            deleteFromNonLeaf(node, idx);

        return;
    }


    if (node->isLeaf)
    {
        printf("Key not found!\n");
        return;
    }
    else
    {
        bool flag = (idx == node->nKeys);

        if (node->children[idx]->nKeys < MIN_DEGREE)
            rebalance(node, idx);

        if (flag && idx > node->nKeys)
            deleteKey(node->children[idx - 1], key);
        else
            deleteKey(node->children[idx], key);
    }

}



void BTree::deleteFromNonLeaf(BTreeNode* node, int idx)
{

    int key = node->keys[idx];


    if (node->children[idx]->nKeys >= MIN_DEGREE)
    {
        int predKey = getPredecessor(node->children[idx]);
        node->keys[idx] = predKey;
        deleteKey(node->children[idx], predKey);

    }
    else if (node->children[idx + 1]->nKeys >= MIN_DEGREE)
    {
        int succKey = getSuccessor(node->children[idx + 1]);
        node->keys[idx] = succKey;
        deleteKey(node->children[idx + 1], succKey);

    }
    else
    {
        BTreeNode::mergeChildren(node, idx);
        deleteKey(node->children[idx], key);
    }

}



void BTree::deleteFromLeaf(BTreeNode* node, int idx)
{
    node->removeKey(idx);
}



void BTree::rebalance(BTreeNode* node, int idx)
{

    if (idx != 0)
    {
        if (node->children[idx - 1]->nKeys >= MIN_DEGREE)
        {
            BTreeNode::rotateRight(node, idx);
            return;
        }
    }


    if (idx != node->nKeys)
    {
        if (node->children[idx + 1]->nKeys >= MIN_DEGREE)
        {
            BTreeNode::rotateLeft(node, idx);
            return;
        }
    }


    if (idx != node->nKeys)
        BTreeNode::mergeChildren(node, idx);
    else
        BTreeNode::mergeChildren(node, idx - 1);
}



/**
 * Dump structure of this b-tree
 */
void BTree::dump()
{
    printf("Depth: %d\n", depth);

    if (root->isLeaf)
        dumpLeaf(root, 0);
    else
        dump(root, 0);

    printf("\n");
}



void BTree::dump(BTreeNode* node, int level)
{

    for (int i = 0; i <= node->nKeys; i++)
    {
        BTreeNode* child = node->children[i];

        if (child->isLeaf)
            dumpLeaf(child, level + 1);
        else
            dump(child, level + 1);

        if (i < node->nKeys)
        {
            indent(level);
            printf("%s\n", (char*) &node->keys[i]);
        }
    }

}



void BTree::dumpLeaf(BTreeNode* node, int level)
{
    indent(level);
    printf("%s\n", node->toString().c_str());
}



void BTree::indent(int n)
{
    for (int i = 0; i < n; i++)
        printf("\t");
}



/**
 * Dump leaf nodes in ascending order
 */
void BTree::dumpLeafNodesAsc()
{
    ListNode* node = nodes[0]->first();

    while (node->hasNext())
    {
        BTreeNode* leaf = dynamic_cast<BTreeNode*>(node);
        printf("%s, ", leaf->toString().c_str());

        node = node->next();
    }

    printf("\n\n");
}



/**
 * Dump leaf nodes in descending order
 */
void BTree::dumpLeafNodesDesc()
{
    ListNode* node = nodes[0]->last();

    while (node->hasPrev())
    {
        BTreeNode* leaf = dynamic_cast<BTreeNode*>(node);
        printf("%s, ", leaf->toStringReversed().c_str());

        node = node->prev();
    }

    printf("\n\n");
}
