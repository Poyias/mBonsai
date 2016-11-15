#include "sdsl/int_vector.hpp"

using namespace std;
using namespace sdsl;
#ifndef DARRAY
#define DARRAY value
class DArray
{
public:

int_vector<3> D;
DArray(){}
DArray(unsigned long long size);

private:

unsigned long long size;
};
#endif
