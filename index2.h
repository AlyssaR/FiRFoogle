/*************************************************
 * Class: Index2 (Hash Table)
 * Owner: Alyssa Rahman
 *************************************************/

#ifndef INDEX2_H
#define INDEX2_H

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

class Index2 {
private:
    char* filename;
    unordered_map<string, set<Entry*> > table;
    set<string> keys, docs;
    Entry* temp;
    void printIDs(string, ofstream&);
    void put(string, string, int); //Adds individual key
public:
    Index2() {
        filename = "output.xml";
        temp = new Entry("temp");
    }

    void add(string, const unordered_map<string, int>&); //Adds all keywords from doc
    void addKey(string, const unordered_map<string, int>&); //Adds all docs for keyword

    unordered_map<string, int> get(string); //Returns weighted docs for given keyword
    char* getFilename() { return filename; }
    set<string> getIDs() { return docs; }
    void setFilename(char*& f) {
        filename = new char[100];
        strcpy(filename, f);
    }

    void printTable();

    ~Index2();
};

#endif // INDEX2_H
