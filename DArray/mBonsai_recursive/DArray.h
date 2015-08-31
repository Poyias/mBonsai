#include "sdsl/int_vector.hpp"

using namespace std;
using namespace sdsl;

class DArray
{
public:

int_vector<DARRAYSIZE> D;
DArray(){}
DArray(unsigned long long size);

private:

unsigned long long size;
};
