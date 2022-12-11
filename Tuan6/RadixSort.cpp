#include "RadixSort.h"

Ref *createRef(int value)
{
    Ref *p = new Ref;
    p->next = nullptr;
    p->key = value;
    return p;
}

void addRef(Bucket *&current, int value)
{
    if (current->head == nullptr) // add head
    {
        current->head = createRef(value);
        return;
    }
    // find position to add new value
    Ref *temp = current->head;
    while (temp->next != nullptr)
        temp = temp->next;
    // add
    temp->next = createRef(value);
}

Bucket *createBucket(int key, int value)
{
    Bucket *q = new Bucket;
    q->key = key;
    q->head = nullptr;
    q->next = nullptr;
    addRef(q, value);
    return q;
}

void addBucket(Bucket *&head, int key, int value)
{

    if (head == nullptr) // add head
    {
        head = createBucket(key, value);
        return;
    }
    Bucket *p1 = head;
    Bucket *p2 = head->next;

    // add at the first bucket
    if (key < head->key)
    {
        Bucket *tmp = createBucket(key, value);
        tmp->next = head;
        head = tmp;
        return;
    }

    while (p2 && p2->key <= key)
    {
        p1 = p1->next;
        p2 = p2->next;
    }

    // add at the last bucket
    if (p1->next == nullptr)
    {
        p2 = createBucket(key, value);
        p1->next = p2;
        return;
    }

    // key has already in multiple linked list
    if (p1->key == key)
    {
        addRef(p1, value);
        return;
    }

    // key is not exist
    Bucket *temp = createBucket(key, value);
    temp->next = p2;
    p1->next = temp;
}

int getDigits(int num)
{
    int count = 0;
    while (num)
    {
        count++;
        num /= 10;
    }
    return count;
}

int getMax(vector<int> nums)
{
    int max = nums[0];
    for (int i = 1; i < nums.size(); i++)
        if (max < nums[i])
            max = nums[i];
    return max;
}

void RadixSort()
{
    vector<int> nums;
    int k;
    readFile("input.txt", k, nums);
    Bucket *head = nullptr;

    int maxNum = getMax(nums);
    // numbers of digits of the maximum element
    int n = getDigits(maxNum);
    int tmp = 1;
    int cnt = 0;
    for (int i = 0; i < ceil(n / k); i++)
    {
        cnt = 0;
        for (int j = 0; j < nums.size(); j++)
        {
            // calculate key
            int key = nums[j] % int(pow(10, tmp * k)) / pow(10, (tmp - 1) * k);
            // add key to the bucket and nums[j] to that bucket's linked-list
            addBucket(head, key, nums[j]);
        }

        // get elements from bucket-list
        Bucket *p = head;
        while (p)
        {
            Ref *temp = head->head;
            while (temp) // get element(s) of each bucket
            {
                nums[cnt++] = temp->key;
                head->head = head->head->next;
                delete temp;
                temp = head->head;
            }
            head = head->next;
            delete p;
            p = head;
        }
        tmp++;
    }

    // print to screen
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
}

void readFile(const char *filename, int &k, vector<int> &nums)
{
    fstream f(filename, ios::in);
    if (!f)
    {
        cerr << "Can't open this file";
        exit(1);
    }
    int n;
    f >> k >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++)
        f >> nums[i];
}