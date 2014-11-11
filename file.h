#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <map>
using namespace std;

class File {
private:
    int id, height = 0;
    File * left = nullptr, * right = nullptr;
    map<char*, int> keywords;
    char * title, * author;
public:
    File(int val, char* name, char* auth) : id(val),
        title(name), author(auth) {}

    char* getAuthor() { return author; }
    int getID() { return id; }
    int getHeight() { return height; }
    File* getLeft() { return left; }
    File* getRight() { return right; }
    char* getTitle() { return title; }

    void setID(int i) { id=i; }
    void setHeight(int h) { height = h; }
    void setLeft(File* l) { left = l; }
    void setRight(File* r) { right = r; }

    ~File() {
        delete left;
        delete right;
        delete title;
        delete author;
    }
};

#endif // FILE_H
