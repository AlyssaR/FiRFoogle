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

    cout << "[+] Keywords added to index successfully." << endl;
    cout << "--> Keywords added in: " << elapsed_seconds.count() << "s" << endl;

    /** Prints index to file **/
    outputIndex(output);

    return true;
}

void Handler::outputIndex(char *& output) {
    index->printTable(output);
    int x = 1, y = 1;

    string deCommand = "./Articles/" + to_string(y) + ".txt";
    ofstream out(deCommand.c_str());
    for(auto thing : documents) {
        if(x % 100 == 0) {
            out.close();
            y++;
            deCommand = "./Articles/" + to_string(y) + ".txt";
            out.open(deCommand.c_str());
        }
        out << x << " " << thing->getID() << endl;
        out << thing->getTitle() << endl;
        out << thing->getText() << endl;
        x++;
    }
}

vector<string> Handler::search(vector<string>& ands, vector<string>& ors, vector<string>& nots) {
    unordered_map<string, int> results, entries, temp;

    if(ors.size() != 0) {
        /** Get all OR'd terms **/
        for(auto word : ors) {
            temp = index->get(word); //Get index entry
            for(auto line : entries)
                results[line.first] += line.second;
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
        for(auto word : entries)
            entries[word.first] += results[word.first];
        results = entries;
        entries.clear();
    }

    if(nots.size() != 0) {
        /** Get all NOT terms **/
        for(auto word : nots) {
            temp = index->get(word);
            for(auto line : temp)
                entries[line.first] = line.second;
        }

        /** Exclude NOT terms **/
        for(auto word : results) {
            if(entries[word.first] != 0)
                results.erase(word.first);
        }
    }

    return sorted(results);
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
