#ifndef HANDLER_H
#define HANDLER_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "index.h"
#include "babyparser.h"

class Handler {
private:
    Index * index;
    BabyParser * parse;
    vector<string> sorted(unordered_map<string, int>); //Sorts docs by weights
public:
    Handler() {
        index = new Index();
        parse = new BabyParser(); //Change to use big boy parser later
    }

    bool addToIndex(char*, char*); //Accepts XML and output filename from caller
    void deleteIndex();
    vector<string> search(vector<string>, vector<string>, vector<string>); //Accepts keywords, returns docs in weighted order

    ~Handler() {
        delete index;
        delete parse;
    }
};

#endif // HANDLER_H
