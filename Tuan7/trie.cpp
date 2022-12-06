#include "trie.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// auxiliary function
int pos(char c){
    return c - 'a';
}
char word(int pos){
    return 'a' + pos;
}


void Insert(TrieNode* &Dic, string word, int id){
    if(Dic == nullptr){
        Dic = new TrieNode;
        for(int i = 0; i < NUM_CHAR; i++)
            Dic->next[i] = nullptr;
        Dic->id = -1;
    }
    TrieNode* pTrie = Dic;
    for(int i = 0; i < word.size(); i++){
        // word has not present from the i-th character in the string
        if(pTrie->next[pos(word[i])] == nullptr){
            // create new node, move to new node and set nullptr to all its child node
            pTrie->next[pos(word[i])] = new TrieNode;
            pTrie = pTrie->next[pos(word[i])];
            pTrie->id = -1;// mark as not present
            for(int i = 0; i < NUM_CHAR; i++){
                pTrie->next[i] = nullptr;
            }
        }
        else{// word still present at the i-th character
            pTrie = pTrie->next[pos(word[i])];// move to new node
        }
    }
    pTrie->id = id;// only a node that is present is assigned value
}


void readFile(ifstream& ifs, string& word, int& id){
    string line;
    getline(ifs, line);
    // line has the form: number + ". " + word + "\r"
    // read id (from beginning of the string to before '.' char)
    if(line == "") return;// cannot read empty string
    line.pop_back();// remove /r
    int endOfNum = line.find('.');
    string id_str = line.substr(0, endOfNum);
    id = stoi(id_str);
    // read word (from next to the ws to before endline)
    int wordLen = line.size() - (endOfNum + 2);
    word = line.substr(endOfNum + 2, wordLen);
}
void createTrie(TrieNode* &Dic, string dicFile){
    ifstream ifs(dicFile);
    string word;
    int id;
    char c;
    if(!ifs){
        cerr << "Cannot read the dictionary file!\n";
        return;
    }
    while(!ifs.eof()){
        readFile(ifs, word, id);
        Insert(Dic, word, id);
    }
    ifs.close();
}


int lookUp(TrieNode* Dic, string word){
    TrieNode* pTrie = Dic;
    if(Dic == nullptr) return -1;
    for(int i = 0; i < word.size(); i++){
        if(pTrie->next[pos(word[i])] == nullptr)
            return -1;
        pTrie = pTrie->next[pos(word[i])]; 
    }
    return pTrie->id;
}


string extractWord(stack<char> s){
    string rev;
    while(!s.empty()){
        rev.push_back(s.top());
        s.pop();
    }
    string res;
    for(int i = rev.size() - 1; i >= 0; i--)
        res.push_back(rev[i]);
    return res;
}
// depth-first traversal function to collect all the words from the starting node
void df_collectWord(TrieNode* pTrie, stack<char>& s, vector<string>& wordList){
    if(pTrie->id != -1) // if this node is present, then the word in s is in dic
        wordList.push_back(extractWord(s));// push to word list
    for(int i = 0; i < NUM_CHAR; i++){
        if(pTrie->next[i] != nullptr){
            s.push(word(i));
            df_collectWord(pTrie->next[i], s, wordList);
            s.pop();
        }
    }
}
vector<string> lookUpPrefix(TrieNode* Dic, string prefix){
    vector<string> wordList;
    // look for the prefix node
    TrieNode* pTrie = Dic;
    for(int i = 0; i < prefix.size(); i++){
        if(pTrie->next[pos(prefix[i])] == nullptr)
            return wordList;// return empty list if not found the prefix
        pTrie = pTrie->next[pos(prefix[i])]; 
    }
    // extract desired list
    stack<char> s;
    for(int i = 0; i < prefix.size(); i++){
        s.push(prefix[i]);
    }
    df_collectWord(pTrie, s, wordList);
    return wordList;
}


void Remove(TrieNode* Dic, string word){
    // look for the node to remove
    TrieNode* pTrie = Dic;
    stack<TrieNode*> checkNode;// to trace the parent node for deletion
    stack<int> posNode;// marking the position to assign nullptr
    // -> checkNode.top is pointed by its parent at posNode.top
    checkNode.push(Dic);
    // find the word and trace
    for(int i = 0; i < word.size(); i++){
        if(pTrie->next[pos(word[i])] == nullptr)
            return;// not found the word
        posNode.push(pos(word[i]));// trace
        pTrie = pTrie->next[pos(word[i])];
        checkNode.push(pTrie);// trace
    }
    pTrie->id = -1;// in case not deleting node
    // check if the node before 'word' needed to delete 
    TrieNode* curNode = checkNode.top();
    checkNode.pop();
    while(!posNode.empty()){// until no need to check pos
        for(int i = 0; i < NUM_CHAR; i++){
            if(curNode->next[i] != nullptr)// node with prefix as 'word' still present in trie 
                return;// therefore, no need to delete the node
        }
        // delete the current checking node and all its parent node if needed
        delete curNode;// current node deleted
        curNode = checkNode.top();// go to the parent node
        checkNode.pop();
        curNode->next[posNode.top()] = nullptr;// assign nullptr for deleted node
        posNode.pop();
        // return the loop for the parent node, parent node is deleted 
        // when all of its child were deleted
    }
}

void removeTrie(TrieNode* &Dic){
    if(Dic == nullptr) return;
    for(int i = 0; i < NUM_CHAR; i++){
        removeTrie(Dic->next[i]);
    }
    delete Dic;
    Dic = nullptr;
}