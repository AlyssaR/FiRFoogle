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
    const int TABLE_SIZE = 16451136; //4048^2. Lulz
    hash<char*> hashIt;
public:
    Index();

    map<int, int> get(char*); //Returns all weighted docIDs associated with given keyword
    void put(char*, int); //Finds table entry to place any keyword/docID pair
    void remove(char*); /*! Haven't written yet !*/

    void printIDs(char*);
    void printTable();

    ~Index();
};

#endif // INDEX_H
