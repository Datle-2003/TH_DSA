#include "Searching.h"

int main(int argc, char **argv)
{
  if (argc == 4)
  {
    const char *filename = argv[1];
    char *pattern = argv[2];
    char *tmp = argv[3];
    // get type of searching algorithm
    // 1 is Brute-force
    // 2 is Rabin-Karp
    // 3 is Knuth-Morris-Patt
    // 4 is Boyer-Moore
    int type = typeOfSearching(tmp);
    Search(filename, pattern, type);
  }
  else
    cerr << "Syntax Error!\n"; // Tham số dòng lệnh không hợp lệ
  return 0;
}