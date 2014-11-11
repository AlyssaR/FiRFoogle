#ifndef TREE_H
#define TREE_H

#include "file.h"

class Tree {
private:
    File * root = nullptr;

    void insert(int, char*, char*, File*&);
    int height(File * t) { return (t==nullptr?-1:t->getHeight()); }
    int max(int a, int b) { return (a>=b?a:b); }

    void rotateWithLeftChild(File *&); //Case 1
    void doubleWithLeftChild(File *&); //Case 2
    void doubleWithRightChild(File *&); //Case 3
    void rotateWithRightChild(File *&); //Case 4


public:
    Tree();
    void insert(int v, char* t, char* a) { insert(v, t, a, root); }
    void get() {
        cout << root->getAuthor() << " wrote: " << root->getTitle()
             << " (" << root->getID() << ")" << endl;
    }

    ~Tree() { delete root; }
};


#endif // TREE_H
