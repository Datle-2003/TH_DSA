#include "TopoSort.h"

void readFile(vector<pair<int, int>> &P)
{
    char tmp;
    fstream f("input.txt", ios::in);
    if (!f)
    {
        cerr << "Can't open this file";
        exit(1);
    }
    while (f >> tmp)
    {
        int a, b;
        f >> a >> tmp >> b >> tmp;
        P.push_back({a, b});
    }
}

void TopoSort()
{
    // create head and tail
    leader *head = new leader;
    leader *tail = head;
    int size = 0; // size of leader-list
    vector<pair<int, int>> nums;
    readFile(nums);
    for (int i = 0; i < nums.size(); i++)
    {
        // add each pair <int, int> to leader-list
        leader *p = addList(head, tail, nums[i].first, size);
        leader *q = addList(head, tail, nums[i].second, size);

        trailer *t = new trailer; // manage the nodes behind the current node
        t->id = q;
        // add node to trailer
        t->next = p->trail;
        p->trail = t;
        // numbers of node before current node
        q->count++;
    }

    // find nodes has 0 node before and put them up to the top of linked-list
    leader *p = head;
    head = NULL;
    while (p != tail)
    {
        leader *q = p;
        p = p->next;
        if (q->count == 0) // current node doesn't have any node before
        {
            q->next = head;
            head = q;
        }
    }

    // print
    leader *q = head;
    while (q)
    {
        cout << q->key << " "; // print current node
        size--;
        trailer *t = q->trail; // traversal nodes after current node and decrease count atribute by one
        q = q->next;
        while (t)
        {
            leader *p = t->id;
            p->count--;
            if (p->count == 0) // current node doesn't have any node before
            {
                p->next = q;
                q = p;
            }
            t = t->next;
        }
    }

    // free memory
    q = head;
    while (q)
    {
        trailer *t = q->trail;
        while (t)
        {
            q->trail = q->trail->next;
            delete t;
            t = q->trail;
        }
        head = head->next;
        delete q;
        q = head;
    }

    delete tail;
}

leader *addList(leader *&head, leader *&tail, int value, int &size)
{
    leader *h = head;
    tail->key = value;

    while (h->key != value)
        h = h->next;
    // if value is already exist, do nothing
    // else assign new leader to tail and create new tail
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