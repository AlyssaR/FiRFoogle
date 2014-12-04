#include "handler.h"

bool Handler::addToIndex(char*& filename) {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    cout << "[+] Adding " << filename <<  " to index" << endl;

    set<Article*> temp;
    /** Reads file and returns vector of document ids **/
    start = chrono::system_clock::now();
    temp = parse->read(filename, index);
    documents.insert(temp.begin(), temp.end());
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;

    cout << "--> File read in: " << elapsed_seconds.count() << "s" << endl;
    cout << "[+] Keywords added to index successfully." << endl;

    return true;
}

bool Handler::loadIndex() {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    cout << "[+] Loading index" << endl;
    start = chrono::system_clock::now();

    ifstream in("output.xml");
    if(!in.is_open()) {
        cerr << "[!] Unable to find/open output.xml" << endl;
        return false;
    }
    string key, doc, weight;
    int w, x = 1;
    unordered_map<string, int> docAndWeight;
    in >> key;
    while(in >> key && key.compare("</index>") != 0) {
        if(x % 5000 == 0)
            cout << "+" << flush;
        x++;
        key = key.substr(5, key.size());
        while(in >> doc && doc.compare("</key>") != 0) {
            doc = doc.substr(5, doc.size()-11);
            in >> weight;
            w = atoi(weight.substr(8, weight.size()-1).c_str());
            docAndWeight[doc] += w;
        }
        addKeys(key, docAndWeight);
        docAndWeight.clear();
    }
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;

    cout << "--> Index loaded in: " << elapsed_seconds.count() << "s" << endl;
    cout << "[+] Keywords added to index successfully." << endl;

}

void Handler::outputIndex() {
    index->printTable();
    int x = 1, y = 1;

    string deCommand = "./Articles/" + to_string(y) + ".txt";
    ofstream out(deCommand.c_str());
    for(auto thing : documents) {
        if(x % 1001 == 0) {
            x = 1;
            out.close();
            y++;
            deCommand = "./Articles/" + to_string(y) + ".txt";
            out.open(deCommand.c_str());
        }
        out << x << " " << thing->getTitle() << endl;
        out << thing->getText() << "\n<>" << endl;
        x++;
    }
    cout << "[+] Articles saved successfully" << endl;
}

vector<string> Handler::search(vector<string>& ands, vector<string>& ors, vector<string>& nots) {
    unordered_map<string, int> results, temp, *andy = new unordered_map<string,int>[ands.size()];

    if(ors.size() != 0) {
        /** Get all OR'd terms **/
        for(auto word : ors) {
            temp = index->get(word); //Get index entry
            for(auto line : temp)
                results[line.first] += line.second;
        }
    }
    temp.clear();

    if(ands.size() != 0) {
        /** Get all AND'd terms **/
        int x = 0;
        /** Save docs/weights in separate maps for each keyword **/
        for(auto word : ands) {
            andy[x] = index->get(word);
            x++;
        }
        /** Check each doc with first keyword **/
        for(auto line : andy[0]) {
            /** If it's not in every subsequent map ignore it **/
            for(int x = 1; x < ands.size(); x++) {
                if(andy[x][line.first] == 0)
                    break;
                else if(x == ands.size() - 1)
                    temp[line.first] += line.second;
            }
        }

        /** Merge AND terms with ORs **/
        for(auto word : temp)
            temp[word.first] += results[word.first];
        results = temp;
        temp.clear();
    }

    if(nots.size() != 0) {
        /** Get all NOT terms **/
        for(auto word : nots)
            temp.insert(index->get(word).begin(), index->get(word).end());

        /** Exclude NOT terms **/
        for(auto word : results) {
            if(temp[word.first] != 0)
                results.erase(word.first);
        }
    }

    return sorted(results);
}

void Handler::deleteIndex() {
    remove(index->getFilename());
    string deCommand = "rm -rf ./Articles";
    system(deCommand.c_str());
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
