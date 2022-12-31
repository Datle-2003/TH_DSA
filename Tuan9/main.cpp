#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lzw_compression.h"

using namespace std;

// command args for compression: exe_file "-c" string
// command args for decompression: exe_file "-e" num_list
int main(int argc, char **argv)
{
    string str;
    vector<int> list;
    string mode;
    // determine compress mode
    int compressionMode = readArgs(str, list, mode, argc, argv);
    if (!compressionMode)
    {
        cerr << "Wrong argument!\n";
        return 0;
    }
    if (compressionMode == 1)
    {
        // compress
        list = lzw_compress(str);
        // print result
        for (int num : list)
        {
            cout << num << " ";
        }
        cout << "\n";
        printBinaryList(list);
        cout << "\n";
        cout << fixed << setprecision(2) << compressRatio(str, list) << "\n";
    }
    else
    {
        // decompress
        str = lzw_decompress(list);
        // print result
        cout << str << "\n";
        cout << fixed << setprecision(2) << compressRatio(str, list) << "\n";
    }
    return 0;
}