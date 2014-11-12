#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "porter2_stemmer.h"
#include "rapidxml.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
using namespace rapidxml;

class XMLParser
{
private:
    char* filename;
public:
    XMLParser();
    void readFile(char*);
    void stopwords();
    void stem();
};

#endif // XMLPARSER_H
