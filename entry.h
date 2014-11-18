#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <string>
using namespace std;

class Entry {
private:
    string keyword, docID;
    int weight;
    Entry * next = nullptr;
public:
    Entry(string k, string d, int n = 1) : keyword(k), docID(d),
        weight(n) {}

    string getKeyword() { return keyword; }
    string getDocID() { return docID; }
    int getWeight() { return weight; }
    Entry* getNext() { return next; }

    void setDocID(string d) { docID = d; }
    void setNext(Entry * n) { next = n; }
    void setWeight(int w) { weight = w; }

    ~Entry() { delete next; }
};

#endif // ENTRY_H
