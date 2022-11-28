#ifndef CIRCLE_LINKED_LIST_H
#define CIRCLE_LINKED_LIST_H

#include "Node.h"
#include <iostream>

CNode *createNode(int key);
void addHead(CNode *&tail, int key);
void addTail(CNode *&tail, int key);
void removeHead(CNode *&tail);
void removeTail(CNode *&tail);
void addAfter(CNode *&pos, int key);
bool addAfter(CNode *&tail, int keyBefore, int keyAfter);
void removeAfter(CNode *&tail, CNode *&pos);
bool removeAfter(CNode *&tail, int key);
void printList(CNode *&tail);
void removeList(CNode *&tail);

#endif