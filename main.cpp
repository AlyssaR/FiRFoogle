#include <fstream>
#include "xmlparser.h"

//use time libraries to check detail of algorithm
void testParser(char*);

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        exit(1);
    }

    testParser(argv[1]);
    return 0;
}

void testParser(char* file) {
    XMLParser parser;
    parser.readFile(file);
}

