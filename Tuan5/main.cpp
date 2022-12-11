#include <iostream>
#include "LinkedList.h"
#include "MinHeap.h"

int main()
{
    // demo for linked-list
    Node *head = NULL;

    cout << "List is empty: " << isEmpty(head) << '\n';

    int Order = 0;
    Insert(head, "tom", Order++, 3);
    Insert(head, "jerry", Order++, 5);
    Insert(head, "mickey", Order++, 1);
    Insert(head, "donal", Order++, 2);

    cout << "List is empty: " << isEmpty(head) << '\n'; // check empty

    Remove(head, "mickey");

    Node *temp = Extract(head);
    cout << temp->ID << " " << temp->Order << " " << temp->Priority << '\n';

    changePriority(head, "tom", 1);

    temp = Extract(head);
    cout << temp->ID << " " << temp->Order << " " << temp->Priority << "\n\n";

    releaseList(head);

    // demo for minheap
    vector<Object> P;

    cout << "List is empty: " << isEmpty(P) << '\n';

    Order = 0;
    Insert(P, "tom", Order++, 3);
    Insert(P, "jerry", Order++, 5);
    Insert(P, "mickey", Order++, 1);
    Insert(P, "donal", Order++, 2);

    cout << "List is empty: " << isEmpty(P) << '\n';

    Remove(P, "mickey");

    Object tmp = Extract(P);
    cout << tmp.ID << " " << tmp.Order << " " << tmp.Priority << '\n';

    changePriority(P, "tom", 1);

    tmp = Extract(P);
    cout << tmp.ID << " " << tmp.Order << " " << tmp.Priority << '\n';

    return 0;
}
