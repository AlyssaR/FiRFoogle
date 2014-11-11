#include "tree.h"

Tree::Tree() {}

void Tree::rotateWithLeftChild(File *& k1) { //Case 1
    File * k2 = k1->getLeft();
    /** Rotate Files **/
    k1->setLeft(k2->getRight());
    k2->setRight(k1);
    /** Update Heights **/
    k1->setHeight(max(height(k1->getLeft()), height(k1->getRight())) + 1);
    k2->setHeight(max(height(k2->getLeft()), height(k2->getRight())) + 1);
    /** Switch alpha **/
    k1 = k2;
}

void Tree::doubleWithLeftChild(File *& k3) { //Case 2
    rotateWithRightChild(k3->getLeft());
    rotateWithLeftChild(k3);
}

void Tree::doubleWithRightChild(File *& k3) { //Case 3
    rotateWithLeftChild(k3->getRight());
    rotateWithRightChild(k3);
}

void Tree::rotateWithRightChild(File *& k1) { //Case 4
    File * k2 = k1->getRight();
    /** Rotate Files **/
    k1->setRight(k2->getLeft());
    k2->setLeft(k1);
    /** Update Heights **/
    k1->setHeight(max(height(k1->getLeft()), height(k1->getRight())) + 1);
    k2->setHeight(max(height(k2->getLeft()), height(k2->getRight())) + 1);
    /** Switch alpha **/
    k1 = k2;
}

void Tree::insert(int val, char* title, char* author, File*& t) {
    if(t==nullptr) //Add node
        t = new File(val, title, author);
    else if(val < t->getID()) { //Go left
        insert(val, title, author, t->getLeft());
        if(height(t->getLeft())-height(t->getRight()) == 2) {
            if(val < t->getLeft()->getID()) //Case 1
                rotateWithLeftChild(t);
            else //Case 2
                doubleWithLeftChild(t);
        }
    }
    else if(t->getID() < val) { //Go right
        insert(val, title, author, t->getRight());
        if(height(t->getRight())-height(t->getLeft()) == 2) {
            if(val < t->getRight()->getID()) //Case 3
                rotateWithRightChild(t);
            else //Case 4
                doubleWithRightChild(t);
        }
    }

    t->setHeight(max(height(t->getLeft()), height(t->getRight()))+1); //Update height
}
