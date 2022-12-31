#include "FileProcessing.h"

vector<vector<int>> readFile(const char *filename, string &type)
{
    vector<vector<int>> table;
    fstream f(filename, ios::in);
    std::string line;
    std::getline(f, line);
    stringstream s(line);
    s >> type;
    while (std::getline(f, line)) // read line by line
    {
        vector<int> tmp;
        std::stringstream ss(line);
        int a;
        while (ss >> a) // extract each element
            tmp.push_back(a);
        table.push_back(tmp);
    }
    return table;
}

void print(vector<vector<int>> &table, ostream &f, string type)
{
    f << type << "\n";
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
            f << setw(3) << table[i][j] << " ";
        f << "\n";
    }
}

void writeToFile(vector<vector<int>> &table, const char *filename, string type)
{
    fstream f(filename, ios::out);
    print(table, f, type);
}

void printToConsole(vector<vector<int>> &table, string type)
{
    print(table, std::cout, type);
}
