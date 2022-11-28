#include "CircleLinkedList.h"

CNode *createNode(int key)
{
    CNode *p = new CNode;
    p->key = key;
    p->next = p;
    return p;
}

void addHead(CNode *&tail, int key)
{
    // if list is empty
    if (tail == NULL)
    {
        tail = createNode(key);
        return;
    }

    CNode *newNode = createNode(key);
    // newNode point to head
    newNode->next = tail->next;
    // make newNode as head
    tail->next = newNode;
}

void addTail(CNode *&tail, int key)
{
    // if list is empty
    if (tail == NULL)
    {
        tail = createNode(key);
        return;
    }

    CNode *newNode = createNode(key);
    // newNode point to head
    newNode->next = tail->next;
    // tail point to newNode
    tail->next = newNode;
    // make newNode as tail
    tail = newNode;
}

void removeHead(CNode *&tail)
{
    // if list is empty
    if (tail == NULL)
        return;

    // if list has only one node
    if (tail->next == tail)
    {
        delete tail;
        tail = NULL;
        return;
    }
    CNode *head = tail->next;
    // tail point to new head
    tail->next = head->next;
    // delete old head
    delete head;
}

void removeTail(CNode *&tail)
{
    // if list is empty
    if (tail == NULL)
        return;

    // if list has only one node
    if (tail->next == tail)
    {
        delete tail;
        tail = NULL;
        return;
    }
    CNode *temp = tail;
    // find the node before tail
    while (temp->next != tail)
        temp = temp->next;
    // make temp as new tail
    temp->next = tail->next;
    delete tail;
    tail = temp;
}

void addAfter(CNode *&pos, int key) // add node after node
{
    // if list is empty
    if (pos == NULL)
    {
        pos = createNode(key);
        return;
    }
    // create new node
    CNode *temp = createNode(key);
    // make new node point to next of pos
    temp->next = pos->next;
    // make pos point to new node
    pos->next = temp;
}

bool addAfter(CNode *&tail, int keyBefore, int keyAfter)
// keyAfter is key to be added
{
    // if list is empty
    if (tail == NULL)
        return false;
    // if node to be added is after head
    CNode *p1 = tail;
    if (tail->key == keyBefore)
    {
        delete tail;
        tail = NULL;
        return true;
    }
    // find the node p1 has key = keyBefore
    do
    {
        p1 = p1->next;
    } while ((p1 != tail) && p1->key != keyBefore);
    // if p1 is not exist
    if (p1 == tail)
        return false;
    // add new node has key equals keyAfter after p1
    addAfter(p1, keyAfter);
    return true;
}

void removeAfter(CNode *&tail, CNode *&pos)
{
    // if list is empty
    if (pos == NULL)
        return;
    // if list has only one node
    if (pos->next == pos)
    {
        delete pos;
        pos = NULL;
        return;
    }
    // remove tail
    if (pos->next == tail)
    {
        removeTail(tail);
        return;
    }
    // assign node temp to node after pos
    CNode *temp = pos->next;
    // pos point to node after temp
    pos->next = temp->next;
    // delete temp
    delete temp;
}

bool removeAfter(CNode *&tail, int key)
{
    // if list is empty
    if (tail == NULL)
        return false;
    // if node to be removed is tail
    CNode *p1 = tail;
    if (tail->key == key)
    {
        removeTail(tail);
        return true;
    }
    // find node p1 has key equals key
    do
    {
        p1 = p1->next;
    } while ((p1 != tail) && p1->key != key);
    // if p1 is not exist
    if (p1 == tail)
        return false;
    // remove node after p1
    removeAfter(tail, p1);
    return true;
}

void printList(CNode *&tail)
{
    // if list is empty
    if (tail == NULL)
    {
        std::cout << "List is empty!\n";
        return;
    }
    std::cout << "the element(s) of the list: ";

    // traversal
    CNode *p = tail->next;
    do
    {
        std::cout << p->key << " ";
        p = p->next;
    } while (p != tail->next);
}

void removeList(CNode *&tail)
{
    // if list is empty
    if (tail == NULL)
        return;
    // delete nodes expected for tail
    CNode *p = tail->next;
    while (tail->next != tail)
    {
        tail->next = p->next;
        delete p;
    }
    // delete tail
    delete tail;
    tail = NULL;
}
