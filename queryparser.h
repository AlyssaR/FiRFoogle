/*************************************************
 * Class: QueryParser
 * Owner: Alyssa Rahman
 *************************************************/

#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include <fstream>
#include <sstream>
#include <vector>

#include "article.h"
#include "entry.h"
#include "handler.h"
using namespace std;

class QueryParser {
private:
    vector<Article*> results;
    Handler* index;
public:
    QueryParser(Handler* i) : index(i) {}

    vector<Article*> find(string&);
    Article* getArticle(string, int);
    void getDocInfo(unordered_map<string, int>&);

    ~QueryParser() {
        delete index;
        for(auto entry : results)
            delete entry;
        results.clear();
    }
};

#endif // QUERYPARSER_H
