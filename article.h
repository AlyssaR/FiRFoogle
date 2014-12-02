#ifndef ARTICLE_H
#define ARTICLE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Article {
private:
    string title, text, id;
public:
    Article(string t, string tx, string i) : title(t), text(tx), id(i) {}

    void display() { cout << text << endl; }

    string getTitle() const { return title; }
    string getID() const { return id; }
    string getText() const { return text; }
    void set(string t, string tx, string i) {
        title = t;
        text = tx;
        id = i;
    }
};

#endif // ARTICLE_H
