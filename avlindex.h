/*************************************************
 * Class: AVLIndex
 * Owner: Courtney Kent
 *************************************************/

#ifndef AVLINDEX_H
#define AVLINDEX_H

#include <cstring>
#include <set>
#include <string>
#include <unordered_map>

#include "avltree.h"
#include "entry.h"
using namespace std;

class AVLIndex{
private:
    string filename;
    Code203_Tree* tree; //equivalent of table
    set<string> keys, docs;
    //Entry* temp;
    void printIDs(string, ofstream&);
    void put(string, string, int); //Adds individual key
public:
    AVLIndex() {
        filename = "output.xml";
    }

    AVLTreeNode* createNewNode(const string, const unordered_map<string, set<Entry*> >);

    void add(string, unordered_map<string, int>); //Adds all keywords from doc
    void addKey(string, unordered_map<string, int>&); //Adds all docs for keyword

    unordered_map<string, int> get(string); //Returns weighted docs for given keyword
    string getFilename() { return filename; }
    set<string> getIDs() { return docs; }
    void setFilename(char*& f) {
        filename = string(f);
    }

    void printTable();

    ~AVLIndex();
};

#endif // AVLINDEX_H
