#include "RadixSort.h"


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

int getDigits(int num)
{
    int count = 0;
    while (num)
    {
        count++;
        num /= 10;
    }
    return count;
}

void radixSort(vector<int> &nums, int k)
{
    Bucket *head, *tail = nullptr;

    int max = *std::max(nums.begin(), nums.end());
    int n = getDigits(max);
    int tmp = 1;
    int cnt = 0;
    for (int i = 0; i < ceil(n / k); i++)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            // calculate key
            int key = nums[i] % int(pow(10, tmp * k)) / pow(10, (tmp - 1) * k);
            addBucket(head, tail, key, nums[i]);
        }
        Bucket *p = head;
        while (p)
        {
            Ref *temp = head->head;
            while (temp)
            {
                nums[cnt++] = temp->key;
                head->head = head->head->next;
                delete temp;
                temp = head->head;
            }
            head = head->next;
            delete p;
            p = head;
        }
    }
}