#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

#include <vector>
#include <string>

using namespace std;

// compress and decompress
vector<int> lzw_compress(string str);
string lzw_decompress(vector<int> compressValue);
// calculate ratio
double compressRatio(string str, vector<int> compressList);

// auxiliary function
bool readArgs(string &str, vector<int>& compressionList, string &mode, int argc, char** argv);
void printBinary(int num);
void printBinaryList(vector<int> compressionList);

#endif