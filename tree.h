#ifndef TREE_H
#define TREE_H

#include "file.h"

struct Node {
    Node * left, * right;
    int height, id;
    Node(int x) : id(x) {}
};

class Tree {
private:
    Node * root;

    void insert(int, Node *&);
    int height(Node * t) { return (t==nullptr?-1:t->height); }
    int max(int a, int b) { return (a>=b?a:b); }

    void rotateWithLeftChild(Node *&); //Case 1
    void doubleWithLeftChild(Node *&); //Case 2
    void doubleWithRightChild(Node *&); //Case 3
    void rotateWithRightChild(Node *&); //Case 4


public:
    Tree(): root(nullptr) {}
    void insert(int v) { insert(v, root); }

};


#endif // TREE_H
