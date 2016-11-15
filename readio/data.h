#ifndef DATA
#define DATA
#include <stdio.h>
class Transaction
{
public:

	int length;
	int *t;

	Transaction(int l) : length(l) {t = new int[l];}
	Transaction(const Transaction &tr);
	~Transaction(){delete [] t;}
};

class Data
{
public:
	Data(char *filename);
	~Data();
	Transaction *getNext();
	char *fn;
private:
	FILE *in;
	int current;
};
#endif
