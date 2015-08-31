#include "gammaBlock.h"


gammaBlock::gammaBlock(unsigned int size){
  int_vector <> tmp(size,1);
  coder::elias_gamma::encode(tmp,dBlock);
  tmp.bit_resize(0);
}

unsigned int gammaBlock::get(unsigned int loc){
	unsigned int idx = loc/1024;
	return (coder::elias_gamma::decode<false, false, int*>(dBlock.data(), 0, loc+1 -1024*idx))-1;
}

void gammaBlock::set(unsigned int loc, unsigned int item)
{
	// decode values in tmp
	int_vector<> tmp;
	coder::elias_gamma::decode(dBlock,tmp);
	//insert item in location
	tmp[loc] = item+1;
	// encode tmp in block and delete tmp
	dBlock.resize(0);
	coder::elias_gamma::encode(tmp,dBlock);
	tmp.resize(0);
}


