#include "index2.h"
Index2::Index2() {
    filename = "output.xml";
    temp = new Entry("blah");
}

void Index2::add(string doc, const unordered_map<string, int>& keywords) {
    docs.insert(doc); //Add doc id to set
    for(auto key : keywords) {
        keys.insert(key.first); //Add keyword to set
        table[key.first].insert(new Entry(doc, key.second)); //Add to index
    }
}

void Index2::addKey(string key, const unordered_map<string, int>& theDocs) {
    keys.insert(key);
    for(auto doc : theDocs) {
        docs.insert(doc.first);
        table[key].insert(new Entry(doc.first, doc.second));
    }
}

unordered_map<string, int> Index2::get(string keyword) {
    string docID;
    unordered_map<string, int> ids;

    /** If not empty, return all docs in chain with correct key **/
    for(auto thing : table[keyword]) {
        docID = thing->getDocID();
        ids[docID] = thing->getWeight();
    }
    return ids;
}

void Index2::printIDs(string keyword, ofstream& out) {
    out << "<key>" << keyword << endl;
    unordered_map<string, int> docs = get(keyword);
    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
        out << "\t<doc>" << iter->first << "</doc> <weight>"
             << iter->second << "</weight>" << endl;
    out  << "</key>" << endl;
}

void Index2::printTable() {
    ofstream out(filename);
    out << "<index>" << endl;

    /** Print all docs by keyword **/
    for(auto entry : keys)
        printIDs(entry, out);

    out << "</index>" << endl;
    out.close();

    cout << "[+] Index saved successfully to " << filename << endl;
}

Index2::~Index2() {
    delete filename;
    /*for(auto item : table) {
          if(item.second != nullptr) {
                Entry *prevEntry = nullptr;
                Entry *entry = item.second;
                while(entry != nullptr) {
                     prevEntry = entry;
                     entry = entry->getNext();
                     delete prevEntry;
                }
          }
    }*/
    table.clear();
}
