#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "rapidxml.h"
#include "rapidxml_utils.h"
using namespace std;

class XMLParser {
public:
    XMLParser();
    void parseFile(char*);
    void clean(ofstream&);
    void removePunct(ofstream&);
    void stopwords(string, ofstream&);
    void stem();
};

#endif // XMLPARSER_H
