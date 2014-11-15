#include "handler.h"

bool createIndex(char* filename) {
    ofstream xml(filename);
    if(!xml.is_open()) {
        cerr << "[!] Unable to open file " << filename << "\n"
             << "--> Please check path and try again." << endl;
        return false;
    }

    vector<int> docs = parse->read(xml); //Gets vector of document ids
    for(auto id : docs)
        index.add(id, parse->getKeywords(id));

    return true;
}
