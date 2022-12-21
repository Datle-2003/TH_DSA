#include "RBTree.h"
#include <iostream>

// auxiliary function
Ref getNode(int key, bool color, Ref nil)
{
    Ref temp = new RBNode;
    temp->key = key;
    temp->color = color;
    temp->left = temp->right = nil;
    temp->parent = nil;
    return temp;
}

void binaryInsert(Ref &pRoot, Ref p, Ref nil){
    if(pRoot == nullptr || pRoot == nil){
        pRoot = p;
        return;
    }
    Ref prev = nullptr;
    Ref trav = pRoot;
    while(trav != nil){
        prev = trav;
        if (p->key < trav->key)
            trav = trav->left;
        else if (p->key > trav->key)
            trav = trav->right;
        else
            return; // key already exists
    }
    if (p->key < prev->key)
    {
        prev->left = p;
    }
    else
    {
        prev->right = p;
    }
    p->parent = prev;
}

void leftRotate(Ref &pRoot, Ref p, Ref nil)
{
    Ref q = p->right;
    p->right = q->left;
    if (q->left != nil)
    {
        q->left->parent = p; // child node points to parent node if not nil
    }
    q->parent = p->parent;
    if (p->parent == nil)
        pRoot = q; // pRoot = p so after rotating, pRoot change to q
    else
    {
        // Parent of p points to q
        if (p == p->parent->left)
            p->parent->left = q;
        else
            p->parent->right = q;
    }
    p->parent = q;
    q->left = p;
}

void rightRotate(Ref &pRoot, Ref p, Ref nil){
    Ref q = p->left;
    p->left = q->right;
    if (q->right != nil)
    {
        q->right->parent = p; // child node points to parent node if not nil
    }
    q->parent = p->parent;
    if (p->parent == nil)
        pRoot = q; // pRoot = p so after rotating, pRoot change to q
    else
    {
        // Parent of p points to q
        if (p == p->parent->left)
            p->parent->left = q;
        else
            p->parent->right = q;
    }
    p->parent = q;
    q->right = p;
}

void RBTree_FixUp(Ref &pRoot, Ref x, Ref nil)
{
    // x: inserted node, p: parent of x, g: grandparent of x, u: uncle of x
    Ref p = x->parent;
    // Case 1: parent is BLACK
    if (p->color == BLACK)
    {
        pRoot->color = BLACK; // force root to be black (in case x is root)
        return;
    }
    Ref g = p->parent;
    Ref u = (g->left == p) ? g->right : g->left;
    if (p->color == RED && u->color == RED)
    { // Case 2: Swap g color with p, u color
        g->color = RED;
        p->color = u->color = BLACK;
        return RBTree_FixUp(pRoot, g, nil); // recursive call with g is the newly node to balance
    }
    else if (p->color == RED && u->color == BLACK)
    {
        // Case 3: x is external Child: swap color g and p, rotate at g
        bool leftExternalChild = (g->right == u && p->left == x);
        bool rightExternalChild = (g->left == u && p->right == x);
        // Case 4: x is internal Child
        bool leftInternalChild = (g->right == u && p->right == x);
        bool rightInternalChild = (g->left == u && p->left == x);
        if (leftExternalChild)
        {
            g->color = RED;
            p->color = BLACK;
            rightRotate(pRoot, g, nil);
        }
        else if (rightExternalChild)
        {
            g->color = RED;
            p->color = BLACK;
            leftRotate(pRoot, g, nil);
        }
        else if(leftInternalChild){
            leftRotate(pRoot, p, nil);
            g->color = RED;
            p->color = BLACK;
            rightRotate(pRoot, g, nil);
        }
        else if(rightInternalChild){
            rightRotate(pRoot, p, nil);
            g->color = RED;
            p->color = BLACK;
            leftRotate(pRoot, g, nil);
        }
    }
    pRoot->color = BLACK; // force root to be black
}

Ref searchTree(Ref pRoot, int key, Ref nil){
    if(pRoot == nil)
        return nil;
    if(pRoot->key == key)
        return pRoot;
    else if(pRoot->key < key){
        return searchTree(pRoot->right, key, nil);
    }
    else
        return searchTree(pRoot->left, key, nil);
}

Ref rightMostNode(Ref r, Ref nil){
    if(r == nil)
        return nil;
    // right most node of left subtree of r
    Ref p = r->left;
    if(p == nil) return nil;
    while(p->right != nil){
        p = p->right;
    }
    return p;
}

