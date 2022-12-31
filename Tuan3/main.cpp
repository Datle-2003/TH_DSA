#include "SparseTable.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        cerr << "Error!\n";
        return 1;
    }
    string type = argv[1];
    if (type == "make")
    {
        // read array
        vector<int> nums;
        for (int i = 4; i < argc; i++)
            nums.push_back(atoi(argv[i]));
        const char *filename = argv[2];
        // build the table
        buildSparseTable(nums, filename, string(argv[3]));
    }
    if (type == "query")
    {
        // read the range of the query
        int L = atoi(argv[3]);
        int R = atoi(argv[4]);
        const char *filename = argv[2];
        // print result to the console
        std::cout << query(L, R, filename) << "\n";
    }
    return 0;
}