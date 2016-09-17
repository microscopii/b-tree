//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "ListNode.h"

ListNode::ListNode() {

    leftSib  = nullptr;
    rightSib = nullptr;
}



ListNode::~ListNode() {}



/**
 * Link ListNode on rhs to this ListNode
 *
 * @param rightNode  ListNode on rhs
 * @return ListNode on rhs
 */
ListNode* ListNode::link(ListNode* rightNode) {

    this->rightSib = rightNode;
    rightNode->leftSib = this;

    return rightNode;
}



/**
 * Link two ListNodes together
 *
 * @param firstNode   the 1st ListNode
 * @param secondNode  the 2nd ListNode
 */
void ListNode::link(ListNode* firstNode, ListNode* secondNode) {

    firstNode->rightSib = secondNode;
    secondNode->leftSib = firstNode;
}



/**
 * Link three ListNodes together
 *
 * @param firstNode   the 1st ListNode
 * @param secondNode  the 2nd ListNode
 * @param thirdNode   the 3rd ListNode
 */
void ListNode::link(ListNode* firstNode, ListNode* secondNode, ListNode* thirdNode) {

    firstNode->rightSib = secondNode;
    secondNode->leftSib = firstNode;

    secondNode->rightSib = thirdNode;
    thirdNode->leftSib = secondNode;
}



/**
 * Return true if this ListNode has a right sibling
 *
 * @return true or false
 */
bool ListNode::hasNext() {

    return (rightSib != nullptr);
}



/**
 * Return true if this ListNode has a left sibling
 *
 * @return true or false
 */
bool ListNode::hasPrev() {

    return (leftSib != nullptr);
}



/**
 * Return next ListNode in list
 *
 * @return ListNode
 */
ListNode* ListNode::next() {

    return rightSib;
}



/**
 * Return previous ListNode in list
 *
 * @return ListNode
 */
ListNode* ListNode::prev() {

    return leftSib;
}
