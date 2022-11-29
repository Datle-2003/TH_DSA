#include "TopoSort.h"

void readFile(vector<pair<int, int>> &P)
{
    char tmp;
    fstream f("input.txt", ios::in);
    while (f >> tmp)
    {
        int a, b;
        f >> a >> tmp >> b >> tmp;
        P.push_back({a, b});
    }
}

void topoSort()
{
    leader *head = new leader;
    leader *tail = head;
    int size = 0;
    vector<pair<int, int>> nums;
    readFile(nums);
    for (int i = 0; i < nums.size(); i++)
    {
        leader *p = addList(head, tail, nums[i].first, size);
        leader *q = addList(head, tail, nums[i].second, size);

        trailer *t = new trailer;
        t->id = q;
        t->next = p->trail;
        p->trail = t;
        q->count++;
    }

    leader *p = head;
    head = NULL;
    while (p != tail)
    {
        leader *q = p;
        p = p->next;
        if (q->count == 0)
        {
            q->next = head;
            head = q;
        }
    }

    leader *q = head;
    while (q)
    {
        cout << q->key << " ";
        size--;
        trailer *t = q->trail;
        q = q->next;
        while (t)
        {
            leader *p = t->id;
            p->count--;
            if (p->count == 0)
            {
                p->next = q;
                q = p;
            }
            t = t->next;
        }
    }

    
}

leader *addList(leader *&head, leader *&tail, int value, int &size)
{
    leader *h = head;
    tail->key = value;
    while (h->key != value)
        h = h->next;
    if (h == tail)
    {
        tail = new leader;
        size++;
        h->count = 0;
        h->trail = NULL;
        h->next = tail;
    }
    return h;
}