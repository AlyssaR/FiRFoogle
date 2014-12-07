/*************************************************
 * Class: AVLIndex
 * Owner: Courtney Kent
 *************************************************/

#include "avlindex.h"

/** IN PROGRESS **/


//AVLTreeNode* AVLIndex::createNewNode(const string word, const unordered_map<string, set<Entry*> > table) {
//   AVLTreeNode *temp = new AVLTreeNode();
//   temp->setKeyword(word);
//   temp->setDocAndWeights(table);
//   temp->setLeft(NULL);
//   temp->setRight(NULL);
//   temp->setParent(NULL);
//   temp->setBalanceFactor('=');
//   return temp;
//}

//void AVLIndex::add(string id, unordered_map<string, int> keywords) {
//    /** Add all keywords from document **/
//    docs.insert(id); //Add doc id to set
//    for(auto key : keywords) {
//        keys.insert(key.first); //Add keyword to set
//        table[key.first].insert(new Entry(key.first, key.second)); //Add to index
//    }
//}

//void AVLIndex::addKey(string key, unordered_map<string, int>& theDocs) {
//    /** Add all documents for keyword **/
//    keys.insert(key);
//    for(auto doc : theDocs) {
//        docs.insert(doc.first);
//        //table[key].insert(new Entry(doc.first, doc.second));
//        tree->Insert(createNewNode(key, table));
//    }
//}


//unordered_map<string, int> AVLIndex::get(string keyword) {
//    string docID;
//    unordered_map<string, int> ids;
//    AVLTreeNode node;
//    unordered_map<string, set<Entry*> > group;

//    node = tree->find(keyword, tree->root);
//    unordered_map<string, set<Entry*> >::const_iterator got = table.find(keyword);
//    docID = got->second.getDocID();
//    ids[docID] = got->second.getWeight();

//    return ids;
//}

//void AVLIndex::printIDs(string keyword, ofstream& out) {
//    /** Output keys to index **/
//    out << "<key>" << keyword << endl;
//    node = tree->find(keyword, tree->root);
//    unordered_map<string, set<Entry*> >::const_iterator got = table.find(keyword);

//    unordered_map<string, int> docs = get(keyword);
//    for(auto iter = docs.begin(); iter != docs.end(); ++iter)
//        out << "\t<doc>" << iter->first << "</doc> <weight>"
//             << iter->second << "</weight>" << endl;
//    out  << "</key>" << endl;
//}

//void AVLIndex::printTable() {
//    ofstream out(filename);
//    out << "<index>" << endl;

//    /** Print all keywords, docs, and weights **/
//    for(auto entry : keys)
//        printIDs(entry, out);

//    out << "</index>" << endl;
//    out.close();

//    /** Display completion message **/
//    cout << "[+] Index saved successfully to " << filename << endl;
//}

//AVLIndex::~AVLIndex() {
//    delete filename;
//    /*for(auto item : table) {
//          if(item.second != nullptr) {
//                Entry *prevEntry = nullptr;
//                Entry *entry = item.second;
//                while(entry != nullptr) {
//                     prevEntry = entry;
//                     entry = entry->getNext();
//                     delete prevEntry;
//                }
//          }
//    }*/
//    tree->delete();
//}

