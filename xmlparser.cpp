#include "xmlparser.h"

XMLParser::XMLParser() {
    stopwords = new set<string>{"a", "about", "above", "abroad", "accord", "across", "actual", "after",
           "afterword", "again", "against", "ago", "ahead", "aint", "all", "allow", "almost", "alone",
           "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst",
           "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anywhere",
           "apart", "appear", "appreciate", "appropriate", "are", "around", "as", "aside", "ask",
           "associated", "at", "available", "away", "awful", "back", "backward", "be", "became",
           "because", "become", "becom", "been", "before", "beforehand", "began", "begin", "behind",
           "believe", "below", "beside", "beside", "best", "better", "between", "beyond", "both", "brief", "but",
           "by", "came", "can", "cannot", "caption", "cause", "causes", "certain", "certainly", "changes", "cleary",
           "c", "co", "com", "come", "comes", "coming", "concerning", "consequently", "consider", "considering",
           "contain", "contains", "corresponding", "could", "couldn", "course", "currently", "d", "dare",
           "definetly", "describ", "despite", "did", "different", "direct", "div", "do", "does",
           "doing", "done", "down", "downward", "dur", "each",  "edu", "ed", "eight",
           "eighty", "either", "else", "elsewhere", "end", "end", "enough", "entire", "especial", "et", "etc",
           "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exact",
           "example", "except", "fair", "far", "farther", "few", "fewer", "fifth", "first", "five", "follow",
           "followed", "following", "for", "forever", "former", "formerly", "fourth", "forward", "found", "four",
           "from", "further", "furthermore", "get", "give", "given", "go", "goe",
           "gone", "got", "gotten", "had", "hadn", "half", "happens", "hardly", "has", "hasn", "have",
           "hav", "he", "hello", "help", "hence", "her", "here", "hereby",
           "hereupon", "hers", "herself", "hi", "him", "himself", "his", "hither", "hopefully", "how",
           "however", "how", "however", "hundred", "i", "ie", "if", "ignore", "immediate", "in", "inasmuch", "inc",
           "indeed", "indicate", "inner", "inside", "insofar", "instead", "into", "inward",
           "is", "it", "its", "itself","just", "k", "keep", "kept", "know", "known", "last",
           "late", "later", "latter", "least", "less", "lest", "let", "like", "lik", "likewise",
           "little", "ll", "look", "low", "lower", "m", "made", "main", "make",
           "many", "may","maybe", "me", "mean", "meatime", "meawhile", "mear", "might", "mine",
           "minus", "miss","mon", "more", "moreoever", "most", "most", "mr", "mrs", "must", "my", "myself",
           "name", "nd", "near", "neccesary", "need", "needs", "never", "neither",
           "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless"
           "noone", "nor", "normally", "not", "noth", "notwithstanding", "novel", "now", "nowhere", "obviously",
           "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "only", "onto", "opposite", "or",
           "other","otherwise", "ought", "our", "ours", "ourselve", "out", "outside", "over",
           "overall", "own", "particular", "past", "per", "perhap", "placed", "please", "plus"
           "possible", "presumab", "probab", "provid", "provide", "que", "quite", "qv", "rather", "rd", "re",
           "real", "reasonab", "recent", "regard", "regardless", "relative",
           "respective", "right","round", "s", "said", "same", "saw", "say", "say", "say", "second",
           "second", "see", "seeing", "seem", "seen", "self", "selve", "sensible",
           "sent", "serious",  "seven", "several", "shall" "shan", "she", "should", "since",
           "six", "so", "some", "somebody","someday", "somehow", "someone", "something", "sometime", "sometimes",
           "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "sup",
           "such", "t", "take", "taken", "tak", "tell", "tend", "th", "than", "thank", "that",
           "the", "their", "them", "themselve", "then", "thence", "there", "thereafter", "thereby",
           "therefore", "these", "they", "thing" "things", "thinks", "third", "thirty" "this",
           "thorough", "those", "though", "three", "through", "throughout", "thru", "thus", "til", "to",
           "together", "too", "took", "toward", "tri", "tries", "tru", "try", "twice", "two",
           "un", "under", "under", "underneath", "undo", "unfortunate", "unless", "unlike", "until",
           "unto", "up", "upward", "us", "use", "used", "useful", "use", "us", "usual", "v", "value",
           "various", "ve", "versus", "very", "via", "vs", "want", "was",  "way", "we",
           "we", "welcome", "well", "went", "were", "what", "when", "where", "whereupon","wherever"
           "whether", "which", "whichever", "while", "whilst", "whither", "who", "whomever", "whose", "why", "will",
           "willing", "wish", "with", "within", "without", "wonder", "won", "would", "whom", "why",
           "would", "yes", "yet", "you", "your", "yourself", "yourselve"};
}

void XMLParser::getFilenames() {
    DIR *directory;
    struct dirent *thedir;
    if((directory  = opendir("WikiDump")) == NULL)
        cout << "Error(" << errno << ") opening " << "WikiDump" << endl;

    while ((thedir = readdir(directory)) != NULL)
        filenames.insert(string(thedir->d_name));
    closedir(directory);
}

void XMLParser::parseFile(const char* filename) {
    string id = "merp", text, title, daREALFileShady;
    daREALFileShady = "./WikiDump/" + string(filename);

    try {
        /** Open XML document **/
        rapidxml::file<> file(daREALFileShady.c_str());
        doc.parse<0>(file.data());

        //if(root_node == 0)
          //  cout << "ERROR: Improperly formated XML" << endl;

        rapidxml::xml_node<>* revision_node;

        /** Loop through all entries in XML file **/
        for(rapidxml::xml_node<>* page_node = doc.first_node()->first_node("page"); page_node; page_node = page_node->next_sibling()) {
            /** Get information from individual document **/
            revision_node = page_node->first_node("revision");
            title = page_node->first_node("title")->value();
            text = revision_node->first_node("text")->value();
            id = revision_node->first_node("sha1")->value();

            /** Save text **/
            documents.insert(new Article(title,text,id));

            /** Call cleaning function and add keywords to index **/
            clean(text);
            index->add(id, keywords);
            keywords.clear();
        }
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }
} //close loadFile

set<Article*> XMLParser::read(char* bigfile, Index2*& i) {
    index = i; //Make sure same index is always used

    string somecommandcrap = "perl splitter.pl " + string(bigfile) + " 1000 80";

    system(somecommandcrap.c_str());
    getFilenames();

    int x = 0;

    /** Parse each baby file **/
    for(auto file : filenames) {
        if(x%4 == 0)
            cout << "+" << flush;
        parseFile(file.c_str());
        x++;
    }

    return documents;
}

void XMLParser::clean(string &text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower); //make words lowercase

    istringstream iss(text);
    string word, after;
    while(iss >> word) {
        for(auto character = word.begin(); character != word.end(); character++) {
            /** Remove crappy stuff **/
            if(!isalpha(*character))
                break;
            /** Add non-crappy stuff **/
            else if(character+1 == word.end()) {
                if(stemmed[word] != "")
                    keywords[stemmed[word]]++;
                else {
                    after = word;
                    Porter2Stemmer::stem(after);
                    stemmed[word] = after;
                    keywords[after]++;
                }
            }
        }
    }
    /** Remove stopwords **/
    for(auto word = stopwords->begin(); word != stopwords->end(); word++)
        keywords.erase(*word);

} //close clean
