#ifndef BABYPARSER_H
#define BABYPARSER_H

#include "xmlparser.h"
#include <unordered_map>
#include <random>
#include <time.h>

class BabyParser : public XMLParser
{
public:
    BabyParser() { srand(time(NULL)); }
    vector<int> readFile();
    unordered_map<string, int> getKeywords(int);

};

#endif // BABYPARSER_H
