#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Ref
{
    int key;
    Ref *next;
};

struct Bucket
{
    int key;
    Bucket *next;
    Ref *head;
};

Ref *createRef(int value);
void addRef(Bucket *current, int value);
Bucket *createBucket(int key, int value);
void addBucket(Bucket *head, Bucket *tail, int key, int value);
int getDigits(int num);
void radixSort(vector<int> &nums, int k);

#endif