#include <iostream>
#include "LinkedList.h"
#include "MinHeap.h"

int main()
{
    vector<Object> P;
    int n;
    cin >> n;
    while (n--)
    {

        Object O1;
        cin >> O1;
        P.push_back(O1);
    }
    
    // void Insert(vector<Object> & P, string ID, int Order, int Priority);
    // bool Remove(vector<Object> & P, string ID);
    // bool changePriority(vector<Object> & P, string ID, int priority);
    // istream &operator>>(istream &is, Object &Obj);
    // ostream &operator<<(ostream &os, const vector<Object> &P);
    return 0;
}
