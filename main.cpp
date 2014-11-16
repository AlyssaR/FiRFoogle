#include <fstream>
#include "handler.h"
#include "xmlparser.h"

//use time libraries to check detail of algorithm
void testParser(char*);
void testIndex(char * xml, char* output);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        cerr << "Correct usage: ./a.out input.xml output.xml" << endl;
        exit(1);
    }
//    testParser(argv[1]);
    testIndex(argv[1], argv[2]);

    return 0;
}

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
//    parser.readFile(xml);
}

void testIndex(char* xml, char * output) {
    Handler * index = new Handler();
    index->createIndex(xml, output);
}

