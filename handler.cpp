#include "handler.h"

bool Handler::addToIndex(char*& filename, char*& output) {
    index->setFilename(output);

    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    /** Reads file and returns vector of document ids **/
    start = chrono::system_clock::now();
    deleteIndex();
    documents = parse->read(filename, index);
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;

    cout << "--> File read in: " << elapsed_seconds.count() << "s" << endl;

    string somecommandcrap = "rm -rf ./WikiDump";
    system(somecommandcrap.c_str());

    cout << "[+] Keywords added to index successfully." << endl;
    cout << "--> Keywords added in: " << elapsed_seconds.count() << "s" << endl;

    /** Prints index to file **/
    index->printTable(output);

    return true;
}

vector<string> Handler::search(vector<string>& ands, vector<string>& ors, vector<string>& nots) {
    unordered_map<string, int> results, entries, temp;

    if(ors.size() != 0) {
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
    }

    if(ands.size() != 0) {
        /** Get all AND'd terms **/
        for(auto word : ands) {
            temp = index->get(word);
            for(auto line : temp)
                entries[line.first] += line.second;
        }

        /** Merge AND terms with ORs **/
        for(auto word : entries) {
            if(word.second < 2)
                entries.erase(word.first);
            else
                word.second += results[word.first];
        }
        results = entries;
        entries.clear();
    }

    if(nots.size() != 0) {
        /** Get all NOT terms **/
        for(auto word : nots) {
            temp = index->get(word);
            for(auto line : temp) {
                entries[line.first] += line.second;
            }
        }
        temp = entries;
        entries.clear();

        /** Exclude NOT terms **/
        for(auto word : results) {
            if(temp[word.first] == 0)
                entries[word.first] += word.second;
        }
    }

    return sorted(entries);
}

void Handler::deleteIndex() {
    remove(index->getFilename());
    index = new Index2();

    cout << "[+] Index and all log files have been successfully deleted" << endl;
}

bool byValues(pair<string,int> first, pair<string,int> second) { //Compares by value
    return first.second > second.second;
}

vector<string> Handler::sorted(unordered_map<string, int>& entries) {
    vector<pair<string, int>> pairs(entries.begin(), entries.end());

    sort(pairs.begin(), pairs.end(), &byValues);

    vector<string> justDocs;
    for(auto doc : pairs)
        justDocs.push_back(doc.first);

    return justDocs;
}
