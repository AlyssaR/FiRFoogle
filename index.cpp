#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = NULL;
}

void Index::add(int doc, const map<string, int>& keys) {
    /** Finish at some point in life **/
}

map<int, int> Index::get(string keyword) {
    int hash = hashIt(keyword) - 4000000, docID;
    map<int, int> ids;
    if (table[hash] == NULL)
          return ids;

    Entry *entry = table[hash];
    while (entry != NULL) {
        if(keyword == entry->getKeyword()) {
            docID = entry->getDocID();
            ids[docID] = entry->getWeight();
        }
        entry = entry->getNext();
    }
    return ids;
}

void Index::put(int docID, string keyword, int weight) {
    int hash = hashIt(keyword) - 4000000;

    if(table[hash] == NULL)
          table[hash] = new Entry(keyword, docID, weight);
    else {
          Entry *entry = table[hash];
          while(entry->getNext() != nullptr)
                entry = entry->getNext();
          entry->setNext(new Entry(keyword, docID, weight));
    }
}

void Index::remove(string keyword) {
    int hash = hashIt(keyword) - 4000000;
    if (table[hash] != NULL) {
          Entry *prevEntry = NULL;
          Entry *entry = table[hash];
          while (entry->getNext() != NULL && entry->getKeyword() == keyword) {
                prevEntry = entry;
                entry = entry->getNext();
          }
          if(entry->getKeyword() == keyword) {
                if(prevEntry == NULL) {
                     Entry *nextEntry = entry->getNext();
                     delete entry;
                     table[hash] = nextEntry;
                } else {
                     Entry *next = entry->getNext();
                     delete entry;
                     prevEntry->setNext(next);
                }
          }
    }
}

void Index::printIDs(string keyword) {
    cout << keyword << " is in:";
    map<int, int> docs = get(keyword);
    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
        cout << " " << iter->first << " (" << iter->second << ")";
    cout << endl;
}

void Index::printTable() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(table[i] == nullptr)
            continue;
        printIDs(table[i]->getKeyword());
    }
}

Index::~Index() {
    for (int i = 0; i < TABLE_SIZE; i++)
          if (table[i] != NULL) {
                Entry *prevEntry = NULL;
                Entry *entry = table[i];
                while (entry != NULL) {
                     prevEntry = entry;
                     entry = entry->getNext();
                     delete prevEntry;
                }
          }
    delete[] table;
}
