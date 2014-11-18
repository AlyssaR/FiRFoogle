#ifndef INDEX_H
#define INDEX_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <set>

#include "entry.h"
using namespace std;

class Index {
private:
    unordered_map<string, Entry*> table;
    set<string> keys;
    void printIDs(string, ofstream&);
    void put(string, string, int); //Adds individual key
public:
    Index();

    void add(string, const unordered_map<string, int>&); //Adds all keywords from doc
    unordered_map<string, int> get(string); //Returns weighted docs for given keyword

    void remove(string); /*! Not written yet !*/
    void printTable(char*);

    ~Index();
};

#endif // INDEX_H
