#include "queryparser.h"

vector<Article*> QueryParser::find(string& query) {
    unordered_map<string, int> docIDs;
    vector<string> ands, ors, nots, terms;

    cout << endl;
    /** Split query into individual words **/
    transform(query.begin(), query.end(), query.begin(), ::tolower); //make words lowercase
    stringstream stream(query);
    string blah;
    while(stream >> blah) {
        Porter2Stemmer::stem(blah);
        terms.push_back(blah);
    }

    if(terms.size() < 2)
        ands.push_back(terms[0]);
    else {
        /** Split groups of terms into separate vectors **/
        vector<string>::iterator iter = terms.begin();
        while(iter != terms.end()) {
            if((*iter).compare("and") == 0) {
                iter++;
                while(iter != terms.end() && (*iter).compare("or") != 0 && (*iter).compare("not") != 0) {
                    ands.push_back(*iter);
                    iter++;
                }
            }
            else if((*iter).compare("and") == 0) {
                iter++;
                while(iter != terms.end() && (*iter).compare("and") != 0 && (*iter).compare("not") != 0) {
                    ors.push_back(*iter);
                    iter++;
                }
            }
            else if((*iter).compare("not") == 0) {
                iter++;
                while(iter != terms.end() && (*iter).compare("or") != 0 && (*iter).compare("and") != 0) {
                    nots.push_back(*iter);
                    iter++;
                }
            }
        }
    }

    /** Get Doc IDs that match those terms **/
    results.clear();
    docIDs = index->search(ands, ors, nots);
    getDocInfo(docIDs);

    /** Return a vector of entries with info for those docs **/
    return results;
}

Article* QueryParser::getArticle(string id, int weight) {
    string title, text, temp, docID, docNum, filename, wordCount;
    float wc;

    filename = "./Articles/" + id.substr(0, id.find('_')) + ".txt";
    docNum = id.substr(id.find('_') + 1, id.size());

    ifstream in(filename.c_str());
    if(!in.is_open()) {
        cerr << "[!] Could not open " << filename << endl;
        return (new Article("error", "error", "error", 0));
    }
    while(!in.eof() && docID.compare(docNum) != 0) {
        in >> docID;
        in >> wordCount;
        getline(in, title);
        text = "";
        while(true) {
            getline(in, temp, '>');
            text = text + temp;
            if(text[text.size()-1] == '<' || temp == " ") {
                text = text.substr(0, text.size() - 2);
                break;
            }
        }
    }
    in.close();
    wc = float(weight)/float(atoi(wordCount.c_str()));
    return (new Article(title,text,id,wc));
}

void QueryParser::getDocInfo(unordered_map<string, int>& docIDs) {
    for(auto doc : docIDs)
        results.push_back(getArticle(doc.first, doc.second));
}
