#include "FileProcessing.h"

vector<vector<int>> readFile(const char *filename)
{
    vector<vector<int>> table;
    fstream f(filename, ios::in);
    std::string line;

    while (std::getline(f, line))
    {
        vector<int> tmp;
        std::stringstream ss(line);
        int a;
        while (ss >> a)
            tmp.push_back(a);
        table.push_back(tmp);
    }
    return table;
}

void print(vector<vector<int>> &table, ostream &f)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
            f << setw(3) << table[i][j] << " ";
        f << "\n";
    }
}

void writeToFile(vector<vector<int>> &table, const char *filename)
{
    fstream f(filename, ios::out);
    print(table, f);
}

void printToConsole(vector<vector<int>> &table)
{
    print(table, std::cout);
}
