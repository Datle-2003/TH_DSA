#ifndef SEARCHING_H
#define SEARCHING_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iomanip>

#define MAX_TEXT_LENGTH 100000
#define TABLE_LENGTH 256


using namespace std;
using namespace std::chrono;

int typeOfSearching(char *name);
void Search(const char *filename, char *pattern, int type);

#endif