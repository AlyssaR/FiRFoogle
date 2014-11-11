#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "English_Stem.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class XMLParser
{
private:
    char* filename;
public:
    XMLParser();
    void ascii(char*);
    void readFile(char*);
    void stopwords();
    void stem();
};

#endif // XMLPARSER_H
