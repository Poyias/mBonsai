#ifndef MBONSAIGAMMA_GAMMABLOCK
#define MBONSAIGAMMA_GAMMABLOCK
#include "sdsl/coder_elias_gamma.hpp"
#include "sdsl/int_vector.hpp"
#include "sdsl/vlc_vector.hpp"
class gammaBlock {

public:
  sdsl::int_vector<> dBlock;
  gammaBlock() {}
  gammaBlock(uint64_t size);
  void set(uint64_t loc, uint64_t item);
  uint64_t get(uint64_t loc);
};
#endif