#include <vector>
#include <string>
#include <map>

using namespace std;

vector<int> lzw_compress(string str){
    vector<int> compressValue;
    map<string, int> compressTable;
    // build the 8-bit character table
    for(int i = 0; i < 256; i++){
        compressTable[string(1, char(i))] = i;
    }
    int count = 256;
    string cur;
    char adder;
    int j;
    for(int i = 0; i < str.size() - 1; i++){
        cur = str[i];
        j = i + 1;
        while(true){
            adder = str[j++];
            if(compressTable.find(cur + adder) == compressTable.end()){
                // not found, add the current string and push cur + adder
                compressValue.push_back(compressTable[cur]);
                compressTable[cur + adder] = count++;
                break;
            }
            // found, update cur, go back to the loop and continue to check
            cur += adder;
            if(j == str.size()){// break if string go to the end
                compressValue.push_back(compressTable[cur]);
                return compressValue;// has reached the end of string
            }
        }
        i = j - 2;
    }
    compressValue.push_back(int(str[str.size() - 1]));// push last character
    return compressValue;
}

string lzw_decompress(vector<int> compressValue){
    string str;
    map<int, string> decompressTable;
    // build the 8-bit character table
    for(int i = 0; i < 256; i++){
        decompressTable[i] = string(1, char(i));
    }
    int count = 256;
    int j;
    for(int i = 0; i < compressValue.size(); i++){
        j = i + 1;
        if(decompressTable.find(compressValue[i]) != decompressTable.end()){// found
            str += decompressTable[compressValue[i]];
            if(compressValue[i] >= 256)// multiple chars
                // update table with prev char if value represents multiple chars
                decompressTable[count++] = decompressTable[compressValue[i - 1]] + decompressTable[compressValue[i]].front();
            if(j < compressValue.size() && compressValue[j] < 256)
                // update table if next value represents single char
                decompressTable[count++] = decompressTable[compressValue[i]] + char(compressValue[j]);

        }
        else{// not found, in case string like 'aaaaaa...' happens (87 256 257 ...)
            // count = compressValue[i], update the decompress table
            decompressTable[count++] = decompressTable[compressValue[i - 1]] + decompressTable[compressValue[i - 1]].front(); 
            str += decompressTable[compressValue[i]];// then add to str the newly update value
        }
    }
    return str;
}