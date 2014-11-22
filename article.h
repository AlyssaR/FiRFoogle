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

/*    void display() {
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
    }*/
    void display() { cout << text << endl; }

    string getTitle() const { return title; }
//    string getAuthor() { return author; }
    string getID() const { return id; }
    void set(string t, string tx, string i) {
        title = t;
        text = tx;
        id = i;
    }
};

#endif // ARTICLE_H
