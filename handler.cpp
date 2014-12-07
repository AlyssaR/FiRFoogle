#include "handler.h"

void Handler::addToIndex(char*& filename, bool hash) {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    cout << "[+] Adding " << filename <<  " to index" << endl;

    /** Insert files into index using hash table **/
    if(hash == true) {
        set<Article*> temp;
        start = chrono::system_clock::now(); //begin timer
        temp = parser->read_hash(filename, hashTable);
        documents.insert(temp.begin(), temp.end());
        end = chrono::system_clock::now(); //end timer
        elapsed_seconds = end-start;
    } else {
        set<Article*> temp;
        start = chrono::system_clock::now(); //begin timer
        temp = parser->read_AVL(filename, AVLTree);
        documents.insert(temp.begin(), temp.end());
        end = chrono::system_clock::now(); //end timer
        elapsed_seconds = end-start;
    }

    /** Display time taken to insert **/
    cout << "--> File read in: " << elapsed_seconds.count() << "s" << endl;
    cout << "[+] Keywords added to index successfully." << endl;

}

bool Handler::loadIndex() {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    cout << "[+] Loading index" << endl;
    start = chrono::system_clock::now(); //begin timer

    /** Open index file to read in **/
    ifstream in("output.xml");
    if(!in.is_open()) {
        cerr << "ERROR: Unable to find/open output.xml" << endl;
        return false;
    }

    string key, doc, weight;
    int w, x = 1;
    unordered_map<string, int> docAndWeight;

    /** Read in keywords **/
    in >> key;
    while(in >> key && key.compare("</index>") != 0) {
        if(x % 5000 == 0)   //status check
            cout << "+" << flush; //output every 5000 keys
        x++;
        key = key.substr(5, key.size());

        /** Read in weight **/
        while(in >> doc && doc.compare("</key>") != 0) {
            doc = doc.substr(5, doc.size()-11);
            in >> weight;
            w = atoi(weight.substr(8, weight.size()-1).c_str());
            docAndWeight[doc] += w;
        }
        addKeys(key, docAndWeight);
        docAndWeight.clear();
    }
    end = chrono::system_clock::now(); //end timer
    elapsed_seconds = end-start;

    /** Display time take to add keywords **/
    cout << "--> Index loaded in: " << elapsed_seconds.count() << "s" << endl;
    cout << "[+] Keywords added to index successfully." << endl;

}

void Handler::outputIndex() {
    hashTable->printTable();
    int x = 1, y = 1;

    string file = "./Articles/" + to_string(y) + ".txt";

    /** Open files to output documents **/
    ofstream out(file.c_str());
    for(auto thing : documents) {
        if(x % 1001 == 0) { //output 1000 documents per file
            x = 1;
            out.close();
            y++;
            file = "./Articles/" + to_string(y) + ".txt";
            out.open(file.c_str());
        }

        /** Write out documents to files **/
        out << x << " " << thing->getWordCount() << " " << thing->getTitle() << endl;
        out << thing->getText() << "\n<>" << endl;
        x++;
    }

    /** Display completion message **/
    cout << "[+] Articles saved successfully" << endl;
}

unordered_map<string, int> Handler::search(vector<string>& ands, vector<string>& ors, vector<string>& nots) {
    unordered_map<string, int> results, temp, *andy = new unordered_map<string,int>[ands.size()];

    if(ors.size() != 0) {
        /** Get all OR'd terms **/
        for(auto word : ors) {
            temp = hashTable->get(word); //Get index entry
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
            andy[x] = hashTable->get(word);
            x++;
        }
        /** Check each doc with first keyword **/
        for(auto line : andy[0]) {
            /** If it's not in every subsequent map ignore it **/
            if(ands.size() < 2)
                temp[line.first] += line.second;
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
        for(auto word : nots) {
            temp = hashTable->get(word);
            for(auto thing : temp)
                results.erase(thing.first);
        }
    }
    return results;
}

void Handler::deleteIndex() {
    string deCommand = "rm -rf ./Articles";
    system(deCommand.c_str());
    hashTable = new Index2();

    cout << "[+] Index and all log files have been successfully deleted" << endl;
}
