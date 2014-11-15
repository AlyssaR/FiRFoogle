#ifndef INDEX_H
#define INDEX_H

#include <cstring>
#include "entry.h"
#include <functional>
#include <iostream>
#include <map>
using namespace std;

class Index {
private:
    Entry **table;
    const int TABLE_SIZE = 999999;

    hash<string> hashIt;
    void put(int, string, int); //Finds table entry to place any keyword/docID pair
public:
    Index();

    void add(int, map<string, int>&); //Adds all keywords
    map<int, int> get(string); //Returns all weighted docIDs associated with given keyword
    void remove(string);
    void printIDs(string);
    void printTable();

    ~Index();
};

#endif // INDEX_H
