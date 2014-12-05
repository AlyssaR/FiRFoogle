#ifndef HANDLER_H
#define HANDLER_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <vector>

#include "article.h"
#include "index2.h"
#include "xmlparser.h"

class Handler {
private:
    Index2* index;
    XMLParser* parser;
    set<Article*> documents;
    vector<string> sorted(unordered_map<string, int>&); //Sorts docs by weights
public:
    Handler() {
        index = new Index2();
        parser = new XMLParser();
    }

    void addDocs(string doc, unordered_map<string, int> keys) {
        index->add(doc, keys);
    }
    void addKeys(string key, unordered_map<string, int> docs) {
        index->addKey(key, docs);
    }
    void addToIndex(char*&); //Accepts XML filename from caller
    bool loadIndex();
    void deleteIndex();
    void outputIndex();
    unordered_map<string, int> search(vector<string>&, vector<string>&, vector<string>&); //Accepts keywords, returns docs in weighted order

    ~Handler() {
        string somecommandcrap = "rm -rf ./WikiDump";
        system(somecommandcrap.c_str());
        delete index;
        delete parser;
    }
};

#endif // HANDLER_H
