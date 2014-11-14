#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = NULL;
}

map<int, int> Index::get(char* keyword) {
    int hash = hashIt(keyword) - 4000000, docID;
    map<int, int> ids;
    if (table[hash] == NULL)
          return ids;

    Entry *entry = table[hash];
    while (entry != NULL) {
        if(strcmp(entry->getKeyword(), keyword) == 0) {
            docID = entry->getDocID();
            ids[docID] = entry->getNumTimes();
        }
        entry = entry->getNext();
    }
    return ids;
}

void Index::put(char* keyword, int docID) {
    int hash = hashIt(keyword) - 4000000;

    if(table[hash] == NULL)
          table[hash] = new Entry(keyword, docID);
    else {
          Entry *entry = table[hash];
          while(entry->getNext() != NULL && (strcmp(entry->getKeyword(), keyword) != 0 || entry->getDocID() != docID))
                entry = entry->getNext();
          if(strcmp(entry->getKeyword(), keyword) != 0 && entry->getDocID() == docID)
              entry->addNumTimes();
          else
              entry->setNext(new Entry(keyword, docID));
    }
}

void Index::remove(char* keyword) {
    int hash = hashIt(keyword) - 4000000;
    if (table[hash] != NULL) {
          Entry *prevEntry = NULL;
          Entry *entry = table[hash];
          while (entry->getNext() != NULL && strcmp(entry->getKeyword(), keyword) != 0) {
                prevEntry = entry;
                entry = entry->getNext();
          }
          if (strcmp(entry->getKeyword(), keyword) == 0) {
                if (prevEntry == NULL) {
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

void Index::printIDs(char * keyword) {
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
