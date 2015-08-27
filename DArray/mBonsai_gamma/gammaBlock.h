#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

#include <sstream>
#include <cstring>
#include <vector>  
#include <cmath>

#include "sdsl/int_vector.hpp"
#include "sdsl/enc_vector.hpp"
#include "sdsl/vlc_vector.hpp"
#include "sdsl/rank_support.hpp"
#include "sdsl/select_support.hpp"
#include <sdsl/bit_vectors.hpp>
#include <queue>
#include <stack>

using namespace std;
using namespace sdsl;


#include "sdsl/enc_vector.hpp"
#include <sdsl/bit_vectors.hpp>
#include "sdsl/coder_elias_gamma.hpp"
#include "sdsl/bit_vectors.hpp"
using namespace coder;

class gammaBlock{

public:

  int_vector<>dBlock ;


gammaBlock(){}
gammaBlock(unsigned int size);
void set(unsigned int loc,unsigned int item);
unsigned int get(unsigned int loc);

};
