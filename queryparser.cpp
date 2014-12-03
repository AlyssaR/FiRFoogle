#include "queryparser.h"

vector<Article*> QueryParser::find(string& query) {
    vector<string> docIDs;
    vector<string> ands, ors, nots, terms;

    /** Split query into individual words **/
    stringstream stream(query);
    string blah;
    while(stream >> blah) {
        Porter2Stemmer::stem(blah);
        terms.push_back(blah);
    }

    if(terms.size() < 2)
        ands.push_back(terms.at(0));
    else {
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
            else if((*iter).compare("OR") == 0) {
                iter++;
                while(iter != terms.end() && (*iter).compare("AND") != 0 && (*iter).compare("NOT") != 0) {
                    ors.push_back(*iter);
                    iter++;
                }
            }
            else if((*iter).compare("NOT") == 0) {
                iter++;
                while(iter != terms.end() && (*iter).compare("OR") != 0 && (*iter).compare("AND") != 0) {
                    nots.push_back(*iter);
                    iter++;
                }
            }
        }
    }

    /** Get Doc IDs that match those terms **/
    docIDs = index->search(ands, ors, nots);
    getDocInfo(docIDs);

    /** Return a vector of entries with info for those docs **/
    return results;
}

struct find_by_id {
    find_by_id(const string & id) : id(id) {}
    bool operator()(Article * const& article) {
        return (article->getID() == id);
    }
private:
    string id;
};

void QueryParser::getDocInfo(vector<string>& docIDs) {
    set<Article*> articles = index->documents;
    for(auto doc : docIDs) {
        auto it = find_if(articles.begin(), articles.end(), find_by_id(doc));
        if(it != articles.end())
            results.push_back(*it);
    }
}
