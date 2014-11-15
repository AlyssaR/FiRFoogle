#ifndef HANDLER_H
#define HANDLER_H

#include <fstream>
#include "index.h"
#include "xmlparser.h"

class Handler {
private:
    Index * index;
    XMLParser * parse;
public:
    Handler() {
        index = new Index();
        parse = new XMLParser(); //Change to use baby parser
    }

    bool createIndex(char*); //Accepts XML filename from caller
};

#endif // HANDLER_H
