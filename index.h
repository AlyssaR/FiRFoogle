#ifndef INDEX_H
#define INDEX_H

#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>

#include "entry.h"
using namespace std;

class Index {
private:
    map<int, Entry*> table;
    hash<string> hashIt;
    void printIDs(string, ofstream&);
    void put(int, string, int); //Adds individual key
public:
    Index();

    void add(int, const map<string, int>&); //Adds all keywords from doc
    map<int, int> get(string); //Returns weighted docs for given keyword

    void remove(string); /*! Not written yet !*/
    void printTable(char*);

    ~Index();
};

#endif // INDEX_H
