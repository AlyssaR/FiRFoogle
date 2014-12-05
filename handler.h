#ifndef HANDLER_H
#define HANDLER_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "index2.h"
#include "babyparser.h"

class Handler {
private:
    Index2* index;
    XMLParser* parse;
    set<Article*> documents;
    vector<string> sorted(unordered_map<string, int>&); //Sorts docs by weights
public:
    friend class QueryParser; //To get vector of Articles
    Handler() {
        index = new Index2();
        parse = new XMLParser();
    }

    void addDocs(string doc, unordered_map<string, int> keys) {
        index->add(doc, keys);
    }
    void addKeys(string key, unordered_map<string, int> docs) {
        index->addKey(key, docs);
    }
    bool addToIndex(char*&); //Accepts XML filename from caller
    bool loadIndex();
    void deleteIndex();
    void outputIndex();
    unordered_map<string, int> search(vector<string>&, vector<string>&, vector<string>&); //Accepts keywords, returns docs in weighted order

    ~Handler() {
        string somecommandcrap = "rm -rf ./WikiDump";
        system(somecommandcrap.c_str());
        delete index;
        delete parse;
    }
};

#endif // HANDLER_H
