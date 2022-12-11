#include "MinHeap.h"

void updateOrder(vector<Object> &Obj)
{
    for (int i = 0; i < Obj.size(); i++)
        Obj[i].Order = i;
}

bool isEmpty(vector<Object> &P)
{
    // return true if size = 0
    return P.size() == 0;
}

void UpdateQueue(vector<Object> &P, int l, int r)
{
    // add object
    int i = l, j = 2 * i + 1;
    while (j <= r)
    {
        if (j < r) // has element after position j
            // find the object has smaller value priority(means higher priotity)
            if (P[j].Priority > P[j + 1].Priority)
                j++;
        if (P[i].Priority <= P[j].Priority) // correct order
            break;
        std::swap(P[i], P[j]);
        // update index
        i = j;
        j = 2 * i + 1;
    }
    updateOrder(P);
}

Object Extract(vector<Object> &P)
{
    int size = P.size() - 1;
    Object temp = P[0];
    // put the most priority Object at the end of Queue
    swap(P[0], P[size]);
    P.pop_back();
    // resize queue
    size--;
    // update queue
    UpdateQueue(P, 0, size);
    updateOrder(P);
    return temp;
}

void PushObjectBack(vector<Object> &P, int index)
{

    int i = (index - 1) / 2;
    while (i >= 0)
    {
        if (index % 2 == 0 && index > 0)
            // find the object has higher priority
            if (P[index - 1].Priority < P[index].Priority)
                index--;
        if (P[index].Priority < P[i].Priority)
            std::swap(P[index], P[i]);
        index = i; // update index
        i = floor((i - 1) * 1.0 / 2);
    }
    // update order of queue
    updateOrder(P);
}

void Insert(vector<Object> &P, string ID, int Priority)
{
    P.push_back({ID, 0, Priority});
    int j = P.size() - 1;
    PushObjectBack(P, j); // update queue after push back new object
}

bool Remove(vector<Object> &P, string ID)
{
    int index = -1;
    // find object to be removed
    for (int i = 0; i < P.size(); i++)
        if (P[i].ID == ID)
        {
            index = i;
            break;
        }
    // not found
    if (index == -1)
        return false;

    std::swap(P[index], P[P.size() - 1]);
    P.pop_back();
    // add each element to queue
    for (int i = index; i < P.size() - 1; i++)
        PushObjectBack(P, i);

    return true;
}
bool changePriority(vector<Object> &P, string ID, int Priority)
{
    int index = -1;
    // find object to be changed priority
    for (int i = 0; i < P.size(); i++)
        if (P[i].ID == ID)
        {
            index = i;
            break;
        }

    // not found
    if (index == -1)
        return false;

    P[index].Priority = Priority;
    PushObjectBack(P, index);            // update the elements to the left of the changed object of the queue
    UpdateQueue(P, index, P.size() - 1); // update the elements to the right of the changed object
    return true;
}

istream &operator>>(istream &is, Object &Obj)
{
    std::cout << "ID = ";
    is >> Obj.ID;
    std::cout << "Priority = ";
    is >> Obj.Priority;
    return is;
}

ostream &operator<<(ostream &os, const vector<Object> &P)
{
    for (int i = 0; i < P.size(); i++)
        os << "ID = " << P[i].ID << "  "
           << "Order = " << P[i].Order << "  "
           << "Priority = " << P[i].Priority << '\t';
    os << '\n';
    return os;
}