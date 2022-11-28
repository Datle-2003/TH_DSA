#ifndef SEARCHING_H
#define SEARCHING_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <cstring>

#define MAX_TEXT_LENGTH 1000
#define TABLE_LENGTH 256


using namespace std;
using namespace std::chrono;

int typeOfSearching(char *name);
void Search(const char *filename, char *pattern, int type);

#endif