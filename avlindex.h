#ifndef AVLINDEX_H
#define AVLINDEX_H

#include <set>
#include <unordered_map>

#include "avltree.h"
using namespace std;

class AVLIndex{
private:
    char* filename;
    Code203_Tree* tree; //equivelent of table
    set<string> keys, docs;
    //Entry* temp;
    void printIDs(string, ofstream&);
    void put(string, string, int); //Adds individual key
public:
    AVLIndex() { filename - "output.xml"; }

    AVLTreeNode* createNewNode(string&, int&);

    void add(string, unordered_map<string, int>); //Adds all keywords from doc
    void addKey(string, Code203_Tree&); //Adds all docs for keyword

    unordered_map<string, int> get(string); //Returns weighted docs for given keyword
    char* getFilename() { return filename; }
    set<string> getIDs() { return docs; }
    void setFilename(char*& f) {
        filename = new char[100];
        strcpy(filename, f);
    }

    void printTable();

    ~AVLIndex();
};

#endif // AVLINDEX_H
