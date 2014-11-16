#ifndef HANDLER_H
#define HANDLER_H

#include <chrono>
#include <ctime>
#include <fstream>
#include <vector>
#include "index.h"
#include "babyparser.h"

class Handler {
private:
    Index * index;
    BabyParser * parse;
public:
    Handler() {
        index = new Index();
        parse = new BabyParser(); //Change to use big boy parser later
    }

    bool createIndex(char*, char*); //Accepts XML and output filename from caller
    void deleteIndex() { delete index; }
    vector<int> search(vector<string>, vector<string>, vector<string>); //Accepts keywords, returns docs in weighted order
    vector<int> sorted(map<int, int>); //Sorts docs by weights

    ~Handler() {
        delete index;
        delete parse;
    }
};

#endif // HANDLER_H
