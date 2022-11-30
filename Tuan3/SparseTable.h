#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <cmath>
#include <cstring>
#include "FileProcessing.h"

using namespace std;
void buildSparseTable(vector<int> &nums, const char *filename, int type);
int typeOfTable(const char *type);
int query(int L, int R, const char *filename);
#endif