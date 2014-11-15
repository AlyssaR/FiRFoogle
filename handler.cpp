#include "handler.h"

bool Handler::createIndex(char* filename) {
    vector<int> docs = parse->readFile(filename); //Gets vector of document ids
    for(auto id : docs)
        index->add(id, parse->getKeywords(id)); //Add all docs

    return true;
}
