#include "index.h"

Index::Index() {
    table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = nullptr;
}

void Index::add(int doc, const map<string, int>& keywords) {
    cout << doc << endl;
    for(auto key : keywords) //Add all keywords in doc
        put(doc, key.first, key.second);
}

map<int, int> Index::get(string keyword) {
    int hash = hashIt(keyword) - 4000000, docID;
    Entry *entry = table[hash];
    map<int, int> ids;

    if (table[hash] == nullptr)
          return ids;
    /** If not empty, return all docs in chain with correct key **/
    while (entry != nullptr) {
        if(keyword == entry->getKeyword()) {
            docID = entry->getDocID();
            ids[docID] = entry->getWeight();
        }
        entry = entry->getNext();
    }
    return ids;
}

void Index::put(int docID, string keyword, int weight) {
    int hash = hashIt(keyword) - 400000000;
    cout << hash << endl;
    /** Add if first**/
    if(table[hash] == nullptr)
        table[hash] = new Entry(keyword, docID, weight);
    /** Add to end of key chain. Ha. Keychain. **/
    else {
          Entry *entry = table[hash];
          while(entry->getNext() != nullptr)
                entry = entry->getNext();
          entry->setNext(new Entry(keyword, docID, weight));
    }
}

/* NOT WRITTEN YET!
 *
 * void Index::remove(string keyword) {
    int hash = hashIt(keyword) - 4000000;
    if(table[hash] != nullptr) {
          Entry *prevEntry = nullptr;
          Entry *entry = table[hash];
          while(entry->getNext() != nullptr && entry->getKeyword() == keyword) {
                prevEntry = entry;
                entry = entry->getNext();
          }
          if(entry->getKeyword() == keyword) {
                if(prevEntry == nullptr) {
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
}*/

void Index::printIDs(string keyword) {
    cout << "<key>" << keyword << "</key>";
    map<int, int> docs = get(keyword);
    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
        cout << "\t<doc>" << iter->first << "</doc><weight>"
             << iter->second << "</weight>" << endl;
    cout << endl;
}

void Index::printTable() {
    for(int x = 0; x < TABLE_SIZE; x++) {
        if(table[x] == nullptr) //Skip empty entries
            continue;
        printIDs(table[x]->getKeyword()); //Print all docs for keyword
    }
}

Index::~Index() {
    for(int x = 0; x < TABLE_SIZE; x++)
          if(table[x] != nullptr) {
                Entry *prevEntry = nullptr;
                Entry *entry = table[x];
                while(entry != nullptr) {
                     prevEntry = entry;
                     entry = entry->getNext();
                     delete prevEntry;
                }
          }
    delete[] table;
}
