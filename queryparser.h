#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "entry.h"
#include <vector>
using namespace std;

class QueryParser {
private:
    vector<Entry*> results;
public:
    QueryParser();

    vector<Entry*> find(string);

    ~QueryParser() {
        for(auto item : results)
            delete item;
        results.clear();
    }
};

#endif // QUERYPARSER_H
