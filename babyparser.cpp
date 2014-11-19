#include "babyparser.h"

vector<string> BabyParser::readFile() {
    vector<string> allTheDocs;
    for(int x = 4; x < 27; x++)
        allTheDocs.push_back(to_string(x));

    cout << "[+] Articles read successfully." << endl;
    return allTheDocs;
}

unordered_map<string, int> BabyParser::getKeywords(string doc) {
    unordered_map<string, int> allTheWords;
    int times = rand()%15 +1, whichWord;
    unordered_map<int, int> used;
    string words[] = {"a", "about", "above", "after", "again", "against", "all" ,"am", "an", "and", "any", "are", "aren't",
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

    for(int x = 0; x < times; x++) {
        whichWord = rand()%177;
        while(used[whichWord] == 4)
            whichWord = rand()%177;
        allTheWords[words[whichWord]] = rand()%9 + 1;
        used[whichWord] = 4;
    }

    ofstream out(doc + ".txt");
    out << "Title: Blah" << endl;
    out << "Author: Bloop\n" << endl;
    out << "Text: Blammy" << endl;
    out.close();

    return allTheWords;
}
