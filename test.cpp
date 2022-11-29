#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    vector<int> nums = {15522, 16427, 2253, 7644};
    int tmp = 2, k = 2;
    for (int i = 0; i < 4; i++)
    {
        int key = nums[i] % int(pow(10, tmp * k)) / pow(10, (tmp - 1) * k);
        cout << key << " ";
    }
}