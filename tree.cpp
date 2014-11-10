#include "tree.h"

void Tree::rotateWithLeftChild(Node *& k1) { //Case 1
    Node * k2 = k1->left;
    //Rotate nodes
    k1->left = k2->right;
    k2->right = k1;
    //Update Heights
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    //Switch alpha
    k1 = k2;
}

void Tree::doubleWithLeftChild(Node *& k3) { //Case 2
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void Tree::doubleWithRightChild(Node *& k3) { //Case 3
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

void Tree::rotateWithRightChild(Node *& k1) { //Case 4
    Node * k2 = k1->right;
    //Rotate nodes
    k1->right = k2->left;
    k2->left = k1;
    //Update Heights
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    //Switch alpha
    k1 = k2;
}

void Tree::insert(int val, Node *& t) {
    if(t==nullptr) //Add node
        t = new Node(val);
    else if(val < t->id) { //Go left
        insert(val, t->left);
        if(height(t->left)-height(t->right) == 2) {
            if(val < t->left->id) //Case 1
                rotateWithLeftChild(t);
            else //Case 2
                doubleWithLeftChild(t);
        }
    }
    else if(t->id < val) { //Go right
        insert(val, t->right);
        if(height(t->right)-height(t->left) == 2) {
            if(val < t->right->id) //Case 3
                rotateWithRightChild(t);
            else //Case 4
                doubleWithRightChild(t);
        }
    }

    t->height = max(height(t->left), height(t->right))+1; //Update height
}
