#include "queryparser.h"

QueryParser::QueryParser() {}

vector<Article*> QueryParser::find(string query) {
    vector<string> docIDs;
    vector<string> ands, ors, nots, terms;
    Handler * index = new Handler();

    /** Split query into individual words **/
    stringstream stream(query);
    while(stream >> query)
        terms.push_back(query);

    /** Split groups of terms into separate vectors **/
    vector<string>::iterator iter = terms.begin();
    while(iter != terms.end()) {
        if((*iter).compare("AND") == 0) {
            iter++;
            while(iter != terms.end() && (*iter).compare("OR") != 0 && (*iter).compare("NOT") != 0) {
                ands.push_back(*iter);
                iter++;
            }
        }
        if((*iter).compare("OR") == 0) {
            iter++;
            while(iter != terms.end() && (*iter).compare("AND") != 0 && (*iter).compare("NOT") != 0) {
                ors.push_back(*iter);
                iter++;
            }
        }
        if((*iter).compare("NOT") == 0) {
            iter++;
            while(iter != terms.end() && (*iter).compare("OR") != 0 && (*iter).compare("AND") != 0) {
                nots.push_back(*iter);
                iter++;
            }
        }
    }

    /** Get Doc IDs that match those terms **/
    docIDs = index->search(ands, ors, nots);

    /** Return a vector of entries with info for those docs **/
    return getDocInfo(docIDs);
}

vector<Article*> QueryParser::getDocInfo(vector<string> docIDs) {
    for(auto doc : docIDs) {
        ifstream in("./documents/" + doc + ".txt");

        in.close();
    }
}
