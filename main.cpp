#include <fstream>
#include "handler.h"
#include "queryparser.h"
#include "xmlparser.h"

void maintain(char*, char*);
void stressTest(char*, char*);
void interactive(char*, char*);

void testParser(char*);
void testIndex(char *, char*);

int main(int argc, char* argv[], int option = 0) {
    if(argc < 3) {
        cerr << "\nERROR: Invalid number of arguments" << endl;
        cerr << "Correct usage: ./a.out input.xml saved_index.xml [optional mode choice]" << endl;
        cerr << "Mode choices:\n"
             << "\t [1] Interactive/User (default)\n"
             << "\t [2] Maintenance\n"
             << "\t [3] Stress Test\n" << endl;
        exit(1);
    }

    argv[3]==NULL?option=1:option=atoi(argv[3]); //If no mode chosen, set to 1

    if(option == 3)
        stressTest(argv[1], argv[2]);
    else if(option == 2)
        maintain(argv[1], argv[2]);
    else if(option == 1)
        interactive(argv[1], argv[2]);
    else
        cerr << "\nInvalid user mode. Please try again.\n" << endl;

//    testParser(argv[1]);
//    testIndex(argv[1], argv[2]);

    return 0;
}

void maintain(char * input, char * output) {
    Handler * index = new Handler();
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

void stressTest(char * input, char * output) {
    cout << "No need to test. You're definitely stressed." << endl;
}

void interactive(char * input, char * output) {
    QueryParser * query = new QueryParser();
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

        results = query->find(search); /*! Note to self: Uh... make this */

        /** Display Search Results **/
        auto iter = results.begin();
        int index = 1;
        do {
            /** Print 5 Results at a Time **/
            for(int x = index; iter != results.end() && x < index+6; iter++, x++) {
                //Print out crap
            }
            cout << "Options:\n'more'\t see next page \n#\t see specific article \n'quit'\t quit"
                 << "\nPlease select an option: ";
            cin >> search;

            /** Input isn't a number, so prepare string for while loop check **/
            if(!atoi(search.c_str())) {
                transform(search.begin(), search.end(), search.begin(), ::tolower); //Lower case input
                index += 5; //Increment index
            }
            /** Display selected article and reprint current list of results **/
            else {
                results[index-1]->display(); //Print article
                search = "more";
            }
        } while(search.compare("more") == 0);

    }

}

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
//    parser.readFile(xml);
}

void testIndex(char* xml, char * output) {
    Handler * index = new Handler();

    index->addToIndex(xml, output);
    vector<string> ands, ors, nots;
    ands.push_back("most");
    ands.push_back("he'll");
    ands.push_back("should");
    ands.push_back("after");
    ands.push_back("again");
    ands.push_back("against");
    nots.push_back("not");
    nots.push_back("nor");
    nots.push_back("cannot");
    nots.push_back("can't");
    ors.push_back("him");
    ors.push_back("her");

    vector<string> searchResults = index->search(ands, ors, nots);
    for(auto result : searchResults)
        cout << "Doc " << result << endl;
}

