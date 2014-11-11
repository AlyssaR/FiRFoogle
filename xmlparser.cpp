#include "xmlparser.h"

XMLParser::XMLParser() {}

void XMLParser::ascii(char* filename) {
    char* temp;

    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "ERROR: Unable to open " << filename << "." << endl;
        exit(1);
    }
    /** Convert file to ascii **/
    wstring s((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    string asciiText(s.begin(), s.end());
    cout << asciiText;
    //    wcstombs(temp, s, s.size());
}

void XMLParser::readFile(char* filename) {
    char* buffer = " ";

    /** Open Filestream **/
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "ERROR: Unable to open " << filename << "." << endl;
        exit(1);
    }

    fin.ignore(4897);
    for(int i = 0; i < 6; i++)  //ignore lines that aren't needed
        fin.ignore(numeric_limits<streamsize>::max(), ' ');
    fin.getline(buffer, 10, '>');

    fin.close();
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

}
