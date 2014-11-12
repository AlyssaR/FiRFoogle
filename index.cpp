#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = NULL;
}

int Index::get(char* keyword) {
    int hash = hashIt(keyword);
    if (table[hash] == NULL)
          return -1;
    else {
          Entry *entry = table[hash];
          while (entry != NULL && strcmp(entry->getKeyword(), keyword) != 0)
                entry = entry->getNext();
          if (entry == NULL)
                return -1;
          else
                return entry->getDocID();
    }
}

void Index::put(char* keyword, int docID) {
    int hash = hashIt(keyword);
    if (table[hash] == NULL)
          table[hash] = new Entry(keyword, docID);
    else {
          Entry *entry = table[hash];
          while (entry->getNext() != NULL)
                entry = entry->getNext();
          if (strcmp(entry->getKeyword(),keyword) == 0)
                entry->setDocID(docID);
          else
                entry->setNext(new Entry(keyword, docID));
    }
}

void Index::remove(char* keyword) {
    int hash = hashIt(keyword);
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
