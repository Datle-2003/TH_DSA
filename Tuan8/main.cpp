#include <iostream>
#include "RBTree.h"

using namespace std;

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr)/sizeof(int);
    Ref nil;
    Ref pRoot = createTree(arr, n, nil);
    
    // Operation here...

    removeTree(pRoot, nil);
    delete nil;
    return 0;
}