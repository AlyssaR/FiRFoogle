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
public:
    QueryParser();

    vector<Article*> find(string);
    vector<Article*> getDocInfo(vector<string>);
};

#endif // QUERYPARSER_H
