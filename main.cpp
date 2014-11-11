<<<<<<< HEAD
#include "xmlparser.h"
#include <iostream>
using namespace std;
=======
#include <cstring>
#include <fstream>

#include "tree.h"
>>>>>>> ba1d5e73089937525783e76f923eb21c902139a4

//use time libraries to check detail of algorithm


int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        exit(1);
    }
<<<<<<< HEAD
=======

    Tree * birch = new Tree();
    birch->insert(1, "acorn", "alyssa");
    birch->get();

    //    removeStopwords(argv[1]);

    return 0;
}

void removeStopwords(char* file) {
    const int STOPWORDS_SIZE = 177;
>>>>>>> ba1d5e73089937525783e76f923eb21c902139a4

    XMLParser parser;

    parser.ascii(argv[1]);
    parser.readFile(argv[1]);

    return 0;
}

