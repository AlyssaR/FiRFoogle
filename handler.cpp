#include "handler.h"

bool Handler::createIndex(char* filename, char* output) {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds, total;

    start = chrono::system_clock::now();
    vector<int> docs = parse->readFile(); //Gets vector of document ids
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    total = elapsed_seconds;

    cout << "--> File read in: " << elapsed_seconds.count() << "s" << endl;

    start = chrono::system_clock::now();
    for(auto id : docs)
        index->add(id, parse->getKeywords(id)); //Add all docs
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    total += elapsed_seconds;

    cout << "[+] Keywords added to index successfully." << endl;
    cout << "--> Keywords added in: " << elapsed_seconds.count() << "s" << endl;

    index->printTable(output);
    cout << "\n--> All tasks completed in: " << elapsed_seconds.count() << "s" << endl;

    return true;
}
