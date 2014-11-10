#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <map>
using namespace std;

class File {
private:
    int id, height;
    File * left, * right;
    map<char*, int> keywords;
    char * title, * author;
public:
    friend class Tree;
    File(int val, char* name, char* auth) : id(val), left(nullptr),
        right(nullptr), height(0), title(name), author(auth) {}

    //getters and setters
};

#endif // FILE_H
