#include "SparseTable.h"

void Processing(int argc, char **argv)
{
    string type = argv[1];
    if (type == "make")
    {
        // read array
        vector<int> nums;
        for (int i = 4; i < argc; i++)
            nums.push_back(atoi(argv[i]));
        int type = typeOfTable(argv[3]);
        const char *filename = argv[2];
        buildSparseTable(nums, filename, type);
    }
    if (type == "query")
    {
        int L = atoi(argv[3]);
        int R = atoi(argv[4]);
        const char *filename = argv[2];
        std::cout << query(L, R, filename) << "\n";
    }
}

int main(int argc, char **argv)
{
    Processing(argc, argv);
    return 0;
}