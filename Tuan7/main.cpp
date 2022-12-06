#include "trie.h"
#include <string>
#include <vector>

using namespace std;

int main(){
    // demo
    TrieNode* Dic = nullptr;
    string dicFile = "HW6-dic.txt";

    createTrie(Dic, dicFile);

    string word = "drastic";
    cout << "id of drastic in dic: " << lookUp(Dic, word) << "\n";

    vector<string> wordList = lookUpPrefix(Dic, "aar");
    cout << "Word list with 'aar' as prefix:\n";
    for(auto word: wordList)
        cout << word << "\n";

    Remove(Dic, "aaronite");
    Remove(Dic, "aarrghh");
    Remove(Dic, "aarrgh");
    
    vector<string> newWordList = lookUpPrefix(Dic, "aar");
    cout << "New word list with 'aar' as prefix:\n";
    for(auto word: newWordList)
        cout << word << "\n";
    
    removeTrie(Dic);// free memory
    
    return 0;
}