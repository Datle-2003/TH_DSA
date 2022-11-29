#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

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

Ref *createRef(int value)
{
    Ref *p = new Ref;
    p->next = nullptr;
    p->key = value;
    return p;
}

void addRef(Bucket *current, int value)
{
    if (current->head == nullptr) // add head
    {
        current->head = createRef(value);
        return;
    }
    Ref *temp = current->head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = createRef(value);
}

Bucket *createBucket(int key, int value)
{
    Bucket *q = new Bucket;
    q->key = key;
    q->next = nullptr;
    addRef(q, value);
    return q;
}

void addBucket(Bucket *head, Bucket *tail, int key, int value)
{

    if (head == tail)
    {
        head = createBucket(key, value);
        tail = head;
        return;
    }
    Bucket *p1 = head;
    Bucket *p2 = head->next;

    while (p2 && p2->key <= key)
    {
        p1 = p1->next;
        p2 = p2->next;
    }

    // the last bucket
    if (p2 == tail)
    {
        p2->next = createBucket(key, value);
        tail = tail->next;
        return;
    }

    // key has already in multiple linked list
    if (p1->key == key)
    {
        addRef(p1, value);
        return;
    }

    // key is not exist
    Bucket *temp = createBucket(key, value);
    temp->next = p2;
    p1->next = temp;
}

void radixSort()
{
    Bucket *head, *tail = nullptr;
    
}

#endif