#include "gammaBlock.h"
#include "sdsl/int_vector.hpp"


using namespace std;
using namespace sdsl;

class blockedDArray
{
public:

gammaBlock **darray;
unsigned int size;

blockedDArray(){}
blockedDArray(unsigned int size, unsigned int numBlocks);
unsigned int get(unsigned int loc);
void set (unsigned int loc,unsigned int item);
void setT(unsigned int loc,unsigned int item);

};
