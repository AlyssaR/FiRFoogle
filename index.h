#ifndef INDEX_H
#define INDEX_H

#include <cstring>
#include "entry.h"
#include <functional>
#include <iostream>
using namespace std;

class Index {
private:
    Entry **table;
    const int TABLE_SIZE = 16451136; //4048^2. Lulz
    std::hash<char*> hashIt;
public:
    Index();

    int* get(char*); //Returns all docIDs associated with given keyword
    void put(char*, int); //Finds table entry to place any keyword/docID pair
    void remove(char*); /*! Haven't written yet !*/

    void printIDs(char*);

    ~Index();
};

#endif // INDEX_H
