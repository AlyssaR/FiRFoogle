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
public:
    QueryParser();

    vector<Article*> find(string);
    void getDocInfo(vector<string>);

    ~QueryParser() {
        for(auto entry : results)
            delete entry;
        results.clear();
    }
};

#endif // QUERYPARSER_H
