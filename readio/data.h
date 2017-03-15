#ifndef READIO_DATA
#define READIO_DATA
#include <stdint.h>
#include <stdio.h>

class Transaction {
public:
    uint64_t length;
    uint64_t* t;

    Transaction(uint64_t l)
        : length(l)
    {
        t = new uint64_t[l];
    }
    Transaction(const Transaction& tr);
    ~Transaction() { delete[] t; }
};

class Data {
public:
    Data(char* filename);
    ~Data();
    Transaction* getNext();
    char* fn;

private:
    FILE* in;
    uint64_t current;
};
#endif
