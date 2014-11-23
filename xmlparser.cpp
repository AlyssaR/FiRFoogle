#include "xmlparser.h"

XMLParser::XMLParser() {
    stopwords = new set<string>{"a", "about", "above", "abroad", "according", "accordingly", "across", "actually", "after",
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
       "haven", "having", "he", "hello", "help", "hence", "her", "here", "hereby",
       "hereupon", "hers", "herself", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit",
       "however", "how", "however", "hundred", "i", "ie", "if", "ignored", "immediate", "in", "inasmuch", "inc",
       "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward",
       "is", "isn", "it", "its", "itself","just", "k", "keep", "keeps", "kept", "know", "known", "knows", "last",
       "lately", "later", "latter", "least", "less", "lest", "let", "like", "liked", "likely", "likewise",
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
       "would", "wouldn", "yes", "yet", "you", "your", "yours", "yourself", "yourselves"};    
}

set<Article*> XMLParser::parseFile(char* filename, Index *&index) {
    string id, text, title;
    set<Article*> documents;
    Article *add = new Article("add", "new", "article");
    try {
        /** Open XML document **/
        rapidxml::file<> file(filename);
        rapidxml::xml_document<> doc;
        doc.parse<0>(file.data());
        rapidxml::xml_node<>* root_node = doc.first_node(), *revision_node;
        if(root_node == 0)
            cout << "ERROR: Improperly formated XML" << endl;

        int x = 1; //Delete later

        /** Loop through all entries in XML file **/
        for(rapidxml::xml_node<>* page_node = root_node->first_node("page"); page_node && x < 1000; page_node = page_node->next_sibling(), x++) {

            if(x%500 == 0)
                cout << "+" << flush;

            /** Get information from individual document **/
            revision_node = page_node->first_node("revision");
            title = page_node->first_node("title")->value();
            text = revision_node->first_node("text")->value();
            id = revision_node->first_node("sha1")->value();

            /** Save text **/
            add->set(title,text,id);
            documents.insert(add);

            /** Call cleaning function and add keywords to index **/
            clean(text);
            index->add(title, keywords);
            keywords.clear();
        }
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }
    return documents;
} //close loadFile

void XMLParser::clean(string &text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower); //make words lowercase

    string word;
    istringstream iss(text);

    while(iss >> word) {
        /** Remove punctuation **/
        if(!(ispunct(word[0]) || ispunct(word[word.size()-1]) || isdigit(word[0])) && isalpha(word[0]))
            keywords[word]++;
    }

    /** Remove stopwords **/
    for(auto word = stopwords->begin(); word != stopwords->end(); word++)
        keywords.erase(*word);

} //close clean
