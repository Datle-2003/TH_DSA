#include "Searching.h"

void readfile(fstream &f, char *s, int &n)
{
    char buffer;
    while (f >> buffer)
        s[n++] = buffer;
    f.close();
}

bool isFound(const char *text, int pos, const char *pattern, int n)
{
    for (int i = 0; i < n; i++)
        if (text[pos++] != pattern[i])
            return false;
    return true;
}

// 1 is Brute-force
// 2 is Rabin-Karp
// 3 is Knuth-Morris-Patt
// 4 is Boyer-Moore
int typeOfSearching(char *name)
{
    if (strcmp(name, "BF") == 0)
        return 1;
    if (strcmp(name, "RK") == 0)
        return 2;
    if (strcmp(name, "KMP") == 0)
        return 3;
    if (strcmp(name, "BM") == 0)
        return 4;
    return 0;
}

void BruteForce(char *text, int tsize, char *pattern, int psize, int &count)
{
    for (int i = 0; i <= tsize - psize; i++)
    {
        if (text[i] == pattern[0])
        {
            if (isFound(text, i, pattern, psize))
                count++;
        }
    }
}

long long getHashcode(char *tmp, int begin, int end)
{
    long long hashcode = 0;
    int j = 0;
    for (int i = begin; i <= end; i++)
    {
        hashcode += int(tmp[i] - 'A' + 1) * pow(10, j);
        j++;
    }
    return hashcode;
}

void RabinKarp(char *text, int tsize, char *pattern, int psize, int &count)
{
    long long hashCode = getHashcode(pattern, 0, psize - 1);

    long long temp = getHashcode(text, 0, 0 + psize - 1);
    for (int i = 0; i <= tsize - psize; i++)
    {
        if (temp == hashCode)
        {
            if (isFound(text, i, pattern, psize))
                count++;
        }
        if (i == tsize - psize)
            break;
        temp = (temp - int(text[i] - 'A' + 1)) / 10 + int(text[i + psize] - 'A' + 1) * pow(10, psize - 1);
    }
}

void createLongestPrefixSuffix(int *lps, int n, char *pattern)
{
    lps[0] = 0;
    int i = 1, j = 0, count = 1;
    while (i < n)
    {
        while (pattern[i] == pattern[j])
        {
            lps[count++] = j + 1;
            i++;
            j++;
        }
        while (pattern[i] != pattern[j] && j != 0 && i < n)
            j = lps[j - 1];
        if (j == 0)
        {
            i++;
            lps[count++] = 0;
        }
    }
}

void KnuthMorrisPatt(char *text, int tsize, char *pattern, int psize, int &count)
{
    // create lps[] hold the longest prefix and suffix
    int *lps = new int[psize];
    createLongestPrefixSuffix(lps, psize, pattern);

    int i = 0, j = 0; // i is index of text, j is index of pattern
    while ((tsize - i) >= (psize - j))
    {

        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == psize)
        {
            count++;
            j = lps[j - 1];
        }

        if (text[i] != pattern[j] && i < tsize)
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    delete lps;
}

void BoyerMoore(char *text, int tsize, char *pattern, int psize, int &count)
{
    // create bad match table
    int bmt[TABLE_LENGTH];

    for (int i = 0; i < TABLE_LENGTH; i++)
        bmt[i] = psize;

    for (int i = 0; i < psize - 1; i++)
        bmt[(int)(pattern[i])] = psize - i - 1;

    int s = 0;
    while (s <= (tsize - psize))
    {
        int j = psize - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0)
        {
            count++;
            if (s + psize < tsize)
                s += bmt[(int)text[s + psize - 1]];
            else
                s++;
        }
        else
            s += bmt[(int)text[s + psize - 1]];
    }
}

void Search(const char *filename, char *pattern, int type)
{
    // read file
    int psize = strlen(pattern); // pattern size
    char text[MAX_TEXT_LENGTH];
    int tsize = 0; // text size
    int count = 0; // counting times exist of pattern in text

    fstream f(filename, ios::in);
    readfile(f, text, tsize);

    auto start = high_resolution_clock::now();

    switch (type)
    {
    case 1:
        BruteForce(text, tsize, pattern, psize, count);
        break;
    case 2:
        RabinKarp(text, tsize, pattern, psize, count);
        break;
    case 3:
        KnuthMorrisPatt(text, tsize, pattern, psize, count);
        break;
    case 4:
        BoyerMoore(text, tsize, pattern, psize, count);
        break;
    default:
        cerr << "Error name of searching algorithm!\n";
        return;
        break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << count << " - " << duration.count() << endl;
}