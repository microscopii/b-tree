//
// Created by Mark on 9/17/16.
// Copyright (c) 2016 Microscopii Research. All rights reserved.
//

#include "List.h"
#include "ListNode.h"

/**
 * Constuct an empty list
 */
List::List()
{
    head = new ListNode();
    tail = new ListNode();

    ListNode::link(head, tail);
}



/**
 * Construct a list and add first item
 *
 * @param item  ListNode to add
 */
List::List(ListNode* item)
{
    head = new ListNode();
    tail = new ListNode();

    ListNode::link(head, item, tail);
}



List::~List()
{
    ListNode* node = head->rightSib;

    while (node != tail)
    {
        delete node;
        node = node->rightSib;
    }

    delete head;
    delete tail;
}



/**
 * Return first item in the list
 *
 * @return the ListNode
 */
ListNode* List::first()
{
    return head->rightSib;
}



/**
 * Return last item in the list
 *
 * @return the ListNode
 */
ListNode* List::last()
{
    return tail->leftSib;
}



/**
 * Add an item to the beginning of the list
 *
 * @param item  the ListNode to add
 */
void List::addFirst(ListNode* item)
{
    ListNode::link(head, item, head->rightSib);
}



/**
 * Add an item to the end of the list
 *
 * @param item  the ListNode to add
 */
void List::addLast(ListNode* item)
{
    ListNode::link(tail->leftSib, item, tail);
}



/**
 * Remove first item from the list
 */
void List::removeFirst()
{
    ListNode::link(head, head->rightSib->rightSib);
}



/**
 * Remove last item from the list
 */
void List::removeLast()
{
    ListNode::link(tail->leftSib->leftSib, tail);
}



/**
 * Add an item to the end of the list
 *
 * @param item  the ListNode to add
 */
void List::add(ListNode* item)
{
    addLast(item);
}



/**
 * Search for an item and remove it from the list. Return true if successful.
 *
 * @param item  the ListNode to remove
 * @return true or false
 */
bool List::remove(ListNode* item)
{
    ListNode* node = head->rightSib;

    while (node != tail && node != item) {
        node = node->rightSib;
    }

    if (node == tail)
        return false;


    ListNode::link(node->leftSib, item, node->rightSib);

    return true;
}
