#include "Searching.h"

int main(int argc, char **argv)
{
  if (argc == 4)
  {
    const char *filename = argv[1];
    char *pattern = argv[2];
    char *tmp = argv[3];

    int type = typeOfSearching(tmp);
    Search(filename, pattern, type);
  }
  else
    cerr << "Syntax Error!\n";
  return 0;
}