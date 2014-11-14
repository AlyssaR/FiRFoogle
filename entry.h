#ifndef ENTRY_H
#define ENTRY_H

class Entry {
private:
    char* keyword;
    int docID, numTimes;
    Entry * next;
public:
    Entry(char* k, int d, int n = 1) : keyword(k), docID(d),
        numTimes(n), next(nullptr) {}

    char* getKeyword() { return keyword; }
    int getDocID() { return docID; }
    int getNumTimes() { return numTimes; }
    Entry* getNext() { return next; }

    void addNumTimes() { numTimes++; }
    void setDocID(int d) { docID = d; }
    void setNext(Entry * n) { next = n; }

    ~Entry() { delete next; }
};

#endif // ENTRY_H
