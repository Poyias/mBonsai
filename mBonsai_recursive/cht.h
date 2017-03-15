#ifndef COMPACTHASHTABLE_CHT
#define COMPACTHASHTABLE_CHT

#include "limits.h"
#include "sdsl/int_vector.hpp"
#include <iostream>
class cht {

public:
  // structure
  sdsl::int_vector<0> quotient_items_C;
  sdsl::bit_vector V;

  // init
  cht() {}
  cht(uint64_t universe, uint64_t M, uint32_t sat, uint32_t diff,
      double up = 0.80, double down = 0.60);
  ~cht();
  void resize(uint64_t universe, uint64_t M, uint64_t sat, uint32_t diff,
              double up = 0.80, double down = 0.60);
  void resize();
  uint64_t minorExpand(uint64_t universe, double expandRatio = 0);
  uint64_t minorShrink(uint64_t universe, double shrinkRatio = 0);
  // misc
  uint64_t getModInverse(uint64_t a, uint64_t prime);
  void euclAlgorithm(uint64_t prime);
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);

  // reverse key
  uint64_t getInitAd(uint64_t loc);
  uint64_t getKey(uint64_t loc);

  // API
  bool insert(uint64_t key, uint32_t value);
  bool remove(uint64_t key);
  uint64_t find(uint64_t key);

  uint64_t findByC(uint64_t key);
  uint64_t getStartOfGroup(uint64_t curAddress);
  uint64_t getItemLocation(uint64_t curAddress);
  uint64_t getChangeBitLoc(uint64_t curAddress);
  bool findSpace(uint64_t cVal, uint64_t quotient);
  void startNewBlock(uint64_t vVal, uint64_t cVal);
  // fetch displacement value stored as satelite data
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
  uint64_t satWidth;

private:
  double up_limit, down_limit, expand_shrink_by;
  uint32_t dif;
  uint64_t cmax;
  uint64_t valNotFound;
  uint64_t valExists;
  uint64_t keyNotFound;
  uint64_t sigma;
  uint64_t prime;
  uint64_t a;
  uint64_t aInv;
  uint64_t emptyLoc;
  uint64_t curEmptySlot;
  uint64_t expectedNodes;
};
#endif
