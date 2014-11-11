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
    friend class Tree;
    File(int val, char* name, char* auth) : id(val),
        title(name), author(auth) {}

    //getters and setters

    ~File() {
        delete left;
        delete right;
        delete title;
        delete author;
    }
};

#endif // FILE_H
