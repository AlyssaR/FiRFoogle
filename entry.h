/*************************************************
 * Class: Entry
 * Owner: Alyssa Rahman
 *************************************************/

#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <string>

using namespace std;

class Entry {
private:
    string docID;
    int weight;
public:
    Entry(string d, int n) : docID(d), weight(n) {}

    string getDocID() { return docID; }
    int getWeight() { return weight; }

    void setDocID(string d) { docID = d; }
    void setWeight(int w) { weight = w; }

    ~Entry() {}
};

#endif // ENTRY_H
