#include "sdsl/coder_elias_gamma.hpp"
#include "sdsl/int_vector.hpp"
#include "sdsl/vlc_vector.hpp"
using namespace sdsl;
using namespace coder;

class gammaBlock{

public:

int_vector<>dBlock ;
gammaBlock(){}
gammaBlock(unsigned int size);
void set(unsigned int loc,unsigned int item);
unsigned int get(unsigned int loc);

};
