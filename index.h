#ifndef INDEX_H
#define INDEX_H

#include "entry.h"

class Index {
private:
    Entry **table;
    const int TABLE_SIZE = 128;
public:
    Index();

    int get(int);
    int hash(int);
    void put(int, int);
    void remove(int);

    ~Index();
};

#endif // INDEX_H
