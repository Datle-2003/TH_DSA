#include "FileProcessing.h"
#include "SparseTable.h"

SparseTable readTable(istream &f, string tablename)
{
    SparseTable ST;

    std::string line, tmp, name;

    while (std::getline(f, line))
    {
        stringstream ss(line);
        if (line.find("Tablename") != std::string::npos)
        {
            ss >> tmp >> name;
            if (name == tablename)
            {
                ST.name = name;
                std::getline(f, line);

            }

        }
    }

    vector<string> temp = {2, ""};
    for (int i = 0; i < 2; i++)
    {
        std::getline(f, line);
        stringstream ss(line);
        ss >> tmp >> temp[i];
    }
    ST.name = temp[0];
    ST.type = temp[1];

    while (std::getline(f, line)) // read line by line
    {
        vector<int> nums;
        std::stringstream ss(line);
        int a;
        while (ss >> a) // extract each element
            nums.push_back(a);
        ST.table.push_back(nums);
    }
    return ST;
}

void deleteTable(const char *filename, string tablename) // ten bang can xoa
{
    fstream f(filename, ios::in || ios::app);
    vector<SparseTable> list;
    int i = 0;
    while (!f.eof())
      //  list[i++] = readTable(f);

    for (int j = 0; j < list.size(); i++)
    {
        if (list[j].name == tablename)
            list.erase(list.begin() + j);
    }

    f.close();
    fstream f(filename, ios::out);
    for (int i = 0; i < list.size(); i++)
        print(list[i], f);
}

void print(SparseTable &ST, ostream &f)
{
    f.seekp(ios::end);
    f << "Tablename:  " << ST.name << "\n";
    f << "Tabletype:  " << ST.type << '\n';
    for (int i = 0; i < ST.table.size(); i++)
    {
        for (int j = 0; j < ST.table[i].size(); j++)
            f << setw(3) << ST.table[i][j] << " ";
        f << "\n";
    }
}
