#include <fstream>
#include "handler.h"
#include "queryparser.h"
#include "xmlparser.h"

void maintain(Handler*);
void stressTest(Handler*);
void interactive(Handler*);

int main(int argc, char * argv[]) {
    Handler* index = new Handler();
    int option;
    argv[1]==NULL?option=1:option = atoi(argv[1]); //If no mode chosen, set to 1

    if(option == 3)
        stressTest(index);
    else if(option == 2)
        maintain(index);
    else if(option == 1) {
        cout << " ______ _ _____  ______                _" << endl;
        cout << "|  ____(_)  __ \\|  ____|              | |     " << endl;
        cout << "| |__   _| |__) | |__ ___   ___   __ _| | ___ " << endl;
        cout << "|  __| | |  _  /|  __/ _ \\ / _ \\ / _` | |/ _ \\" << endl;
        cout << "| |    | | | \\ \\| | | (_) | (_) | (_| | |  __/" << endl;
        cout << "|_|    |_|_|  \\_\\_|  \\___/ \\___/ \\__, |_|\\___|" << endl;
        cout << "                                  __/ |" << endl;
        cout << "                                  |___/ " << endl;
        interactive(index);
    } else
        cerr << "\nInvalid user mode. Please try again.\n" << endl;

    return 0;
}

void maintain(Handler* index) {
    int option;
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
            index->addToIndex(in, false);
        }
        else if(option == 2)
            index->deleteIndex();
        else if(option == 3)
            index->loadIndex();
        else if(option == 4)
            index->outputIndex();
        else
            cout << "\nInvalid choice. Please try again.\n" << endl;
    }
}

void stressTest(Handler* index) {
    char option[2];
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
        if(option == "AD") {
            char* in = new char[50], * out = new char[50];
            cout << "Enter the filename (with path/extension) to read in: ";
            cin >> in;
            index->addToIndex(in, false);
        }
        else if(option == "CL")
            index->deleteIndex();
        else if(option == "LD")
            index->loadIndex();
        else if(option == "OT")
            index->outputIndex();
        else if(option == "SR")
            interactive(index);
        else if(option == "QT")
            break;
        else
            cout << "\nERROR: Invalid Entry. Please enter valid command.\n" << endl;
    }
}

void interactive(Handler* index) {
    index->loadIndex();
    QueryParser* query = new QueryParser(index);
    vector<Article*> results;
    string search;

    /** Enter search query **/
    while(true) {
         cout << "===============================================" << endl << endl;

        cout << "Example: 'AND Meaning Life'\t (Type -1 to Exit)" << endl;
        cout << "\nSearch: ";
        getline(cin, search);
        if(search.compare("-1") == 0)
            break;

        results = query->find(search);

        /** Display Search Results **/
        int index = 1, size = results.size();

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
                 << "\n#\t\t see specific article \n-1\t\t quit"
                 << "\nAnything else\t Return to search"
                 << "\n\nPlease select an option: ";
            cin >> search;

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
        cin.ignore();
    }

}
