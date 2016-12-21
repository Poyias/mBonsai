#include "blockedDArray.h"

blockedDArray::blockedDArray(uint64_t size, uint64_t numBlocks) : size(size) {
  darray = new gammaBlock *[numBlocks];
  for (uint64_t i = 0; i < numBlocks; i++) {
    darray[i] = new gammaBlock(size);
  }
}

uint64_t blockedDArray::get(uint64_t loc) {
  uint64_t gammaBlock = loc / size;
  return darray[gammaBlock]->get(loc % size);
}

void blockedDArray::set(uint64_t loc, uint64_t item) {
  uint64_t gammaBlock = loc / size; // get gammaBlock
  darray[gammaBlock]->set((uint64_t)(loc % size), item);
}
