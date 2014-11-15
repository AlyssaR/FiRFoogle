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
    const int TABLE_SIZE = 500000000;

    hash<string> hashIt;
    void put(int, string, int); //Adds individual key
public:
    Index();

    void add(int, const map<string, int>&); //Adds all keywords from doc
    map<int, int> get(string); //Returns weighted docs for given keyword
    void remove(string); /*! Not written yet !*/
    void printIDs(string);
    void printTable();

    ~Index();
};

#endif // INDEX_H
