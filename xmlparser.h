#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include "rapidxml.h"
#include "rapidxml_utils.h"
using namespace std;
//using namespace tinyxml2;

class XMLParser
{
public:
    XMLParser();
    void parseFile(char*);
    void stopwords();
    void stem();
};

#endif // XMLPARSER_H
