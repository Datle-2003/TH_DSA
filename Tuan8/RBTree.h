#ifndef RBTREE_H
#define RBTREE_H

#define BLACK 0
#define RED 1

typedef struct RBNode *Ref;
struct RBNode
{
    int key;
    bool color;
    Ref parent;
    Ref left;
    Ref right;
};

// auxiliary function
Ref getNode(int key, bool color, Ref nil);
void binaryInsert(Ref &pRoot, Ref p, Ref nil);
void leftRotate(Ref &pRoot, Ref p, Ref nil);
void rightRotate(Ref &pRoot, Ref p, Ref nil);
void RBTree_FixUp(Ref &pRoot, Ref x, Ref nil);
Ref rightMostNode(Ref r, Ref nil);
Ref searchTree(Ref pRoot, int key, Ref nil);
void delete_leftAdjust(Ref& pRoot, Ref& x, Ref nil);
void delete_rightAdjust(Ref& pRoot, Ref& x, Ref nil);
void delete_fixUp(Ref& pRoot, Ref x, Ref nil);
void removeTree(Ref &pRoot, Ref nil);// free memory

// main function
void Insert(Ref &pRoot, int key, Ref nil);
Ref createTree(int a[], int n, Ref& nil);
Ref lookUp(Ref pRoot, int key, Ref nil);
int Height(Ref pRoot);
int BlackHeight(Ref pRoot);
int Remove(Ref& pRoot, int key, Ref nil);

#endif