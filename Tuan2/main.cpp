#include "Searching.h"

int main(int argc, char **argv)
{
  if (argc == 4) // check if the correct number of arguments
  {
    const char *filename = argv[1];
    char *pattern = argv[2];
    char *tmp = argv[3];

    // get the type of searching algorithm to use
    // 1 is Brute-force
    // 2 is Rabin-Karp
    // 3 is Knuth-Morris-Patt
    // 4 is Boyer-Moore
    int type = typeOfSearching(tmp);

    // Perform the search
    Search(filename, pattern, type);
  }
  else
    cerr << "Error!\n"; // incorrect number of arguments
  return 0;
}