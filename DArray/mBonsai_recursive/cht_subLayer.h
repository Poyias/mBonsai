#include "sdsl/int_vector.hpp"
#include <iostream>
using namespace sdsl;
using namespace std;

#ifndef MBONSAIREC_CHTSUB
#define MBONSAIREC_CHTSUB
class cht_subLayer {

public:
  // structure
  int_vector<0> quotient_items_C;
  bit_vector V;
  // init
  cht_subLayer() {}
  cht_subLayer(double perU, uint64_t universe, uint32_t sat, double epsilon,
               uint32_t difference);

  // misc
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);

  void insert(uint64_t key, uint32_t value);
  uint64_t getChangeBitLoc(uint64_t curAddress);
  void findSpace(uint64_t cVal, uint64_t quotient);
  uint64_t find(uint64_t key);
  void startNewBlock(uint64_t vVal, uint64_t cVal);
  uint64_t getSatelite(uint64_t vVal, uint64_t cVal, uint64_t quotients);

  inline void setItem(uint64_t loc, uint64_t quo, uint64_t sat, uint64_t c) {
    quotient_items_C[loc] = (((quo << satWidth) | sat) << 1) | c;
  }
  inline uint64_t getQuo(uint64_t loc) {
    return quotient_items_C[loc] >> (satWidth + 1);
  }
  inline uint64_t getSat(uint64_t loc) {
    return (quotient_items_C[loc] >> 1) & ((1 << satWidth) - 1);
  }
  inline uint64_t getC(uint64_t loc) { return quotient_items_C[loc] & 1; }
  inline bool item_exists(uint64_t loc, uint64_t quotient) {
    return ((quotient_items_C[loc] >> (satWidth + 1)) == quotient);
  }
  inline bool is_empty(uint64_t loc) {
    return ((quotient_items_C[loc] >> (satWidth + 1)) == emptyLoc);
  }
  uint32_t nodeNumberCount;
  uint64_t M;

private:
  uint32_t dif;
  uint64_t cmax;
  uint64_t valNotFound;
  uint64_t sigma;
  uint64_t prime;
  uint64_t a;
  uint64_t aInv;
  uint64_t emptyLoc;
  uint64_t curEmptySlot;
  uint64_t satWidth;
};
#endif