#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

#include <vector>
#include <string>

using namespace std;

vector<int> lzw_compress(string str);
string lzw_decompress(vector<int> compressValue);

#endif