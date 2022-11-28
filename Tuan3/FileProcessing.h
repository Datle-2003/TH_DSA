#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

vector<vector<int>> readFile(const char *);
void writeToFile(vector<vector<int>> &, const char *);
void printToConsole(vector<vector<int>> &);
#endif