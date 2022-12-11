#include "Searching.h"

void readfile(fstream &f, char *s, int &n)
{
    char buffer;
    while (f >> buffer)
        s[n++] = buffer;
    f.close();
}

// Kiểm tra chuỗi pattern có nằm trong chuỗi text kể từ vị trí pos hay không
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
    for (int i = 0; i <= tsize - psize; i++) // Duyệt mảng text
    {
        if (text[i] == pattern[0]) // Nếu tồn tại kí tự trong mảng text giống kí tự đầu tiên trong mảng pattern thì kiểm tra các kí tự tiếp theo
        {
            if (isFound(text, i, pattern, psize)) // Kiểm tra chuỗi pattern nằm trong text kể từ vị trí i
                count++;
        }
    }
}

// tính mã hash của chuỗi kể từ vị trí begin -> end
long long getHashcode(char *temp, int begin, int end)
{
    long long hashcode = 0;
    int j = 0;
    for (int i = begin; i <= end; i++)
    {
        // Mã hash của chuỗi = tổng mã hash của từng kí tự
        // Mã hash của ký tự = vị trí của ký tự trong bảng chữ cái(tính từ 1) * 10 ^ j
        // với j là vị trí của ký tự đó trong chuỗi (tính từ 0)
        hashcode += int(temp[i] - 'A' + 1) * pow(10, j);
        j++;
    }
    return hashcode;
}

void RabinKarp(char *text, int tsize, char *pattern, int psize, int &count)
{
    // mã hash của chuỗi pattern
    long long hashCodePattern = getHashcode(pattern, 0, psize - 1);
    // Mã hash của chuỗi con có độ dài bằng chuỗi pattern từ vị trí 0 trong text
    long long hashCode = getHashcode(text, 0, 0 + psize - 1);
    for (int i = 0; i <= tsize - psize; i++)
    {
        if (hashCode == hashCodePattern) // 2 chuỗi có cùng mã hash -> Kiểm tra 2 chuỗi giống nhau hay không
        {
            if (isFound(text, i, pattern, psize))
                count++;
        }
        if (i == tsize - psize) // Không còn chuỗi con trong text có cùng độ dài với pattern kể từ vị trí i
            break;
        // Cập nhật mã hash cho chuỗi con tiếp theo
        // Mã hash mới = (Mã hash cũ - Mã hash của phần từ trái cùng) / 10 + Mã hash của phần từ phải cùng
        hashCode = (hashCode - int(text[i] - 'A' + 1)) / 10 + int(text[i + psize] - 'A' + 1) * pow(10, psize - 1);
    }
}

void createLongestPrefixSuffix(int *lps, int n, char *pattern)
{
    lps[0] = 0; // lps[0] is always 0
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
            // xuất hiện sai khác -> Quay lui về vị trí lps[j - 1];
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

        if (text[i] == pattern[j]) // Kiểm tra từng kí tự
        {
            i++;
            j++;
        }

        if (j == psize) // duyệt hết chuỗi pattern
        {
            count++;
            j = lps[j - 1];
        }

        if (text[i] != pattern[j] && i < tsize)
        {
            // Xuất hiện sai khác
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
    
    // Nếu ký tự không tồn tại trong mảng pattern hoặc là ký tự cuối của chuỗi pattern -> gán giá trị bằng psize
    // Ngược lại gán giá trị bằng psize - i - 1  
    for (int i = 0; i < TABLE_LENGTH; i++)
        bmt[i] = psize; // 
    for (int i = 0; i < psize - 1; i++)
        bmt[(int)(pattern[i])] = psize - i - 1;

    int s = 0; // độ dời của chuỗi pattern so với ban đầu
    while (s <= (tsize - psize))
    {
        int j = psize - 1; // Duyệt chuỗi pattern từ cuối -> đầu

        while (j >= 0 && pattern[j] == text[s + j]) // kiểm tra từng ký tự
            j--;
        if (j < 0) // chuỗi pattern tồn tại trong text
        {
            count++;
            if (s + psize < tsize) 
            // bmt[(int)text[s + psize - 1]] là giá trị của ký tự đang xét của chuỗi text trong bảng bmt
            // Dịch chuỗi pattern sao cho ký tự cuối cùng trong pattern bằng ký tự tiếp theo trong chuỗi text
                s += bmt[(int)text[s + psize - 1]];
            else
                s++; // ngoài phạm vi của mảng
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