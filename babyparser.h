#ifndef BABYPARSER_H
#define BABYPARSER_H

#include <unordered_map>
#include <random>
#include <time.h>

#include "xmlparser.h"

class BabyParser : public XMLParser
{
public:
    BabyParser() { srand(time(NULL)); }
    vector<string> readFile();
    unordered_map<string, int> getKeywords(string);

};

#endif // BABYPARSER_H
