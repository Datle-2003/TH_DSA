#ifndef SPARE_TABLE_H
#define SPARE_TABLE_H

#include <cmath>
#include <cstring>
#include "FileProcessing.h"

using namespace std;
void buildSpareTable(vector<int> &nums, const char *filename, int type);
int typeOfTable(const char *type);
int query(int L, int R, const char *filename);
#endif