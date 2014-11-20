#include <fstream>
#include "handler.h"
#include "queryparser.h"
#include "xmlparser.h"

void maintain(Handler*);
void stressTest(Handler*);
void interactive(Handler*);

void testParser(char*);

int main(int argc, char* argv[], int option) {
    if(argc < 3) {
        cerr << "\nERROR: Invalid number of arguments" << endl;
        cerr << "Correct usage: ./a.out input.xml saved_index.xml [optional mode choice]" << endl;
        cerr << "Mode choices:\n"
             << "\t [1] Interactive/User (default)\n"
             << "\t [2] Maintenance\n"
             << "\t [3] Stress Test\n" << endl;
        exit(1);
    }

    Handler * index = new Handler();
    index->addToIndex(argv[1], argv[2]);

    argv[3]==NULL?option=1:option=atoi(argv[3]); //If no mode chosen, set to 1

    if(option == 3)
        stressTest(index);
    else if(option == 2)
        maintain(index);
    else if(option == 1)
        interactive(index);
    else
        cerr << "\nInvalid user mode. Please try again.\n" << endl;

//    testParser(argv[1]);

    return 0;
}

void maintain(Handler * index) {
    int option;
    while(true) {
        cout << "    ====================\n"
             << "      Maintenance Mode\n"
             << "    ====================" << endl;
        cout << "Would you like to:\n"
             << "    [1] Add documents to index\n"
             << "    [2] Clear index\n"
             << "    [-1] Quit\n\n"
             << "Select: ";
        cin >> option;
        if(option == -1)
            break;
        else if(option == 1) {
            char * in = new char[50], * out = new char[50];
            cout << "Enter the filename (with path/extension) to read in: ";
            cin >> in;
            cout << "Enter the filename (with extension) to save index to: ";
            cin >> out;
            index->addToIndex(in, out);
        }
        else if(option == 2)
            index->deleteIndex();
        else
            cout << "\nInvalid choice. Please try again.\n" << endl;
    }
}

void stressTest(Handler * index) {
    cout << "No need to test. You're definitely stressed." << endl;
}

void interactive(Handler * index) {
    QueryParser * query = new QueryParser(index);
    vector<Article*> results;
    string search;

    /** Enter search query **/
    while(true) {
        cout << "    ====================\n"
             << "\tFiRFoogle\n"
             << "    ====================" << endl;
        cout << "Please tell FiRFoogle what you are searching for and press Enter."
             << "\n\t(eg. 'AND Meaning Life')\t (Type -1 to Exit)" << endl;
        cout << "\nSearch: ";
        getline(cin, search);
        if(search.compare("-1") == 0)
            break;

        results = query->find(search);

        /** Display Search Results **/
        auto iter = results.begin();
        int index = 1;
        do {
            cout << "    ====================\n"
                 << "\tFiRFoogle\n"
                 << "    ====================" << endl;
            cout << "Total found: " << results.size() << " results" << endl;
            cout << "Viewing Results: " << index << " to " << index + 4 << "\n" << endl;

            /** Print 5 Results at a Time **/
            for(int x = index; iter != results.end() && x < index+5; iter++, x++)
                cout << "[" << x << "] " << (*iter)->getTitle() << endl;

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

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
//    parser.readFile(xml);
}

