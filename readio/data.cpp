#include "data.h"
#include <vector>
using namespace std;

Transaction::Transaction(const Transaction &tr) {
  length = tr.length;
  t = new uint64_t[tr.length];
  for (uint64_t i = 0; i < length; i++)
    t[i] = tr.t[i];
}

Data::Data(char *filename) {
  fn = filename;
  current = 0;
  in = fopen(fn, "rt");
}

Data::~Data() {
  if (in)
    fclose(in);
}

Transaction *Data::getNext() {
  vector<uint64_t> list;
  char c;

  // read row by row, push in list
  do {
    uint64_t item = 0, pos = 0;
    c = getc(in);
    while ((c >= '0') && (c <= '9')) {
      item *= 10;
      item += int(c) - int('0');
      c = getc(in);
      pos++;
    }
    if (pos)
      list.push_back(item);
  } while (c != '\n' && !feof(in));

  // if end of file is reached, rewind to beginning for next pass
  if (feof(in)) {
    rewind(in);
    return 0;
  }

  // put items in *t
  Transaction *t = new Transaction(list.size());
  for (uint64_t i = 0; i < uint64_t(list.size()); i++)
    t->t[i] = list[i];

  return t;
}
