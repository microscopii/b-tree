//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#ifndef BTREETEST_LIST_H
#define BTREETEST_LIST_H


class ListNode;

class List {

private:
    ListNode* head;
    ListNode* tail;

public:
    List();
    List(ListNode* item);
    ~List();

    ListNode* first();
    ListNode* last();

    void addFirst(ListNode* item);
    void addLast(ListNode* item);

    void removeFirst();
    void removeLast();

    void add(ListNode* item);
    bool remove(ListNode* item);
};


#endif //BTREETEST_LIST_H
