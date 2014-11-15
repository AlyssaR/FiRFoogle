#ifndef HANDLER_H
#define HANDLER_H

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
        parse = new BabyParser(); //Change to use big boy parser
    }

    bool createIndex(char*); //Accepts XML filename from caller
};

#endif // HANDLER_H
