#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <cstring>
#include <dirent.h>
#include <fstream>
#include "index2.h" //Temporary probably
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "article.h"
#include "porter2_stemmer.h"
#include "rapidxml.h"
#include "rapidxml_utils.h"
#include <stdlib.h>

using namespace std;

class XMLParser {
private:
    Index2 * index;
    rapidxml::xml_document<> doc;
    set<Article*> documents;
    unordered_map<string, int> keywords;
    unordered_map<string, string> stemmed;
    int stopwords_size = 568, fileNum = 1, docNum = 1;
    set<string>* stopwords, filenames;
    Article *add = new Article("add", "new", "article", 0);
public:
    XMLParser();

    void getFilenames();
    void parseFile(const char*);
    set<Article*> read(char*, Index2*&);

    int clean(string&);
    void stem();

    ~XMLParser() {
        for(auto thing : documents)
            delete thing;
        documents.clear();

        delete stopwords;
    }
};

#endif // XMLPARSER_H
