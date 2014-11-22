#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <cstring>
#include <fstream>
#include "index.h" //Temporary probably
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "article.h"
#include "porter2_stemmer.h"
#include "rapidxml.h"
#include "rapidxml_utils.h"
using namespace std;

class XMLParser {
private:
    unordered_map<string, int> keywords;
    int stopwords_size = 568;
    set<string>* stopwords;
public:
    XMLParser();
    set<Article*> parseFile(char*, Index *&);
    void clean(string&);
    void stem();
};

#endif // XMLPARSER_H
