#ifndef ARTICLE_H
#define ARTICLE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Article {
private:
    string title, author, id;
public:
    Article(string t, string a, string i) : title(t), author(a), id(i) {}

    void display() {
        string buffer;
        ifstream in(id + ".txt");
        if(!in.is_open()) {
            cerr << "[!] Unable to open ./documents/" << id << ".txt" << endl;
            return;
        }
        getline(in, buffer); //Skip title
        getline(in, buffer); //Skip author
        getline(in, buffer); //Blank line
        in >> buffer; //Skip "Text:"
        cout << "\n================================" << endl;
        while(getline(in, buffer))
            cout << buffer << endl;
        cout << "================================\n" << endl;
    }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getID() { return id; }
};

#endif // ARTICLE_H
