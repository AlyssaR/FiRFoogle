#ifndef HANDLER_H
#define HANDLER_H

#include <chrono>
#include <ctime>
#include <fstream>
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
};

#endif // HANDLER_H
