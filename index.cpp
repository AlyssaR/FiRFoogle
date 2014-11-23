#include "index.h"

void Index::add(string doc, const unordered_map<string, int>& keywords) {
    docs.insert(doc); //Add doc id to set
    for(auto key : keywords) {
        keys.insert(key.first); //Add keyword to set
        put(doc, key.first, key.second); //Add to index
    }
}

unordered_map<string, int> Index::get(string& keyword) {
    string docID;
    Entry * entry = table[keyword];
    unordered_map<string, int> ids;

    if(entry == nullptr)
        return ids;
    /** If not empty, return all docs in chain with correct key **/
    while (entry != nullptr) {
        /* Not sure if needed for unordered_map collisions yet
         * if(keyword == entry->getKeyword()) { */
            docID = entry->getDocID();
            ids[docID] = entry->getWeight();
        //}
        entry = entry->getNext();
    }
    return ids;
}

void Index::put(string docID, string keyword, int weight) {
    /** Add if first**/
    if(table[keyword] == nullptr)
        table[keyword] = new Entry(docID, weight);
    /** Add to end of key chain. Ha. Keychain. **/
    else {
          Entry *entry = table[keyword];
          while(entry->getNext() != nullptr)
                entry = entry->getNext();
          entry->setNext(new Entry(docID, weight));
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

void Index::printIDs(string& keyword, ofstream& out) {
    out << "<key>" << keyword << "</key>" << endl;
    unordered_map<string, int> docs = get(keyword);
    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
        out << "\t<doc>" << iter->first << "</doc><weight>"
             << iter->second << "</weight>" << endl;
}

void Index::printTable(char *& output) {
    ofstream out(output);
    out << "<index>" << endl;

    /** Print all docs by keyword **/
    for(auto entry : keys)
        printIDs(entry, out);
    out << "</index>" << endl;
    out.close();
    cout << "[+] Index saved successfully to " << output << endl;
}

Index::~Index() {
    delete filename;
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
    table.clear();
}
