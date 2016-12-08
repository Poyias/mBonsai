#ifndef MBONSAIRECURSIVE_MBONSAI
#define MBONSAIRECURSIVE_MBONSAI
#include "../DArray/mBonsai_recursive/cht_subLayer.h"
#include "../readio/data.h"
#include "limits.h"
#include "sdsl/int_vector.hpp"
class mBonsai {

public:
  sdsl::int_vector<0> quotient_D;
  cht_subLayer cht_sl;                // sublayer displacement array
  std::map<uint32_t, uint32_t> mapSl; // overflown Displacement

  // init
  mBonsai() {}
  mBonsai(uint32_t nodeNumber, uint32_t sigma, double loadFactor, char *file);
  void setData(char *file) { data = new Data(file); }

  // build
  void build();
  void insert(Transaction *t);
  uint64_t setAddress(uint64_t initAd, uint32_t DIVM);
/*
  uint64_t getParent(uint64_t location);
  uint64_t getInitAd(uint64_t);
*/
  // search bencmarks
  void searchBench(char *file);
  std::vector<uint32_t> getVector(std::string s); // readio
  uint64_t searchItem(uint64_t initAd, uint32_t DIVM, uint32_t itemID);

  // misc
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);
  long long getModInverse(long long a, uint64_t prime);
  void euclAlgorithm(uint64_t prime);

  inline uint64_t getQuo(uint64_t loc) { return quotient_D[loc] >> dWidth; }
  inline uint64_t getD(uint64_t loc) {
    return quotient_D[loc] & ((1 << dWidth) - 1);
  }
  inline uint64_t setQuo(uint64_t loc, uint64_t quo) {
    quotient_D[loc] = quo << dWidth;
  }

  inline uint64_t setQuo_D(uint64_t loc, uint64_t quo, uint64_t D) {
    quotient_D[loc] = (quo << dWidth) | D;
  }
  // args for printing and counting
  uint64_t sigma;
  uint64_t M;
  uint32_t nodeNumberCount;
  uint32_t origNodeCount;

private:
  bool singlepath;
  uint64_t rootID;
  uint64_t prime;
  uint64_t a;
  uint64_t aInv;
  uint64_t valNotFound;
  uint64_t randRootAdrs;
  uint64_t emptyLoc;
  uint8_t dWidth;
  Data *data; // readio
};
#endif