void delete_leftAdjust(Ref& pRoot, Ref& x, Ref nil){
    // x is the left child, w is the right child, p is parent
    Ref p = x->parent;
    Ref w = p->right;
    // Case 3: w is RED -> w and p swap colors, left rotate at p, black token remains at x
    if(w->color == RED){
        w->color = BLACK;
        p->color = RED;
        leftRotate(pRoot, p, nil);
        w = p->right;// update w
    }
    // Case 2: w and its child are all BLACK -> w changes to RED and black token from x to p
    if(w->left->color == BLACK && w->right->color == BLACK){
        w->color = RED;
        x = p;
    }
    else{// Case 4: at least 1 child of w is BLACK
        if(w->right->color == BLACK){// make external child RED
            w->left->color = BLACK;
            w->color = RED;
            rightRotate(pRoot, w, nil);
            w = p->right;
        }
        w->color = p->color;
        p->color = BLACK;
        w->right->color = BLACK;
        leftRotate(pRoot, p, nil);
        x = pRoot;// x = pRoot will end the balancing
    }
}

void delete_rightAdjust(Ref& pRoot, Ref& x, Ref nil){
    // x is the left child, w is the right child, p is parent
    Ref p = x->parent;
    Ref w = p->left;
    // Case 3: w is RED -> w and p swap colors, right rotate at p, black token remains at x
    if(w->color == RED){
        w->color = BLACK;
        p->color = RED;
        rightRotate(pRoot, p, nil);
        w = p->left;// update w
    }
    // Case 2: w and its child are all BLACK -> w changes to RED and black token from x to p
    if(w->left->color == BLACK && w->right->color == BLACK){
        w->color = RED;
        x = p;
    }
    else{// Case 4: at least 1 child of w is BLACK
        if(w->left->color == BLACK){// make external child RED
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(pRoot, w, nil);
            w = p->left;
        }
        w->color = p->color;
        p->color = BLACK;
        w->left->color = BLACK;
        rightRotate(pRoot, p, nil);
        x = pRoot;// x = pRoot will end the balancing
    }
}

void delete_fixUp(Ref& pRoot, Ref x, Ref nil){
    // p is parent of x, in case x is nil (still needed to balance)
    while(x->color == BLACK && x != pRoot){// if not case 1
        if(x == x->parent->left)
            delete_leftAdjust(pRoot, x, nil);
        else
            delete_rightAdjust(pRoot, x, nil);
    }
    x->color = BLACK;// implement case 1, change color of x to BLACK
}

void removeTree(Ref &pRoot, Ref nil){
    // remove recursively
    if(pRoot->left != nil)
        removeTree(pRoot->left, nil);
    if(pRoot->right != nil)
        removeTree(pRoot->right, nil);
    delete pRoot;
    pRoot = nil;
}

// main function
void Insert(Ref &pRoot, int key, Ref nil){
    Ref p = getNode(key, RED, nil);// Node inserted is always red
    binaryInsert(pRoot, p, nil);
    RBTree_FixUp(pRoot, p, nil);
}

Ref createTree(int a[], int n, Ref& nil){
    nil = getNode(0, BLACK, nullptr);
    nil->left = nil->right = nil->parent = nil;
    Ref pRoot = nil;
    for(int i = 0; i < n; i++)
        Insert(pRoot, a[i], nil);
    return pRoot;
}

Ref lookUp(Ref pRoot, int key, Ref nil){
    if(pRoot == nullptr) return nullptr;// empty tree
    while(pRoot != nil){
        // binary search
        if(pRoot->key == key)
            return pRoot;
        else if(pRoot->key < key)
            pRoot = pRoot->right;
        else
            pRoot = pRoot->left;
    }
    return nullptr;// not found
}

int Height(Ref pRoot){
    // height(pRoot) = max(height(pRoot->left), height(pRoot->right)) + 1
    if(pRoot == pRoot->left) return 1;// pRoot == nil
    int leftHeight = Height(pRoot->left);
    int rightHeight = Height(pRoot->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int BlackHeight(Ref pRoot){
    // all path from root to leaf has the same black height, so only one is traversed
    if(pRoot == nullptr)
        return 0;// empty tree
    Ref nil = pRoot->parent;
    int height = 0;
    while(pRoot != nil){
        if(pRoot->color == BLACK)
            height++;
        pRoot = pRoot->left;
    }
    return height + 1;// + nil
}

int Remove(Ref& pRoot, int key, Ref nil){
    // y: deleted node, x: child of y, p: father of y
    Ref temp = searchTree(pRoot, key, nil);
    if(temp == nil)
        return 0;
    // y = temp in case node contains key has at most 1 child
    // and y = rightMostNode in case node contains 2 child
    Ref y = (temp->left == nil || temp->right == nil) ? temp : rightMostNode(temp, nil); 
    Ref x = (y->left == nil) ? y->right : y->left;
    Ref p = y->parent;
    x->parent = p;
    if(p == nil)
        pRoot = x;
    else
        if(y == p->left)
            p->left = x;
        else
            p->right = x;
    if(temp != y)
        temp->key = y->key;// temp node gets right most key
    // in case y is red, then all path from y still has the same black height
    // and the tree is still balanced
    if(y->color == BLACK)
        delete_fixUp(pRoot, x, nil);// balance tree in case y is black
    delete y;
    return 1;
}