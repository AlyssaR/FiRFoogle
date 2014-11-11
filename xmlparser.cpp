#include "xmlparser.h"

XMLParser::XMLParser() {}

char* XMLParser::lowercase(char* filename) {
    char* buffer;
    int length;

    /** Read in file and convert to ASCII **/
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "ERROR: Unable to open " << filename << "." << endl;
        exit(1);
    }

    /** http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring **/
    /** read ASCII file into char* **/
    fin.seekg(0, ios::end); // go to the end
    length = fin.tellg(); // report location (this is the length)
    fin.seekg(0, ios::beg); // go back to the beginning
    buffer = new char[length]; // allocate memory for a buffer of appropriate dimension
    fin.read(buffer, length); // read the whole file into the buffer
    fin.close();

    /** Make Word Lowercase **/
    for(int i = 0; i < strlen(buffer); i++) {
        char c = buffer[i];
        buffer[i] = tolower(c);
    }
}

void XMLParser::readFile(char* filename) {

    char* fileText = lowercase(filename);

    /** http://rapidxml.sourceforge.net/manual.html#namespacerapidxml_1two_minute_tutorial **/
    /** parse through file **/
    xml_document<> doc; // character type defaults to char
    doc.parse<0>(fileText); // 0 means default parse flags

}

void XMLParser::stopwords() {
    const int STOPWORDS_SIZE = 177;

    char* stopwords[] = {"a", "about", "above", "after", "again", "against", "all" ,"am", "an", "and", "any", "are", "aren't",
                         "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by",
                         "can't", "cannot", "could", "couldn't", "could've", "did", "didn't", "do", "does", "doesn't",
                         "doing","don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has",
                         "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's",
                         "hers", "herself", "him", "himself", "his", "how", "how's", "i","i'd", "i'll", "i'm", "i've", "if",
                         "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't",
                         "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our",
                         "ours", "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's",
                         "should", "shouldn't", "should've", "so", "some", "such", "than", "that", "that's", "the", "their",
                         "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll",
                         "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was",
                         "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when",
                         "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with",
                         "won't", "would", "wouldn't", "would've", "you", "you'd", "you'll", "you're", "you've", "your",
                         "yours", "yourself", "yourselves"};

    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "ERROR: Unable to open " << filename << "." << endl;
        exit(1);
    }

    char *buffer = new char[100], *text = new char[100];

    while(fin >> buffer) {
        //make word lowercase
        for(int i = 0; i < strlen(buffer); i++) {
            char c = buffer[i];
            buffer[i] = tolower(c);
        }
        //compare to stopwords
        for(int i = 0; i < STOPWORDS_SIZE; i++) {
            if(strcmp(buffer, stopwords[i]) == 0)
                break; //break if buffer is a stopword
            else if(strcmp(buffer, stopwords[i]) != 0 && i == STOPWORDS_SIZE - 1) {
                strcat(text, buffer); //if buffer isn't a stopword, add to text
                strcat(text, " "); //Add space between words
            }
        }
    }
    cout << text << endl;
}

void XMLParser::stem() {

//    Porter2Stemmer::stem();
}
