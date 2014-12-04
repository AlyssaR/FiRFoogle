/***********************************************
 * FiRFoogle
 * Authors:
 *   Alyssa Rahman
 *   Courtney Kent
 * December 8, 2014
 *
 * FiRFoogle is a search engine for wikibooks.
 * For more information on FiRFoogle and how to
 * use itplease refer to the User Manual.
 *
 ***********************************************/

#include <fstream>
#include "handler.h"
#include "queryparser.h"
#include "xmlparser.h"

void maintain(Handler*);
void stressTest(Handler*);
void interactive(Handler*);

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
        cout << "test" << endl;
        interactive(index);
    } else
        cerr << "\nERROR: Invalid user mode. Please try again.\n" << endl;

    return 0;
}

void maintain(Handler* index) {
    int option;

    /** Display Options Menu **/
    while(true) {
        cout << "    ====================\n"
             << "      Maintenance Mode\n"
             << "    ====================" << endl;
        cout << "Would you like to:\n"
             << "    [1] Add documents to index\n"
             << "    [2] Clear index\n"
             << "    [3] Load saved index\n"
             << "    [4] Output index\n"
             << "    [-1] Quit\n\n"
             << "Select: ";
        cin >> option;
        if(option == -1)
            break;
        else if(option == 1) {
            char* in = new char[50], * out = new char[50];
            cout << "Enter the filename (with path/extension) to read in: ";
            cin >> in;
            index->addToIndex(in);
        }

        /** Select Option **/
        else if(option == 2)
            index->deleteIndex();
        else if(option == 3)
            index->loadIndex();
        else if(option == 4)
            index->outputIndex();
        else
            cout << "\nERROR: Invalid choice. Please try again.\n" << endl;
    }
}

void stressTest(Handler* index) {
    char option[2];

    /** Display Codes Menu**/
    while(true) {
        cout << "    ====================\n"
             << "      Stress Test Mode\n"
             << "    ====================" << endl;
        cout << "Command List:\n"
             << "    AD - Add documents to index\n"
             << "    CL - Clear index\n"
             << "    LD - Load saved index\n"
             << "    OT - Output index\n"
             << "    SR - Search\n"
             << "    QT - Quit\n\n"
             << "Enter Command: ";
        cin >> option;
        if(strcmp(option, "AD") == 0) {
            char* in = new char[50], * out = new char[50];
            cout << "Enter the filename (with path/extension) to read in: ";
            cin >> in;
            index->addToIndex(in);
        }

        /** Enter Code **/
        else if(strcmp(option, "CL") == 0)
            index->deleteIndex();
        else if(strcmp(option, "LD") == 0)
            index->loadIndex();
        else if(strcmp(option, "OT") == 0)
            index->outputIndex();
        else if(strcmp(option, "SR") == 0)
            interactive(index);
        else if(strcmp(option, "QT") == 0)
            break;
        else
            cout << "\nERROR: Invalid Entry. Please enter valid command.\n" << endl;
    }
}

void interactive(Handler* index) {
    QueryParser* query = new QueryParser(index);
    vector<Article*> results;
    string search;

    cin.ignore();
    /** Enter search query **/
    while(true) {
        cout << " ______ _ _____  ______                _" << endl;
        cout << "|  ____(_)  __ \\|  ____|              | |     " << endl;
        cout << "| |__   _| |__) | |__ ___   ___   __ _| | ___ " << endl;
        cout << "|  __| | |  _  /|  __/ _ \\ / _ \\ / _` | |/ _ \\" << endl;
        cout << "| |    | | | \\ \\| | | (_) | (_) | (_| | |  __/" << endl;
        cout << "|_|    |_|_|  \\_\\_|  \\___/ \\___/ \\__, |_|\\___|" << endl;
        cout << "                                  __/ |" << endl;
        cout << "                                  |___/ " << endl;
        cout << "===============================================" << endl << endl;
        cout << "Example: 'AND Meaning Life'\t (Type -1 to Exit)"
             << "\nSearch: ";
        getline(cin, search);
        if(search.compare("-1") == 0)
            break;

        results = query->find(search);

        /** Display Search Results **/
        int index = 1, size = results.size();

        //cin.ignore();
        do {
            cout << "    ====================\n"
                 << "\tFiRFoogle\n"
                 << "    ====================" << endl;
            cout << "Total found: " << size << " results" << endl;
            cout << "Viewing Results: " << index << " to " << index + 4 << "\n" << endl;

            /** Print 5 Results at a Time **/
            for(int x = index; x < size && x < index+5; x++)
                cout << "[" << x << "] " << results.at(x-1)->getTitle() << endl;

            cout << "Options:\n'more'\t\t see next page \n'back'\t\t see last page"
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
                results[index-1]->display(); //Print article
                search = "more";
            }
        } while(search.compare("more") == 0);
    }

}
