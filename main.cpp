#include "xmlparser.h"
#include <iostream>
using namespace std;

//use time libraries to check detail of algorithm


int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        exit(1);
    }

    XMLParser parser;

    parser.ascii(argv[1]);
    parser.readFile(argv[1]);

    return 0;
}

