#ifndef ENTRY_H
#define ENTRY_H

class Entry {
private:
    int key, value;
    Entry * next;
public:
    Entry(int k, int v) : key(k), value(v), next(nullptr) {}

    int getKey() { return key; }
    int getValue() { return value; }
    void setValue(int v) { value = v; }
    Entry* getNext() { return next; }
    void setNext(Entry * n) { next = n; }

    ~Entry() { delete next; }
};

#endif // ENTRY_H
