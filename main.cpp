/*************************************************
 * FiRFoogle
 * Authors:
 *   Alyssa Rahman
 *   Courtney Kent
 * December 8, 2014
 *
 * FiRFoogle is a search engine for wikibooks.
 * For more information on FiRFoogle and how to
 * use it please refer to the User Manual.
 *
 *************************************************/

#include <fstream>
#include <iomanip>
#include <math.h>

#include "handler.h"
#include "queryparser.h"
#include "xmlparser.h"
using namespace std;

void maintain(Handler*);
void stressTest(Handler*);
void interactive(Handler*);
bool byValues(const Article* first, const Article* second) { //Compares by value
    return first->getWordCount() > second->getWordCount();
}

int main(int argc, char* argv[]) {
    Handler* index = new Handler();
    int option;
    argv[1]==NULL?option=1:option = atoi(argv[1]); //If no mode chosen, set to 1

    /** Mode Option **/
    if(option == 3)
        stressTest(index);
    else if(option == 2)
        maintain(index);
    else if(option == 1) {
        index->loadIndex();
        cout << "Press enter to begin searching." << endl;
        interactive(index);
    } else
        cerr << "\nERROR: Invalid user mode. Please try again.\n" << endl;

    return 0;
}

void maintain(Handler* index) {
    char option[2];
    bool hash;

    /** Display Codes Menu**/
    while(true) {
        cout << "    ====================\n"
             << "      Maintenance Mode\n"
             << "    ====================" << endl;
        cout << "Command List:\n"
             << "    AD - Add documents to index\n"
             << "    CL - Clear index\n"
             << "    LD - Load saved index\n"
             << "    OI - Output index\n"
             << "    SR - Search\n"
             << "    QT - Quit\n\n"
             << "Enter Command: ";
        cin >> option;

        /** Enter Code **/
        if(strcmp(option, "AD") == 0) {
            int indexType;
            bool hash;
            /** Option to use AVL tree or hash table **/
            cout << "[1] Use AVL Tree\n"
                 << "[2] Use Hash Table\n"
                 << "Enter option: ";
            cin >> indexType;
            if(indexType == 1)
                hash = false;
            else if(indexType == 2)
                hash = true;
            else
                cerr << "ERROR: Invalid option" << endl;

            /** Get file to add to index **/
            char* file = new char[50];
            cout << "Enter the filename (with path/extension) to read in: ";
            cin >> file;
            index->addToIndex(file, hash);
        }
        else if(strcmp(option, "CL") == 0)
            index->deleteIndex();
        else if(strcmp(option, "LD") == 0)
            index->loadIndex();
        else if(strcmp(option, "OI") == 0)
            index->outputIndex();
        else if(strcmp(option, "SR") == 0)
            interactive(index);
        else if(strcmp(option, "QT") == 0)
            break;
        else
            cout << "\nERROR: Invalid Entry. Please enter valid command.\n" << endl;
    }

}

void stressTest(Handler* index) {
    /** WRITE THIS! **/
}

void interactive(Handler* index) {
    QueryParser* query = new QueryParser(index);
    vector<Article*> results;
    string search;

    /** Enter search query **/
    cin.ignore();
    while(true) {
        cout << " ______ _ _____  ______                _" << endl;
        cout << "|  ____(_)  __ \\|  ____|              | |     " << endl;
        cout << "| |__   _| |__) | |__ ___   ___   __ _| | ___ " << endl;
        cout << "|  __| | |  _  /|  __/ _ \\ / _ \\ / _` | |/ _ \\" << endl;
        cout << "| |    | | | \\ \\| | | (_) | (_) | (_| | |  __/" << endl;
        cout << "|_|    |_|_|  \\_\\_|  \\___/ \\___/ \\__, |_|\\___|" << endl;
        cout << "                                  __/ |" << endl;
        cout << "                                 |____/ " << endl;
        cout << "===============================================" << endl << endl;
        cout << "Example: 'AND Meaning Life'\t (Type -1 to Exit)"
             << "\nSearch: ";
        getline(cin, search);
        if(search.compare("-1") == 0)
            break;

        results = query->find(search);

        /** Display Search Results **/
        int index = 1, size = results.size();
        float idf = log(179708/size);
        for(auto thing : results)
            thing->setWordCount(idf); // Sets wordcount to be TF/IDF
        sort(results.begin(), results.end(), &byValues);

        do {
            cout << "\n    ====================\n"
                 << "\tFiRFoogle\n"
                 << "    ====================" << endl;
            cout << "Total found: " << size << " results" << endl;
            cout << "Viewing Results: " << index << " to " << index + 4 << "\n" << endl;

            /** Print 5 Results at a Time **/
            for(int x = index; x <= size && x < index+5; x++)
                cout << "[" << x << "] " << results[x-1]->getTitle() << endl;

            cout << "\nOptions:\n'more'\t\t see next page \n'back'\t\t see last page"
                 << "\n#\t\t see specific article \n'return'\t Return to search"
                 << "\n-1\t\t quit"
                 << "\n\nPlease select an option: ";
            getline(cin, search);

            /** Input isn't a number, so prepare string for while loop check **/
            if(!atoi(search.c_str())) {
                transform(search.begin(), search.end(), search.begin(), ::tolower); //Lower case input
                if(search.compare("back") == 0) {
                    index -= 5;
                    if(index < 1)
                        index += 5;
                    search = "more";
                }
                else
                    index += 5; //Increment index
            }
            /** If -1, exit **/
            else if(atoi(search.c_str()) == -1)
                exit(0);

            /** Display selected article and reprint current list of results **/
            else {
                cout << "\n=====================================================\n"
                     << "\t" << results[atoi(search.c_str())-1]->getTitle()
                     << "\n=====================================================" << endl;
                results[atoi(search.c_str())-1]->display(); //Print article
                cout << "\nPress any key to return to results.";
                getline(cin, search);
                search = "more";
            }
        } while(search.compare("more") == 0);
    }

}
