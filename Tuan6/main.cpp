#include <iostream>

using namespace std;

struct Ref
{
    int key;
    Ref *next;
};

// multiple linked list
struct Bucket
{
    int key;
    Bucket *next;
    Ref *head;
};

// create Ref
Ref *createRef(int key)
{
    Ref *p = new Ref();
    p->next = nullptr;
    p->key = key;
    return p;
}

// add Ref in linkedlist
void addRef(Bucket *current, int key)
{
    if (current->head == nullptr) // add head
    {
        current->head = createRef(key);
        return;
    }
    Ref *p = nullptr;
    for (p = current->head; p; p = p->next)
        ;
    p->next = createRef(key);
}

Bucket *createBucket(int key)
{
    Bucket *q = new Bucket();
    q->key = key;
    q->next = nullptr;
    q->head = nullptr;
}

void addBucket(Bucket *head, Bucket *tail, int key, int value)
{

    if (head == tail)
    {
        head = createBucket(key);
        tail = head;
        head->head = createRef(value);
        return;
    }
    Bucket *p1 = head;
    Bucket *p2 = head->next;

    while (p2 && p2->key <= key)
        p2 = p2->next;

    // the last bucket
    if (p2 == tail)
    {
        p2->next = createBucket(key);
        tail = tail->next;
        p2->head = createRef(value);
        return;
    }
    // key has already in multiple linked list

    if (p2->key == key)
    {
    }
}

void radixSort()
{
    Bucket *head = nullptr;
    Bucket *tail = nullptr;
}

int main()
{

    return 0;
}