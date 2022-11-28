#include "LinkedList.h"

void updateOrder(Node *&head)
{
    int i = 0;
    for (Node *p = head; p; p = p->next)
    {
        p->Order = i;
        i++;
    }
}

Node *create(string ID, int Order, int Priority)
{
    Node *newNode = new Node;
    newNode->ID = ID;
    newNode->Priority = Priority;
    newNode->Order = Order;
    newNode->next = NULL;
    return newNode;
}

bool isEmpty(Node *&head)
{
    return head == NULL;
}

void Insert(Node *&head, string ID, int Order, int Priority)
{
    if (head == NULL)
    {
        head = create(ID, Order, Priority);
        return;
    }
    if (head->Priority > Priority)
    {
        Node *tmp = create(ID, Order, Priority);
        tmp->next = head;
        head = tmp;
        return;
    }
    Node *t1 = head;
    Node *t2 = head->next;
    while (t2 && t2->Priority < Priority)
    {
        t1 = t1->next;
        t2 = t2->next;
    }
    Node *temp = create(ID, Order, Priority);
    t1->next = temp;
    temp->next = t2;
}

Node *Extract(Node *&head)
{
    if (head == NULL)
        return NULL;

    Node *p1 = create(head->ID, head->Order, head->Priority);
    Node *p2 = head;
    head = head->next;
    delete p2;
    return p1;
}

bool Remove(Node *&head, string ID)
{
    if (head == NULL)
        return false;
    // remove head
    if (head->ID == ID)
    {
        Extract(head);
        return true;
    }
    bool isFound = false;
    Node *p = head->next;
    Node *q = head;
    // head is already check
    while (p)
    {
        if (p->ID == ID)
        {
            isFound = true;
            break;
        }
        q = q->next;
        p = p->next;
    }

    if (!isFound)
        return false;

    q->next = p->next;
    delete p;
    return true;
}
bool changePriority(Node *&head, string ID, int Priority)
{
    if (head == NULL)
        return false;
    bool isFound = false;
    Node *p = head->next;
    Node *q = head;
    // head is already check
    while (p)
    {
        if (p->ID == ID)
        {
            isFound = true;
            break;
        }
        q = q->next;
        p = p->next;
    }
    if (!isFound)
        return false;
    int tmp = p->Order;
    q->next = p->next;
    delete p;
    Insert(head, ID, tmp, Priority);
    return true;
}

void releaseList(Node *&head)
{
    Node *tmp = head;
    while(head)
    {
        head = head ->next;
        delete tmp;
    }
}

void print(Node *&head)
{
    for (Node *p = head; p; p = p->next)
        std::cout << p->Priority << " ";
    std::cout << '\n';
}