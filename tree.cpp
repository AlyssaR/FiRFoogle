#include "tree.h"

void Tree::rotateWithLeftChild(File *& k1) { //Case 1
    File * k2 = k1->left;
    //Rotate Files
    k1->left = k2->right;
    k2->right = k1;
    //Update Heights
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    //Switch alpha
    k1 = k2;
}

void Tree::doubleWithLeftChild(File *& k3) { //Case 2
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void Tree::doubleWithRightChild(File *& k3) { //Case 3
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

void Tree::rotateWithRightChild(File *& k1) { //Case 4
    File * k2 = k1->right;
    //Rotate Files
    k1->right = k2->left;
    k2->left = k1;
    //Update Heights
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    //Switch alpha
    k1 = k2;
}

void Tree::insert(int val, char* title, char* author, File*& t) {
    if(t==nullptr) //Add File
        t = new File(val, title, author);
    else if(val < t->id) { //Go left
        insert(val, title, author, t->left);
        if(height(t->left)-height(t->right) == 2) {
            if(val < t->left->id) //Case 1
                rotateWithLeftChild(t);
            else //Case 2
                doubleWithLeftChild(t);
        }
    }
    else if(t->id < val) { //Go right
        insert(val, title, author, t->right);
        if(height(t->right)-height(t->left) == 2) {
            if(val < t->right->id) //Case 3
                rotateWithRightChild(t);
            else //Case 4
                doubleWithRightChild(t);
        }
    }

    t->height = max(height(t->left), height(t->right))+1; //Update height
}
