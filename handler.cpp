#include "handler.h"

bool Handler::createIndex(char* filename, char* output) {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds, total;

    /** Reads file and returns vector of document ids **/
    start = chrono::system_clock::now();
    vector<int> docs = parse->readFile();
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    total = elapsed_seconds;

    cout << "--> File read in: " << elapsed_seconds.count() << "s" << endl;

    /** Adds keywords from all docs to index **/
    start = chrono::system_clock::now();
    for(auto id : docs)
        index->add(id, parse->getKeywords(id)); //Add all docs
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    total += elapsed_seconds;

    cout << "[+] Keywords added to index successfully." << endl;
    cout << "--> Keywords added in: " << elapsed_seconds.count() << "s" << endl;

    /** Prints index to file **/
    index->printTable(output);
    cout << "\n--> All tasks completed in: " << elapsed_seconds.count() << "s" << endl;

    return true;
}

vector<int> Handler::search(vector<string> ands, vector<string> ors, vector<string> nots) {
    map<int, int> results, entries, temp;

    /** Get all OR'd terms **/
    for(auto word : ors) {
        entries = index->get(word); //Get index entry
        for(auto line : entries) {
            if(results[line.first] == 0)
                results[line.first] = line.second;
            else
                results[line.first] += line.second;
        }
    }
    entries.clear();

    /** Get all AND'd terms **/
    for(auto word : ands) {
        temp = index->get(word);
        for(auto line : temp) {
            if(entries[line.first] == 0)
                entries[line.first] = line.second;
            else
                results[line.first] += line.second;
        }
    }
    /** Merge AND terms with ORs **/
    for(auto word : entries) {
        if(results[word.first] != 0)
            word.second += results[word.first];
    }
    results = entries;
    entries.clear();

    /** Get all NOT terms **/
    for(auto word : nots) {
        temp = index->get(word);
        for(auto line : temp) {
            if(entries[line.first] == 0)
                entries[line.first] = line.second;
            else
                results[line.first] += line.second;
        }
    }
    temp = entries;
    entries.clear();

    /** Exclude NOT terms **/
    for(auto word : results) {
        if(temp[word.first] == 0)
            entries[word.first] = word.second;
    }

    return sorted(entries);
}

bool inOrder(pair<int,int> first, pair<int,int> second) { //Compares by value
    return first.second > second.second;
}

vector<int> Handler::sorted(map<int, int> entries) {
    vector<pair<int, int>> pairs(entries.begin(), entries.end());

    sort(pairs.begin(), pairs.end(), &inOrder);

    vector<int> justDocs;
    for(auto doc : pairs)
        justDocs.push_back(doc.first);

    return justDocs;
}
