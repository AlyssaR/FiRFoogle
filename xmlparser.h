  #ifndef XMLPARSER_H
#define XMLPARSER_H

#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>

#include "article.h"
#include "avlindex.h"
#include "index2.h" //hash table index
#include "porter2_stemmer.h"
#include "rapidxml.h"
#include "rapidxml_utils.h"
using namespace std;

class XMLParser {
private:
    Index2* index_hash;
    AVLIndex* index_avl;
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
    void parseFile(const char*, const bool);
    set<Article*> read_hash(char*, Index2*&);
    set<Article*> read_AVL(char*, AVLIndex*&);

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
