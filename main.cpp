#include <fstream>
#include "handler.h"
#include "xmlparser.h"

//use time libraries to check detail of algorithm
void testParser(char*);
void testIndex(char * xml, char* output);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        cerr << "Correct usage: ./a.out input.xml saved_index.xml" << endl;
        exit(1);
    }
//    testParser(argv[1]);
    testIndex(argv[1], argv[2]);

    return 0;
}

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
    parser.readFile(xml);
}

void testIndex(char* xml, char * output) {
    Handler * index = new Handler();
    index->createIndex(xml, output);
/*  Test search query
 *
    vector<string> ands, ors, nots;
    ands.push_back("most");
    ands.push_back("he'll");
    ands.push_back("should");
    ands.push_back("after");
    ands.push_back("again");
    ands.push_back("against");
    nots.push_back("not");
    nots.push_back("nor");
    nots.push_back("cannot");
    nots.push_back("can't");
    ors.push_back("him");
    ors.push_back("her");
*/
    vector<int> searchResults = index->search(ands, ors, nots);
    for(auto result : searchResults)
        cout << "Doc " << result << endl;
}

