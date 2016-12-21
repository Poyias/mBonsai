#ifndef MBONSAIRECURSIVE_MBONSAI
#define MBONSAIRECURSIVE_MBONSAI
// #include "../DArray/mBonsai_recursive/cht_subLayer.h"
#include "../readio/data.h"
#include "cht.h"
#include "limits.h"
#include "sdsl/int_vector.hpp"
#include "sdsl/select_support.hpp"
class mBonsai;

class mBonsai_expand {
  friend class mBonsai;

private:
  mBonsai_expand() {}
  mBonsai_expand(uint64_t n, uint64_t M, uint64_t sigma);
  ~mBonsai_expand() {}
  sdsl::int_vector<0> labels;       //= sdsl::int_vector<0>(n,sigma+1,w);
  sdsl::int_vector<0> displ_level1; // = sdsl::int_vector<3>(n,0);
  cht displ_level2;                 // = cht(0.062303, M, 7, 0.25, 7);
  std::map<uint32_t, uint32_t> displ_level3;
  sdsl::select_support_mcl<0, 1> unary_sel;
  sdsl::bit_vector unary_bit; // n+num
  sdsl::int_vector<0> degree_cntr;
};

class mBonsai {
  // friend class mBonsai_expand;

public:
  // args for printing and counting
  uint64_t sigma;
  uint64_t M;
  uint32_t nodeNumberCount;
  uint64_t randRootAdrs;
  sdsl::int_vector<0> quotient_D;
  cht cht_sl;                         // sublayer displacement array
  std::map<uint32_t, uint32_t> mapSl; // overflown Displacement
  // init
  mBonsai() {}
  mBonsai(uint32_t nodeNumber, uint32_t sigma, double loadFactor, char *file);
  ~mBonsai();
  // build
  void build();
  // search bencmarks
  void searchBench(char *file);
  void extendTrie(double expandRatio = 2.0);
  void resize();
  void replace(const mBonsai &other);

private:
  void setData(char *file) { data = new Data(file); }
  void insert(Transaction *t);
  uint64_t setAddress(uint64_t initAd, uint32_t DIVM);
  uint64_t getParent(uint64_t location);
  uint64_t getInitAd(uint64_t);
  std::vector<uint32_t> getVector(std::string s); // readio
  uint64_t searchItem(uint64_t initAd, uint32_t DIVM, uint32_t itemID);
  void inOrderExpand(uint64_t oldParentId, const mBonsai &tmp_mbr,
                     uint64_t newParentId);
  // misc
  bool isPrime(uint64_t input);
  uint64_t nextPrimeNumber(uint64_t inputNumber);
  long long getModInverse(long long a, uint64_t prime);
  void euclAlgorithm(uint64_t prime);
  // access quotient_D
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

  mBonsai_expand mbe;
  Data *data; // readio
  uint64_t getItemLabel(uint64_t loc);
  uint64_t getDisplVal(uint64_t loc);
  uint64_t getDisplVal_tmp(uint64_t loc);
  const uint64_t end_of_l1 = 7;
  const uint64_t end_of_l2 = 134;
  const uint64_t dWidth = 3;
  uint64_t rootID;
  bool singlepath;
  uint64_t prime;
  uint64_t a;
  uint64_t aInv;
  uint64_t valNotFound;
  uint64_t emptyLoc;
};
#endif
