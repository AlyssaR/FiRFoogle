#ifndef INDEX_H
#define INDEX_H

#include <cstring>
#include "entry.h"
#include <functional>

class Index {
private:
    Entry **table;
    const int TABLE_SIZE = 128;
    std::hash<char*> hashIt;
public:
    Index();

    int get(char*);
    void put(char*, int);
    void remove(char*);

    ~Index();
};

#endif // INDEX_H
