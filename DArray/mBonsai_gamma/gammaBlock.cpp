#include "gammaBlock.h"
#include "sdsl/enc_vector.hpp"
#include "sdsl/vlc_vector.hpp"
#include "sdsl/rank_support.hpp"
#include "sdsl/select_support.hpp"
#include <sdsl/bit_vectors.hpp>
#include "sdsl/int_vector.hpp"
#include "sdsl/vlc_vector.hpp"
#include "sdsl/coder_elias_gamma.hpp"
#include "sdsl/util.hpp"
#include "sdsl/coder.hpp"
#include <iostream>

using namespace sdsl;
using namespace std;
using namespace coder;

gammaBlock::gammaBlock(unsigned int size){
  int_vector <> tmp(size,1);
  coder::elias_gamma::encode(tmp,dBlock);
  tmp.bit_resize(0);
}

unsigned int gammaBlock::get(unsigned int loc){
	unsigned int idx = loc/1024;
	return (coder::elias_gamma::decode<false, false, int*>(dBlock.data(), 0, loc+1 -1024*idx))-1;
}

void gammaBlock::set(unsigned int loc, unsigned int item){
  int_vector<> tmp;
  coder::elias_gamma::decode(dBlock,tmp);
  tmp[loc] = item+1;
  
  dBlock.resize(0);
  
  coder::elias_gamma::encode(tmp,dBlock);
  
  tmp.resize(0);
}


