#ifndef DARRAGH_BONSAI
#define DARRAGH_BONSAI
#include "../Hash/orighashFunc.h"
#include "../readio/data.h"
#include "limits.h"
#include "sdsl/int_vector.hpp"
#include <sdsl/bit_vectors.hpp>

class Bonsai {

public:
  // structure
  sdsl::int_vector<0> quotient;
  sdsl::bit_vector V;
  sdsl::bit_vector C;

  // init
  Bonsai() {}
  Bonsai(uint32_t nodeNumber, uint32_t sigma, double loadFactor, char *file);
  void setData(char *file) { data = new Data(file); }

  // build phase
  void build();
  uint32_t insert(Transaction *t, uint32_t line);
  // navigations collision handling
  uint32_t getAssociatedC(uint32_t curAddress);
  uint32_t findSpace(uint32_t cVal, uint32_t quotient);
  bool itemExists(uint32_t cVal, uint32_t quotient);
  void startNewBlock(uint32_t vVal, uint32_t cVal);
  uint32_t findItem(uint32_t vVal, uint32_t cVal, uint32_t quotient);

  // misc
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);

  // search phase
  void searchBench(char *file);
  std::vector<uint32_t> getVector(std::string s);
  uint32_t search(std::vector<uint32_t> t);

  // args for printing and counting
  uint64_t sigma;
  uint64_t M;
  uint32_t nodeNumberCount;
  uint32_t origNodeCount;

private:
  uint64_t cmax;
  uint64_t noValue;
  uint32_t rootID;
  uint32_t rootLambda;
  uint64_t lambda;
  uint64_t prime;
  uint32_t a;
  uint32_t rootAddress;
  uint32_t emptySymbol;
  uint32_t curEmptySlot;
  Data *data; // readio
};
#endif
