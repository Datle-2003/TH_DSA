#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
using std::string;

struct Node
{
    string ID;
    int Order;
    int Priority;
    Node *next;
};

bool isEmpty(Node *&head);
void Insert(Node *&head, string ID, int Order, int Priority);
Node *Extract(Node *&head);
bool Remove(Node *&head, string ID);
bool changePriority(Node *&head, string ID, int Priority);
void releaseList(Node *&head);
#endif