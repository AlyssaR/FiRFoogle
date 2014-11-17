#include "index.h"

Index::Index() {
    /*table = new Entry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
          table[i] = nullptr;
    */
}

void Index::add(int doc, const map<string, int>& keywords) {
    for(auto key : keywords) //Add all keywords in doc
        put(doc, key.first, key.second);
}

map<int, int> Index::get(string keyword) {
    int hash = hashIt(keyword), docID;
    Entry * entry = table[hash];
    map<int, int> ids;

    if(entry == nullptr)
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
    int hash = hashIt(keyword);
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

void Index::printIDs(string keyword, ofstream& out) {
    out << "<key>" << keyword << "</key>" << endl;
    map<int, int> docs = get(keyword);
    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
        out << "\t<doc>" << iter->first << "</doc><weight>"
             << iter->second << "</weight>" << endl;
}

void Index::printTable(char * output) {
    ofstream out(output);
    out << "<index>" << endl;
    for(auto entry : table)
        printIDs(entry.second->getKeyword(), out); //Print all docs for keyword
    out << "</index>" << endl;
    out.close();
    cout << "[+] Index saved successfully to " << output << endl;
}

Index::~Index() {
    for(auto item : table) {
          if(item.second != nullptr) {
                Entry *prevEntry = nullptr;
                Entry *entry = item.second;
                while(entry != nullptr) {
                     prevEntry = entry;
                     entry = entry->getNext();
                     delete prevEntry;
                }
          }
    }
}
