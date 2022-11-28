#include "CircleLinkedList.h"
using namespace std;

int printMenu()
{
    cout << "1. Add head\n";
    cout << "2. Add tail\n";
    cout << "3. Remove head\n";
    cout << "4. Remove tail\n";
    cout << "5. Add after\n";
    cout << "6. Remove after\n";
    cout << "7. Print list\n";
    cout << "8. Exit\n";
    int n;
    cin >> n;
    return n;
}

int main()
{
    int x, y, n = 1;
    CNode *tail = NULL;

    while (n > 0 && n < 8)
    {
        n = printMenu();
        switch (n)
        {
        case 1:
            cin >> x;
            addHead(tail, x);
            cout << "Add head sucessful\n";
            break;
        case 2:
            cin >> x;
            addTail(tail, x);
            cout << "Add tail sucessful\n";
            break;
        case 3:
            removeHead(tail);
            cout << "Remove head sucessful\n";
            break;
        case 4:
            removeTail(tail);
            cout << "Remove tail sucessful\n";
            break;
        case 5:
        {
            cin >> x >> y;
            bool tmp = addAfter(tail, x, y);
            if (tmp)
                cout << "Add after sucessful\n";
            else
                cout << "Node is not found\n";
            break;
        }
        case 6:
        {
            cin >> y;
            bool tmp1 = removeAfter(tail, y);
            if (tmp1)
                cout << "Remove tail sucessful\n";
            else
                cout << "Node is not found\n";
            break;
        }
        case 7:
            printList(tail);
            cout << '\n';
            break;
        default:
            removeList(tail);
            cout << "Sucessful exit\n";
            break;
        }
    }

    return 0;
}