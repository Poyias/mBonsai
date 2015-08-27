#include <vector>
#include "data.h"
using namespace std;


Transaction::Transaction(const Transaction &tr)
{
	length = tr.length;
	t = new int[tr.length];
	for(int i=0; i< length; i++) t[i] = tr.t[i];
}

Data::Data(char *filename)
{
	fn = filename;
	current=0;
	in = fopen(fn,"rt");
}

Data::~Data()
{
	if(in) fclose(in);
}

Transaction *Data::getNext()
{
	vector<int> list;
	char c;

	// read row by row, push in list
	do {
		int item=0, pos=0;
		c = getc(in);
		while((c >= '0') && (c <= '9')) {
			item *=10;
			item += int(c)-int('0');
			c = getc(in);
			pos++;
		}
		if(pos) list.push_back(item);
	}while(c != '\n' && !feof(in));

	// if end of file is reached, rewind to beginning for next pass
	if(feof(in)){
		rewind(in);
		return 0;
	}

	// put items in *t
	Transaction *t = new Transaction(list.size());
	for(int i=0; i<int(list.size()); i++)
		t->t[i] = list[i];

	return t;
}

