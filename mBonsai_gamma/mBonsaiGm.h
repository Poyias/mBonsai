#ifndef MBONSAIGAMMA_MBONSAIGM
#define MBONSAIGAMMA_MBONSAIGM
#include "../DArray/mBonsai_gamma/blockedDArray.h"
#include "../readio/data.h"
#include "limits.h"
class mBonsaiGm {

public:
  // structure
  sdsl::int_vector<0> quotient;
  blockedDArray D;

  // init
  mBonsaiGm() {}
  mBonsaiGm(uint32_t nodeNumber, uint32_t sigma, double loadFactor, char *file,
            uint32_t blockSize, uint32_t numBlocks);
  void setData(char *file) { data = new Data(file); }

  // build
  void build();
  void insertTrans(Transaction *t);
  uint64_t setAddress(uint64_t initAd, uint32_t DIVM);

  // search benchmarks
  void searchBench(char *file);
  std::vector<uint32_t> getVector(std::string s); // readio
  uint64_t searchItem(uint64_t initAd, uint32_t DIVM);

  // misc
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);

  // args for printing and counting
  uint64_t sigma;
  uint64_t M;
  uint32_t nodeNumberCount;

private:
  uint64_t nodeNotFound;
  uint32_t rootID;
  uint64_t prime;
  uint64_t a;
  uint64_t aInv;
  uint32_t randRootAdrs;
  uint32_t emptyLoc;
  Data *data; // readio
};
#endif
