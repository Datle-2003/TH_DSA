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

void buildSparseTable(vector<int> &nums, const char *filename, int type)
{
    int n = nums.size();
    int (*condition)(int, int);
    if (type == 1)
        condition = findMin;
    else if (type == 2)
        condition = findMax;
    else
        condition = findGCD;
    vector<vector<int>> table;
    // table has n row
    table.resize(n);

    // build 
    // first col
    for (int i = 0; i < n; i++)
        table[i].push_back(nums[i]);

    // others col
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            int tmp = condition(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            table[i].push_back(tmp);
        }
    }
    writeToFile(table, filename);
    printToConsole(table);
}

// 1 - MIN
// 2 - MAX
// 3 - GCD
int typeOfTable(const char *type)
{
    if (strcmp(type, "MIN") == 0)
        return 1;
    if (strcmp(type, "MAX") == 0)
        return 2;
    if (strcmp(type, "GCD") == 0)
        return 3;
    return 0;
}

int query(int L, int R, const char *filename)
{
    vector<vector<int>> table;
    table = readFile(filename);
    int j = log2(R - L + 1);
    
    if (table[0][1] == findMin(table[0][0], table[1][0]))
        return findMin(table[R - (1 << j) + 1][j], table[L][j]);

    if (table[0][1] == findMax(table[0][0], table[1][0]))
        return findMax(table[R - (1 << j) + 1][j], table[L][j]);

    return findGCD(table[R - (1 << j) + 1][j], table[L][j]);
}
