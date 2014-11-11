#include <fstream>
#include "tree.h"
#include "xmlparser.h"

//use time libraries to check detail of algorithm


int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        exit(1);
    }

    Tree * birch = new Tree();
    birch->insert(1, "acorn", "alyssa");
    birch->get();

    //    removeStopwords(argv[1]);

    return 0;
}

void removeStopwords(char* file) {
    const int STOPWORDS_SIZE = 177;

    XMLParser parser;

    parser.ascii(argv[1]);
    parser.readFile(argv[1]);

    return 0;
}
