#include "xmlparser.h"

XMLParser::XMLParser() {}

void XMLParser::parseFile(char* filename) {

        try {
            /** Open XML document **/
            rapidxml::file<> file(filename);
            rapidxml::xml_document<> doc;
            doc.parse<0>(file.data());
            rapidxml::xml_node<>* root_node = doc.first_node();
            if(root_node == 0)
                cout << "ERROR: Improperly formated XML" << endl;

            /** Loop through all entries in XML file **/
//            for(rapidxml::xml_node<>* page_node = root_node->first_node("page"); page_node; page_node = page_node->next_sibling()) {

                /** Use instead of for-loop to test one element **/
                rapidxml::xml_node<>* page_node = root_node->first_node("page");

                /** Get information from individual document **/
                rapidxml::xml_node<>* revision_node = page_node->first_node("revision");
                string title = page_node->first_node("title")->value();
                string text = revision_node->first_node("text")->value();
                string id = revision_node->first_node("sha1")->value();

                /** Write text out to file to be cleaned **/
                ofstream fout;
                fout.open("temp.txt");
                fout << text;
                fout.close();

                /** Call cleaning function **/
                stopwords();
//                stem();
//            }
        }
        catch(exception& e) {
            cout << e.what() << endl;
        }
} //close loadFile

void XMLParser::stopwords() {
    ifstream fin;
    fin.open("temp.txt");
    if(!fin.is_open()) {
        cout << "ERROR: Could not open file temp.txt" << endl;
    }
    cout << "Stopwords" << endl;
} //close clean
