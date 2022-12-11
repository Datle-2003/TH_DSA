#include "LinkedList.h"

// convention: The smaller the element, the higher the priority

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
    // list is empty
    if (head == NULL)
    {
        head = create(ID, Order, Priority);
        return;
    }
    // new node has greater priority
    if (head->Priority > Priority)
    {
        Node *tmp = create(ID, Order, Priority);
        tmp->next = head;
        head = tmp;
        return;
    }

    Node *t1 = head;
    Node *t2 = head->next;
    // loop to find correct position of new node
    // t1 -> new node -> t2
    while (t2 && t2->Priority < Priority)
    {
        t1 = t1->next;
        t2 = t2->next;
    }
    // add new node between t1 and t2
    Node *temp = create(ID, Order, Priority);
    t1->next = temp;
    temp->next = t2;
}

Node *Extract(Node *&head)
{
    if (head == NULL)
        return NULL;
    // save the node that needs to be returned
    Node *p1 = create(head->ID, head->Order, head->Priority);
    Node *p2 = head;
    // update head
    head = head->next;
    delete p2;
    return p1;
}

bool Remove(Node *&head, string ID)
{
    // list is empty
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
    // find node to be removed
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
    // not found node to be removed
    if (!isFound)
        return false;
    // p is the node to be removed
    // delete p
    q->next = p->next;
    delete p;
    return true;
}
bool changePriority(Node *&head, string ID, int Priority)
{
    // list is empty
    if (head == NULL)
        return false;
    // change head
    if (head->ID == ID)
    {
        int Order = head->Order;
        Extract(head);
        Insert(head, ID, Order, Priority);
        return true;
    }
    bool isFound = false;
    Node *p = head->next;
    Node *q = head;
    // find the node to be changed priority
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
    // not found
    if (!isFound)
        return false;
    // delete old node and add new node
    q->next = p->next;
    int Order = p->Order;
    delete p;
    Insert(head, ID, Order, Priority);
    return true;
}

// free memory
void releaseList(Node *&head)
{
    Node *tmp = head;
    while (head)
    {
        head = head->next;
        delete tmp;
    }
}

// void print(Node *&head)
// {
//     for (Node *p = head; p; p = p->next)
//         std::cout << p->Priority << " ";
//     std::cout << '\n';
// }