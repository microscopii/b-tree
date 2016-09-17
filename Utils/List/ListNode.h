//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_LISTNODE_H
#define BTREETEST_LISTNODE_H


class ListNode {

    friend class List;

private:
    ListNode* leftSib;
    ListNode* rightSib;

public:
    ListNode();
    virtual ~ListNode();

    ListNode* link(ListNode* rightNode);
    static void link(ListNode* firstNode, ListNode* secondNode);
    static void link(ListNode* firstNode, ListNode* secondNode, ListNode* thirdNode);

    ListNode* next();
    ListNode* prev();

    bool hasNext();
    bool hasPrev();
};


#endif //BTREETEST_LISTNODE_H
