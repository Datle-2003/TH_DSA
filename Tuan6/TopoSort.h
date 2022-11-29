#ifndef TOPO_SORT_H
#define TOPO_SORT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

struct trailer;

struct leader
{
    int key;
    int count;
    leader *next;
    trailer *trail;
};

struct trailer
{
    leader *id;
    trailer *next;
};

void TopoSort();
leader *addList(leader *&head, leader *&tail, int value, int &size);
void topoSort();
#endif