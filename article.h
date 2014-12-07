/*************************************************
 * Class: Article
 * Owner: Alyssa Rahman
 *************************************************/

#ifndef ARTICLE_H
#define ARTICLE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Article {
private:
    string title, text, id;
    float wordCount;
public:
    Article(string t, string tx, string i, float wc) : title(t), text(tx), id(i), wordCount(wc) {}

    void display() { cout << text << endl; }

    string getTitle() const { return title; }
    string getID() const { return id; }
    string getText() const { return text; }
    float getWordCount() const { return wordCount; }
    void setWordCount(float idf) { wordCount *= idf; }
    void set(string t, string tx, string i) {
        title = t;
        text = tx;
        id = i;
    }
};

#endif // ARTICLE_H
