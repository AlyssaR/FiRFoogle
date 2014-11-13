#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = NULL;
}

int* Index::get(char* keyword) {
    int * ids = new int(TABLE_SIZE), hash = hashIt(keyword);
    ids[0] = -1;
    if (table[hash] == NULL)
          return ids;
    else {
          Entry *entry = table[hash];
          while (entry != NULL && strcmp(entry->getKeyword(), keyword) != 0)
                entry = entry->getNext();
          if (entry == NULL)
                return ids;
          else {
              int x = 0;
              while (entry != NULL) {
                  ids[x] = entry->getDocID();
                  entry = entry->getMore();
                  x++;
              }
              ids[x+1] = -1;
          return ids;
          }
    }
}

void Index::put(char* keyword, int docID) {
    int hash = hashIt(keyword);
    if (table[hash] == NULL)
          table[hash] = new Entry(keyword, docID);
    else {
          Entry *entry = table[hash];
          while (entry->getNext() != NULL && strcmp(entry->getKeyword(),keyword) != 0)
                entry = entry->getNext();
          if (strcmp(entry->getKeyword(),keyword) == 0) {
              while (entry->getMore() != NULL && entry->getDocID() == docID)
                    entry = entry->getMore();
              if(entry->getDocID() == docID)
                  entry->addNumTimes();
              else
                  entry->setMore(new Entry(keyword, docID));
          }
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

void Index::printIDs(char * keyword) {
    int * docs = get(keyword), x = 0;
    cout << keyword << " is in:";
    while(docs[x] > 0) {
        cout << " " << docs[x];
        x++;
    }
    cout << endl;
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
