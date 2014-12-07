#ifndef HANDLER_H
#define HANDLER_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdio.h>
/***********************************************
 * Class: Handler
 * Owner: Alyssa Rahman
 ***********************************************/

#include <vector>

#include "article.h"
#include "avlindex.h"
#include "index2.h"
#include "xmlparser.h"

class Handler {
private:
    Index2* hashTable;
    AVLIndex* AVLTree;
    XMLParser* parser;
    set<Article*> documents;
    vector<string> sorted(unordered_map<string, int>&); //Sorts docs by weights
public:
    Handler() {
        hashTable = new Index2();
        parser = new XMLParser();
    }

    void addDocs(string doc, unordered_map<string, int> keys) {
        hashTable->add(doc, keys);
    }
    void addKeys(string key, unordered_map<string, int> docs) {
        hashTable->addKey(key, docs);
    }
    void addToIndex(char*&, bool); //Accepts XML filename from caller
    bool loadIndex();
    void deleteIndex();
    void outputIndex();
    unordered_map<string, int> search(vector<string>&, vector<string>&, vector<string>&); //Accepts keywords, returns docs in weighted order

    ~Handler() {
        string somecommandcrap = "rm -rf ./WikiDump";
        system(somecommandcrap.c_str());
        delete hashTable;
        delete parser;
    }
};

#endif // HANDLER_H
