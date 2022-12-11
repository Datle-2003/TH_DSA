#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<int> lzw_compress(string str)
{
    vector<int> compressValue;
    map<string, int> compressTable;
    // build the 8-bit character table
    for (int i = 0; i < 256; i++)
    {
        compressTable[string(1, char(i))] = i;
    }
    int count = 256;
    string cur; // current checking substring in 'str'
    char adder; // additional char to extend the substr
    int j;
    for (int i = 0; i < str.size() - 1; i++)
    {
        cur = str[i];
        j = i + 1;
        while (true)
        {
            adder = str[j++];
            if (compressTable.find(cur + adder) == compressTable.end())
            {
                // not found, add the current string and push cur + adder
                compressValue.push_back(compressTable[cur]);
                compressTable[cur + adder] = count++;
                break;
            }
            // found, update cur, go back to the loop and continue to check
            cur += adder;
            if (j == str.size())
            { // break if string go to the end
                compressValue.push_back(compressTable[cur]);
                return compressValue; // has reached the end of string
            }
        }
        i = j - 2; // jump to next character
    }
    compressValue.push_back(int(str[str.size() - 1])); // push last character
    return compressValue;
}

string lzw_decompress(vector<int> compressValue)
{
    string str;
    map<int, string> decompressTable; // using map to store representing value
    // build the 8-bit character table
    for (int i = 0; i < 256; i++)
    {
        decompressTable[i] = string(1, char(i));
    }
    int count = 256;
    int j;
    for (int i = 0; i < compressValue.size(); i++)
    {
        j = i + 1;
        if (decompressTable.find(compressValue[i]) != decompressTable.end())
        { // found
            str += decompressTable[compressValue[i]];
            if (compressValue[i] >= 256) // multiple chars
                // update table with prev char if value represents multiple chars
                decompressTable[count++] = decompressTable[compressValue[i - 1]] + decompressTable[compressValue[i]].front();
            if (j < compressValue.size() && compressValue[j] < 256)
                // update table if next value represents single char
                decompressTable[count++] = decompressTable[compressValue[i]] + char(compressValue[j]);
        }
        else
        { // not found, in case string like 'aaaaaa...' happens (87 256 257 ...)
            // count = compressValue[i], update the decompress table
            decompressTable[count++] = decompressTable[compressValue[i - 1]] + decompressTable[compressValue[i - 1]].front();
            str += decompressTable[compressValue[i]]; // then add to str the newly update value
        }
    }
    return str;
}
double compressRatio(string str, vector<int> compressList)
{
    // N - n: number of bits before and after compression
    int N = str.length() * 8; // before compression
    int n = 0;
    int divider = 256; // number of possible value stored in 1 byte
    for (int val : compressList)
        n += (val / divider) + 8; // get number of bits needed to store val
    return (double(N - n) / N) * 100;
}

int readArgs(string &str, vector<int> &compressionList, string &mode, int argc, char **argv)
{
    // return -1 if decompress, 1 if compress, 0 if error
    if (argc < 3)
        return 0;
    mode = argv[1];
    if (mode == "-c")
        if (argc == 3)
        {
            str = argv[2];
            return 1;
        }
        else
            return 0;
    else if (mode == "-e")
    {
        for (int i = 2; i < argc; i++)
            compressionList.push_back(stoi(string(argv[i])));
        return -1;
    }
    else
        return 0;
}

void printBinary(int num)
{
    string str;
    while (num != 0)
    {
        str.push_back((num % 2) + '0');
        num /= 2;
    }
    while (str.size() < 8)
    {
        str.push_back('0'); // '0' till enough 8 bytes
    }
    for (int i = str.size() - 1; i >= 0; i--)
        cout << str[i]; // reversed str is the desired bit list
    return;
}
void printBinaryList(vector<int> compressionList)
{
    for (int num : compressionList)
    {
        printBinary(num);
        cout << " ";
    }
}