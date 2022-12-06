#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define NUM_CHAR 26
struct TrieNode{
    int id;
    TrieNode* next[NUM_CHAR];
};

int pos(char c);
char word(int pos);

void Insert(TrieNode* &Dic, string word, int id);

void readFile(ifstream& ifs, string& word, int& id);
void createTrie(TrieNode* &Dic, string dicFile);

int lookUp(TrieNode* Dic, string word);

string extractWord(stack<char> s);
void df_collectWord(TrieNode* pTrie, stack<char>& s, vector<string>& wordList);
vector<string> lookUpPrefix(TrieNode* Dic, string prefix);

void Remove(TrieNode* Dic, string word);
void removeTrie(TrieNode* &Dic);
#endif