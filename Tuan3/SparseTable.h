#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <cmath>
#include <cstring>
#include "FileProcessing.h"

using namespace std;
struct SparseTable
{
    vector<vector<int>> table;
    string name;
    string type;
};

void buildSparseTable(vector<int> &nums, const char *tablename, string type);
int typeOfTable(string type);
int query(int L, int R, const char *filename);
#endif