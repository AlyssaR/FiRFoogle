#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include "porter2_stemmer.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class XMLParser {
private:
    char* filename;
public:
    XMLParser();
    vector<int> readFile(char*); //Accepts filename and returns doc IDs
    map<string, int> getKeywords(int); //Accepts doc ID and returns keyword/weight map
    void stopwords();
    void stem();
};

#endif // XMLPARSER_H
