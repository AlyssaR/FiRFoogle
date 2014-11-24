#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <cstring>
#include <dirent.h>
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
#include <stdlib.h>

using namespace std;

class XMLParser {
private:
    Index * index;
    set<Article*> documents;
    unordered_map<string, int> keywords;
    int stopwords_size = 568;
    set<string>* stopwords, filenames;
    Article *add = new Article("add", "new", "article");
public:
    XMLParser();

    void getFilenames();
    void parseFile(const char*);
    set<Article*> read(char*, Index*&);

    void clean(string&);
    void stem();

    ~XMLParser() {
        for(auto thing : documents)
            delete thing;
        documents.clear();

        delete stopwords;
    }
};

#endif // XMLPARSER_H
