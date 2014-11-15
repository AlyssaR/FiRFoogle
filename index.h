#ifndef INDEX_H
#define INDEX_H

#include <cmath>
#include <cstring>
#include "entry.h"
#include <functional>
#include <iostream>
#include <map>
using namespace std;

class Index {
private:
    Entry **table;
    const int TABLE_SIZE = 9999999;

    hash<string> hashStuff;
    void put(int, string, int); //Adds individual key
public:
    Index();

    void add(int, const map<string, int>&); //Adds all keywords from doc
    map<int, int> get(string); //Returns weighted docs for given keyword
    int hashIt(string s) { return hashStuff(s); } /*! MAKE IT SMALLER !*/

    void remove(string); /*! Not written yet !*/
    void printIDs(string);
    void printTable();

    ~Index();
};

#endif // INDEX_H
