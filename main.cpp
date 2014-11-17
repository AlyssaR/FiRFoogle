#include <fstream>
#include "handler.h"
#include "xmlparser.h"

void maintain(char*, char*);
void mainMenu();
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
        else if(option == 1)
            //Add files to index
            cout << "Add file here" << endl;
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
    cout << "Why are you here? It's de-fault of no one but you." << endl;
}

void mainMenu() {
    cout << "    ====================\n"
         << "\t FiRFoogle\n"
         << "    ====================" << endl;

    cout << "[1] Interactive/User (default)\n"
         << "[2] Maintenance\n"
         << "[3] Stress Test\n"
         << "[-1] to Quit" << endl;

    cout << "\nPlease select a mode: ";
}

void testParser(char* xml) {
    XMLParser parser;
//    parser.splitFile(xml);
//    parser.readFile(xml);
}

void testIndex(char* xml, char * output) {
    Handler * index = new Handler();
    index->createIndex(xml, output);

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

    vector<int> searchResults = index->search(ands, ors, nots);
    for(auto result : searchResults)
        cout << "Doc " << result << endl;
}

