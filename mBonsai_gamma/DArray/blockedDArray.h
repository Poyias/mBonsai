#ifndef MBONSAIGAMMA_BLOCKEDDARRAY
#define MBONSAIGAMMA_BLOCKEDDARRAY
#include "gammaBlock.h"
#include "sdsl/int_vector.hpp"
class blockedDArray {
public:
  gammaBlock **darray;
  uint64_t size;

  blockedDArray() {}
  blockedDArray(uint64_t size, uint64_t numBlocks);
  uint64_t get(uint64_t loc);
  void set(uint64_t loc, uint64_t item);
};
#endif
