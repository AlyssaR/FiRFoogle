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
    Index2 * index;
    XMLParser * parse;
    set<Article*> documents;
    vector<string> sorted(unordered_map<string, int>&); //Sorts docs by weights
public:
    friend class QueryParser; //To get vector of Articles
    Handler() {
        index = new Index2();
        parse = new XMLParser(); //Change to use big boy parser later
    }

    void addDocs(string& doc, unordered_map<string, int>& keys) { index->add(doc, keys); }
    bool addToIndex(char*&, char*&); //Accepts XML and output filename from caller
    void deleteIndex();
    vector<string> search(vector<string>&, vector<string>&, vector<string>&); //Accepts keywords, returns docs in weighted order

    ~Handler() {
        delete index;
        delete parse;
        for(auto doc : documents)
            delete doc;
        documents.clear();
    }
};

#endif // HANDLER_H
