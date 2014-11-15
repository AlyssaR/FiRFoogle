#include <fstream>
#include "handler.h"
#include "xmlparser.h"

//use time libraries to check detail of algorithm
void testParser(char*);
void testIndex();

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        cerr << "Correct usage: ./a.out input.xml" << endl;
        exit(1);
    }
//    testParser(argv[1]);
    testIndex();

    return 0;
}

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
//    parser.readFile(xml);
}

void testIndex() {
    Handler * index = new Handler();
    index->createIndex();
}

