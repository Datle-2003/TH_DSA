#include <iostream>

using namespace std;

int interpolationSearch(int *arr, int n, int val, int &countCycle);

int main(int argc, char **argv)
{
    // check args
    if (argc <= 2)
    {
        cerr << "Not enough arg!\n";
        return 1;
    }
    int n = argc - 2;
    int countCycle;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = atoi(argv[i + 2]);
    }
    cout << interpolationSearch(arr, n, atoi(argv[1]), countCycle); // start from 1
    cout << " - " << countCycle << "\n";
    delete[] arr;
    return 0;
}

int interpolationSearch(int *arr, int n, int val, int &countCycle)
{
    int l = 0;
    int r = n - 1;
    int searchPos;
    countCycle = 0;
    while (l < r)
    {
        countCycle++;
        // find the interpolated position
        searchPos = (val - arr[l]) * (r - l) / (arr[r] - arr[l]) + l;
        if (arr[searchPos] == val)
            return searchPos + 1;
        // update the range of searching
        if (arr[searchPos] > val)
        {
            r = searchPos - 1;
        }
        else
            l = searchPos + 1;
    }
    if (l == r && val == arr[l])
        return l + 1;
    return -1; // not found
}