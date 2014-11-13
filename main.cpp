#include <fstream>
#include "index.h"
#include "xmlparser.h"

//use time libraries to check detail of algorithm
void testParser(char*);
void testIndex();

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        exit(1);
    }
    testIndex();
//    testParser(argv[1]);

    return 0;
}

void testParser(char* file) {
    XMLParser parser;
    parser.readFile(file);
}

void testIndex() {
    Index * indice = new Index();

    indice->put("molly", 1);
    indice->put("tom", 2);
    indice->put("molly", 3);
    indice->printIDs("molly");
    indice->printIDs("tom");
}

