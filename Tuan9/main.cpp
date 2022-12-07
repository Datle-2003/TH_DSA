#include <iostream>
#include <vector>
#include <string>
#include "lzw_compression.h"

using namespace std;

int main(){
    string str = "WYS*WYSWYG*WYSWYSG";
    // 97 98 256 97 256
    // ab: 256, ba: 257, aa: 258 
    vector<int> compressList = lzw_compress(str);
    cout << "List after compression: ";
    for(int num: compressList){
        cout << num << " ";
    }
    cout << "\n";
    cout << "String after decompression: ";
    cout << lzw_decompress(compressList) << "\n";
    
    return 0;
}