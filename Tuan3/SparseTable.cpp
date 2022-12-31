#include "SparseTable.h"

typedef int (*condition)(int, int);

int findMax(int a, int b)
{
    return a > b ? a : b;
}

int findMin(int a, int b)
{
    return a < b ? a : b;
}

int findGCD(int a, int b)
{
    a = abs(a);
    b = abs(b);
    if (b == 0)
        return a;
    return findGCD(b, a % b);
}




void buildSparseTable(vector<int> &nums, const char *tablename, string type, const char* filename)
{
    SparseTable ST;
    ST.type = type;
    ST.name = tablename;
    int n = nums.size();
    int (*condition)(int, int);
    int tp = typeOfTable(type);
    if (tp == 1)
        condition = findMin;
    else if (tp == 2)
        condition = findMax;
    else
        condition = findGCD;
    // table has n row
    ST.table.resize(n);

    // build sparse table

    // for the first col
    // min, max, gcd of single element is element itself
    for (int i = 0; i < n; i++)
        ST.table[i].push_back(nums[i]);

    // for the others col
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            int tmp = condition(ST.table[i][j - 1], ST.table[i + (1 << (j - 1))][j - 1]);
            ST.table[i].push_back(tmp);
        }
    }
    // save the table to file and print to the console
    writeToFile(ST, filename);
    printToConsole(ST);
}

// 1 - MIN
// 2 - MAX
// 3 - GCD
int typeOfTable(string type)
{
    if (type == "MIN")
        return 1;
    if (type == "MAX")
        return 2;
    if (type == "GCD")
        return 3;
    return 0;
}

int query(int L, int R, const char *filename)
{
    vector<vector<int>> table;
    string type = "";
    table = readFile(filename, type);
    // split [L, R] into 2 segments, each segment has 2 ^ j elements
    int j = log2(R - L + 1);
    // get type of sparse table(min, max, gcd)
    if (type == "MIN")
        return findMin(table[R - (1 << j) + 1][j], table[L][j]);

    if (type == "MAX")
        return findMax(table[R - (1 << j) + 1][j], table[L][j]);

    return findGCD(table[R - (1 << j) + 1][j], table[L][j]);
}
