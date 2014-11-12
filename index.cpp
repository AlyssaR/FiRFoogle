#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = NULL;
}

int Index::get(int key) {
    int hash = (key % TABLE_SIZE);
    if (table[hash] == NULL)
          return -1;
    else {
          Entry *entry = table[hash];
          while (entry != NULL && entry->getKey() != key)
                entry = entry->getNext();
          if (entry == NULL)
                return -1;
          else
                return entry->getValue();
    }
}

void Index::put(int key, int value) {
    int hash = (key % TABLE_SIZE);
    if (table[hash] == NULL)
          table[hash] = new Entry(key, value);
    else {
          Entry *entry = table[hash];
          while (entry->getNext() != NULL)
                entry = entry->getNext();
          if (entry->getKey() == key)
                entry->setValue(value);
          else
                entry->setNext(new Entry(key, value));
    }
}

void Index::remove(int key) {
    int hash = (key % TABLE_SIZE);
    if (table[hash] != NULL) {
          Entry *prevEntry = NULL;
          Entry *entry = table[hash];
          while (entry->getNext() != NULL && entry->getKey() != key) {
                prevEntry = entry;
                entry = entry->getNext();
          }
          if (entry->getKey() == key) {
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
