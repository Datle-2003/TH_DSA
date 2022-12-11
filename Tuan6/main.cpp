#include "TopoSort.h"
#include "RadixSort.h"
using namespace std;

void printMenu()
{
    cout << "1. Topological sort\n";
    cout << "2. Radix sort\n";
}

int main()
{

    cout << "Please make sure that input.txt contains the correct structure for the algorithm you want to process\n";
    int choice = 0;
    printMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        TopoSort();
        break;
    case 2:
        RadixSort();
        break;
    default:
        cerr << "Error\n";
        break;
    }
    return 0;
}