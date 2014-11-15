#ifndef ENTRY_H
#define ENTRY_H

class Entry {
private:
    char* keyword;
    int docID, weight;
    Entry * next;
public:
    Entry(char* k, int d, int n = 1) : keyword(k), docID(d),
        next(nullptr), weight(n) {}

    char* getKeyword() { return keyword; }
    int getDocID() { return docID; }
    int getWeight() { return weight; }
    Entry* getNext() { return next; }

    void setDocID(int d) { docID = d; }
    void setNext(Entry * n) { next = n; }
    void setWeight(int w) { weight = w; }

    ~Entry() { delete next; }
};

#endif // ENTRY_H
