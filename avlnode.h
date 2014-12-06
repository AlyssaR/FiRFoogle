#ifndef AVLNODE_H
#define AVLNODE_H

class avlnode {
private:
    int key;
    unsigned char height;
    avlnode* left;
    avlnode* right;
    avlnode(int k) { key = k; left = right = 0; height = 1; }
public:
    int getKey() { return key; };
    char getHeight() { return height; };
    avlnode* getLeft() { return left; };
    avlnode* getRight() { return left; };
    void setKey(avlnode* n) {height = }

};

#endif // AVLNODE_H
