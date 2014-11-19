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
                rapidxml::xml_node<>* contributor_node = revision_node->first_node("contributor");
                string title = page_node->first_node("title")->value();
                string author = contributor_node->first_node("username")->value();
                string text = revision_node->first_node("text")->value();
                string id = revision_node->first_node("sha1")->value();

                /** Write text out to file to be cleaned **/
                ofstream fout_temp;
                fout_temp.open("temp.txt");
                fout_temp << text;
                fout_temp.close(); //closes "temp.txt" stream

                string filename = "./documents/" + id + ".txt";
                ofstream fout_file;
                fout_file.open(filename.c_str());
                fout_file << "Title: " << title << endl;
                fout_file << "Author: " << author << endl << endl;
                fout_file << "Text: ";

                /** Call cleaning function **/
                clean(fout_file);

                fout_file.close(); //closes "filename" stream


//                // go through the cleaned text and grab each word
//                stringstream stream(text);

//                while(stream.good()) {
//                    string word;
//                    stream >> word;

//                    //clean the text

//                    /*
//                    create second stringstream out of word
//                    since the pre-cleaned word may have had multiple words
//                    that were read in all as one (e.g. "all-one-word" would be
//                    cleaned to "all one word" which is three individual words).
//                    */
//                    stringstream cleaned(word);
//                    while(cleaned.good()) {
//                        cleaned >> word;
//                        /*
//                        put the word in the map if not already there and increment
//                        the word frequency
//                        */
//                    }
//                }
//            }
        }
        catch(exception& e) {
            cout << e.what() << endl;
        }
} //close loadFile

void XMLParser::clean(ofstream &fout_file) {
    removePunct(fout_file);
}

void XMLParser::removePunct(ofstream &fout_file) {

    ifstream fin;
    fin.open("temp.txt");
    if(!fin.is_open()) {
        cout << "ERROR: Could not open file temp.txt" << endl;
        exit(1);
    }

    string word;
    while(fin >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); //make word lowercase
        for (int i = 0;i<word.length();i++) { //removes punctuation
            if (ispunct(word[i]))
                word[i] = ' ';
        }
        istringstream iss(word);
            do {
                string sub;
                iss >> sub;
                cout << sub << " ";
                cout << "(" << word << ")" << endl;
                stopwords(sub, fout_file);
            } while (iss);
    }

        fin.close();
}

void XMLParser::stopwords(string word, ofstream &fout_file) {
    int stopwords_size = 570;
    string stopwords[] = {"a", "about", "above", "abroad", "according", "accordingly", "across", "actually", "after",
                         "afterwords", "again", "against", "ago", "ahead", "aint", "all", "allow", "almost", "alone", "allows",
                         "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst",
                         "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere",
                         "apart", "appear", "appreciate", "appropriate", "are", "aren", "around", "as", "aside", "ask", "asking",
                         "associated", "at", "available", "away", "awfully", "back", "backward", "backwards", "be", "became",
                         "because", "become", "becoming", "been", "before", "beforehand", "began", "begin", "behind", "being",
                         "believe", "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief", "but",
                         "by", "came", "can", "cannot", "caption", "cause", "causes", "certain", "certainly", "changes", "cleary",
                         "c", "co", "com", "come", "comes", "coming", "concerning", "consequently", "consider", "considering",
                         "contain", "containing" "contains", "corresponding", "could", "couldn", "course", "currently", "d", "dare",
                         "daren", "definetly", "described", "despite", "did", "didn", "different", "directly", "div", "do", "does",
                         "doesn", "doing", "done", "don", "down", "downward", "downwards", "during", "each",  "edu", "ed", "eight",
                         "eighty", "either", "else", "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc",
                         "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly",
                         "example", "except", "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five", "follow",
                         "followed", "following", "for", "forever", "former", "formerly", "fourth", "forward", "found", "four",
                         "from", "further", "furthermore", "get", "gets", "getting", "give", "given", "gives", "go", "goes", "going",
                         "gone", "got", "gotten", "had", "hadn", "half", "happens", "hardly", "has", "hasn", "have",
                         "haven", "having", "he", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein",
                         "hereupon", "hers", "herself", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit",
                         "however", "how", "however", "hundred", "i", "ie", "if", "ignored", "immediate", "in", "inasmuch", "inc",
                         "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward",
                         "is", "isn", "it", "its", "itself","just", "k", "keep", "keeps", "kept", "know", "known", "knows", "last",
                         "lately", "later", "latter", "latterly", "least", "less", "lest", "let", "like", "liked", "likely", "likewise",
                         "little", "ll", "look", "looking", "looks", "low", "lower", "m", "made", "mainly", "make", "makes",
                         "many", "may","maybe", "maynt", "me", "mean", "meatime", "meawhile", "mearly", "might", "mightn't", "mine",
                         "minus", "miss","mon", "more", "moreoever", "most", "mostly", "mr", "mrs", "must", "mustn", "my", "myself",
                         "name", "namely", "nd", "near", "nearly", "neccesary", "need", "needn", "needs", "never", "neither",
                         "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless"
                         "noone", "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously",
                         "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "only", "onto", "opposite", "or",
                         "other", "others", "otherwise", "ought", "oughtn", "our", "ours", "ourselves", "out", "outside", "over",
                         "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus"
                         "possible", "presumably", "probably", "provided", "provides", "que", "quite", "qv", "rather", "rd", "re",
                         "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively",
                         "respectively", "right","round", "s", "said", "same", "saw", "say", "saying", "says", "second",
                         "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible",
                         "sent", "serious", "seriously", "seven", "several", "shall" "shan", "she", "should", "shouldn", "since",
                         "six", "so", "some", "somebody","someday", "somehow", "someone", "something", "sometime", "sometimes",
                         "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "sup",
                         "such", "t", "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks", "that",
                         "the", "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby",
                         "therefore", "these", "they", "thing" "things", "thinks", "third", "thirty" "this",
                         "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "til", "to",
                         "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "twice", "two",
                         "un", "under", "under", "underneath", "undoing", "unfortunately", "unless", "unlike" "unlikely" "until",
                         "unto", "up", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value",
                         "various", "ve", "versus", "very", "via", "vs", "want", "wants" "was", "wasn", "way", "we",
                         "we", "welcome", "well", "went", "were", "weren't", "what", "when", "where", "whereupon","wherever"
                         "whether", "which", "whichever", "while", "whilst", "whither", "who", "whomever", "whose", "why", "will",
                         "willing", "wish", "with", "within", "without", "wonder", "won", "would", "wouldn", "whom", "why",
                         "would", "wouldn", "yes", "yet", "you", "your", "yours", "yourself", "yourselves", " ", ""};


    cout << word << endl;
    /** Remove Stopwords **/
        for(int i = 0; i < stopwords_size; i++) {
 //           cout << i << endl;
            if(strcmp(word.c_str(), stopwords[i].c_str()) == 0) { //if the word is a stopword
                i = stopwords_size;
                cout << "!" << word << ": is a stopword" << endl;
            } else if(i == stopwords_size - 1) { //if the word doesn't match any stopwords
              cout << word << ": not a stopword" << endl;
              fout_file << word << " ";
            }
        }
} //close clean
