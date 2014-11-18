#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <string>
using namespace std;

class Article {
private:
    string title, author, id;
public:
    Article(string t, string a, string i) : title(t), author(a), id(i) {}

    void display() { cout << "[!] Don't forget to write this!!" << endl; } /** WRITE THIS **/

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getID() { return id; }
    //string getText() { return text; }
};

#endif // ARTICLE_H
