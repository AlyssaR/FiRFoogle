#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <string>
using namespace std;

class Entry {
private:
    string keyword;
    int docID, weight;
    Entry * next = nullptr;
public:
    Entry(string k, int d, int n = 1) : keyword(k), docID(d),
        weight(n) {}

    void display() { cout << "[!] Don't forget to write this!!" << endl; } /** WRITE THIS **/

    string getKeyword() { return keyword; }
    int getDocID() { return docID; }
    int getWeight() { return weight; }
    Entry* getNext() { return next; }

    void setDocID(int d) { docID = d; }
    void setNext(Entry * n) { next = n; }
    void setWeight(int w) { weight = w; }

    ~Entry() { delete next; }
};

#endif // ENTRY_H
