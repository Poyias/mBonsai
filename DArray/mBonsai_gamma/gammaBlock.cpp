#include "gammaBlock.h"

gammaBlock::gammaBlock(uint64_t size) {
  sdsl::int_vector<> tmp(size, 1);
  sdsl::coder::elias_gamma::encode(tmp, dBlock);
  tmp.bit_resize(0);
}

uint64_t gammaBlock::get(uint64_t loc) {
  uint64_t idx = loc / 1024;
  return (sdsl::coder::elias_gamma::decode<false, false, int *>(
             dBlock.data(), 0, loc + 1 - 1024 * idx)) -
         1;
}

void gammaBlock::set(uint64_t loc, uint64_t item) {
  // decode values in tmp
  sdsl::int_vector<> tmp;
  sdsl::coder::elias_gamma::decode(dBlock, tmp);
  // insert item in location
  tmp[loc] = item + 1;
  // encode tmp in block and delete tmp
  dBlock.resize(0);
  sdsl::coder::elias_gamma::encode(tmp, dBlock);
  tmp.resize(0);
}