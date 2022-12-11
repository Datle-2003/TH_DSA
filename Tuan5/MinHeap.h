#ifndef MINHEAP_H
#define MINHEAP_H
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

struct Object
{
    string ID;
    int Order;
    int Priority;
};

bool isEmpty(vector<Object> &P);
Object Extract(vector<Object> &P);
void Insert(vector<Object> &P, string ID, int Order, int Priority);
bool Remove(vector<Object> &P, string ID);
bool changePriority(vector<Object> &P, string ID, int priority);
istream &operator>>(istream &is, Object &Obj);
ostream &operator<<(ostream &os, const vector<Object> &P);

#endif
