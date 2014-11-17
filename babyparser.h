#ifndef BABYPARSER_H
#define BABYPARSER_H

#include "xmlparser.h"
#include <map>
#include <random>
#include <time.h>

class BabyParser : public XMLParser
{
public:
    BabyParser() { srand(time(NULL)); }
    vector<int> readFile();
    map<string, int> getKeywords(int);

};

#endif // BABYPARSER_H
