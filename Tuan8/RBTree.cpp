#include "RBTree.h"

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

void binaryInsert(Ref &pRoot, Ref p)
{
    if (pRoot == nullptr)
    {
        pRoot = p;
        return;
    }
    Ref prev = nullptr;
    Ref trav = pRoot;
    while (trav != nullptr)
    {
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
void rightRotate(Ref &pRoot, Ref p, Ref nil)
{ // similar
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
        else if (leftInternalChild)
        {
            leftRotate(pRoot, p, nil); // now in case left external child
            g->color = RED;
            p->color = BLACK;
            rightRotate(pRoot, g, nil);
        }
        else if (rightInternalChild)
        {
            rightRotate(pRoot, p, nil); // now in case right external child
            g->color = RED;
            p->color = BLACK;
            leftRotate(pRoot, g, nil);
        }
    }
    pRoot->color = BLACK; // force root to be black
}

void Insert(Ref &pRoot, int key, Ref nil)
{
    Ref p = getNode(key, RED, nil); // Node inserted is always red
    binaryInsert(pRoot, p);
    RBTree_FixUp(pRoot, p, nil);
}
