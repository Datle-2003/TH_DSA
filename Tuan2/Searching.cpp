#include "Searching.h"

// read characters from a file
void readfile(fstream &f, char *s, int &n)
{
    char buffer;
    while (f >> buffer)
    {
        s[n++] = buffer;
        if (n > MAX_TEXT_LENGTH)
        {
            f.close();
            return;
        }
    }
    f.close();
}

// Check if the pattern is found in the text starting at the specified position
bool isFound(const char *text, int pos, const char *pattern, int n)
{
    // compare each character in two string
    for (int i = 0; i < n; i++)
        if (text[pos++] != pattern[i])
            return false; // character does not match

    return true; // all characters match
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
    for (int i = 0; i <= tsize - psize; i++) // Duyệt mảng text
    {
        // if the first character in pattern is found in text, check the rest of pattern
        if (text[i] == pattern[0])
        {
            // if pattern is found in text, increment the count
            if (isFound(text, i, pattern, psize))
                count++;
        }
    }
}

// calculate the hash code of the characters in the array from start position to end position
long long getHashcode(char *temp, int start, int end)
{
    long long hashcode = 0;
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        // Mã hash của chuỗi = tổng mã hash của từng kí tự
        // Mã hash của ký tự = vị trí của ký tự trong bảng chữ cái(tính từ 1) * 10 ^ j
        // với j là vị trí của ký tự đó trong chuỗi (tính từ 0)
        hashcode += int(temp[i] - 'A' + 1) * pow(10, j);
        // calculate the hash code of the current character
        // hash code of character = position of character in alphabet * 10 ^ position of character in array
        j++;
    }
    return hashcode;
}

void RabinKarp(char *text, int tsize, char *pattern, int psize, int &count)
{
    // calculate the hash code of the pattern
    long long hashCodePattern = getHashcode(pattern, 0, psize - 1);

    // hash code of the the first substring in text that is the same langth as pattern
    long long hashCode = getHashcode(text, 0, 0 + psize - 1);
    for (int i = 0; i <= tsize - psize; i++)
    {
        // if the hash code of the current substring matches the hash code of pattern
        if (hashCode == hashCodePattern)
        {
            // check if two strings are actually equal or not
            if (isFound(text, i, pattern, psize))
                count++;
        }
        // no more substrings in the text have the same length as the pattern
        if (i == tsize - psize)
            break;
        // update new hash code for the next substring in text
        // new hash code = current hash code - hash code of the leftmost character / 10 + hash code of the rightmost character
        hashCode = (hashCode - int(text[i] - 'A' + 1)) / 10 + int(text[i + psize] - 'A' + 1) * pow(10, psize - 1);
    }
}

void createLongestPrefixSuffix(int *lps, int n, char *pattern)
{
    lps[0] = 0; // lps[0] is always 0
    int i = 1, j = 0, count = 1;
    while (i < n)
    {
        // the character at the current position match
        while (pattern[i] == pattern[j])
        {
            // set the current element of the array to the length of the matching prefix/suffix
            lps[count++] = j + 1;
            // move to the next character
            i++;
            j++;
        }
        // character does not match
        while (pattern[i] != pattern[j] && j != 0 && i < n)
            // move to the position indicated by the previous element
            j = lps[j - 1];
        // no matching prefix/suffix
        if (j == 0)
        {
            // move to the next character
            i++;
            // set the current element of the array to 0
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
        // if the characters match
        if (text[i] == pattern[j])
        {
            // move to the next character
            i++;
            j++;
        }

        // the pattern has been fully matched
        if (j == psize)
        {
            count++;
            // move to the position indicated by the previous element
            j = lps[j - 1];
        }

        // the characters do not match
        if (text[i] != pattern[j] && i < tsize)
        {

            if (j != 0)
                // move to the position indicated by the previous element
                j = lps[j - 1];
            else
                // move to the next character in the text
                i++;
        }
    }
    delete lps;
}

void BoyerMoore(char *text, int tsize, char *pattern, int psize, int &count)
{
    // create bad match table
    int bmt[TABLE_LENGTH];

    // if the character is not exist in the pattern or it is the last character of the pattern, set its value to the size of the pattern
    // Ngược lại gán giá trị bằng psize - i - 1
    // Otherwise, set its value to the size of the pattern minus its index in the pattern minus 1
    for (int i = 0; i < TABLE_LENGTH; i++)
        bmt[i] = psize; //

    for (int i = 0; i < psize - 1; i++)
        bmt[(int)(pattern[i])] = psize - i - 1;

    int s = 0; // the shift variable
    while (s <= (tsize - psize))
    {
        int j = psize - 1; // the last character of the pattern

        // compare the charaters of the pattern and text
        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) // the pattern is found in the text
        {

            count++;
            // shift the pattern by the value of the last character in the bad match table
            if (s + psize < tsize)
                s += bmt[(int)text[s + psize - 1]];
            else
                s++; // beyond the scope of the pattern
        }
        else
            // shift the pattern by the value ò the mismatched character in the bad match table
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
    // count processing time
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
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    double elapsedTime = double(duration.count()) / 1000000; // convert nanosecond to millisecond

    cout << count << " - " << std::fixed << std::setw(8) << elapsedTime << endl; // print
}