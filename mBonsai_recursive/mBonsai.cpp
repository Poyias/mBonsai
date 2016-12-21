#include "mBonsai.h"
#include "../Hash/mBonsaiHash.h"
using namespace std;
/*
 * Constructor initialise trie
*/
mBonsai::mBonsai(uint32_t nodeNumber, uint32_t sigma, double loadFactor,
                 char *file)
    : sigma(sigma), M((uint64_t)(nodeNumber) / loadFactor), valNotFound(M + 10),
      nodeNumberCount(1) {
  srand(time(NULL));
  setData(file);
  uint64_t cmax = sigma * M + (M - 1);
  prime = nextPrimeNumber(cmax);
  euclAlgorithm(prime);
  emptyLoc = sigma + 2;
  rootID = 1;
  uint32_t w = sdsl::bits::hi(emptyLoc) + 1 + dWidth;
  uint64_t initVal = emptyLoc << dWidth;
  quotient_D = sdsl::int_vector<0>(M, initVal, w);
  cht_sl =
      cht(M, 1.25 * ((double)M * 0.062303) + 1.0, (1 << dWidth) - 1, end_of_l1);

  randRootAdrs = 4; //(long)(rand() % M);
  quotient_D[randRootAdrs] = rootID << dWidth;
  cout << "M: " << M << endl;
}

// A naive method to find modulor multiplicative inverse of
// 'a' under modulo 'm'
long long mBonsai::getModInverse(long long a, uint64_t prime) {
  a = a % prime;
  for (long long x = 1; x < prime; x++)
    if ((a * x) % prime == 1)
      return x;
  return -1;
}

void mBonsai::euclAlgorithm(uint64_t prime) {

  long long aTemp = (long long)(0.66 * (double)prime);
  long long aInvTemp = -1;
  while (true) {
    aInvTemp = getModInverse(aTemp, prime);
    if (aInvTemp == -1)
      aTemp++;
    else
      break;
  }
  a = aTemp;
  aInv = aInvTemp;
}
/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool mBonsai::isPrime(uint64_t input) {
  uint32_t i;
  bool prime = true;
  if (input == 2) {
    return true;
  }
  if (input % 2 == 0 || input <= 1) {
    prime = false;
  } else {
    for (i = 3; i <= sqrt(input); i += 2) {
      if (input % i == 0) {
        prime = false;
      }
    }
  }
  return prime;
} // end isPrime

/*
 * Function for determining the next prime number
 */
uint64_t mBonsai::nextPrimeNumber(uint64_t inputNumber) {
  uint64_t nextPrimeNumber;
  if (inputNumber <= 0) {
  } else {
    while (inputNumber != 0) {
      nextPrimeNumber = inputNumber + 1;
      if (nextPrimeNumber % 2 == 0 && nextPrimeNumber != 2) {
        nextPrimeNumber += 1;
      }
      while (!isPrime(nextPrimeNumber)) {
        nextPrimeNumber += 2;
      }
      if (isPrime(nextPrimeNumber))
        return nextPrimeNumber;
    }
  }
  return nextPrimeNumber;
} // end nextPrimeNumber

/*
 * It goes through the dataset transaction by transaction
*/
void mBonsai::build() {
  while (Transaction *t = data->getNext()) {
    insert(t);
    delete t;
  }
  delete data;
}
/*
 * called in build()
 * param: transaction of items where trans[0] is parent of trans[1] and so on.
 * it calculates hashkey for every item and calls the setAddress
 */
void mBonsai::insert(Transaction *t) {
  singlepath = false;
  hashFunction *key2 = new hashFunction();
  uint64_t prevInitAd = randRootAdrs;

  for (int i = 0; i < t->length; ++i) {
    key2->getKey(prevInitAd, (uint64_t)t->t[i], M, prime, a);
    prevInitAd = setAddress(key2->initAd, key2->quotient);
  } // end first for
  delete key2;
} // end of insert

/*
 * called by insert
 * it sets the quotient value in the correct location
 * It handles displacement value accordingly
 * returns the hash loc so the next item (its child) can use it
 */
uint64_t mBonsai::setAddress(uint64_t initAd, uint32_t DIVM) {
  uint32_t DCount = 0;
  while (true) {
    // EMPTY LOC soo insert
    if (getQuo(initAd) == emptyLoc && (initAd != randRootAdrs)) {
      singlepath = true;
      ++nodeNumberCount;
      if (DCount != 0) {
        if (DCount < end_of_l1) {
          setQuo_D(initAd, DIVM, DCount);
        } else if (DCount >= end_of_l1 && DCount <= end_of_l2) {
          setQuo_D(initAd, DIVM, end_of_l1);
          cht_sl.insert(initAd, DCount);
        } else if (DCount > end_of_l2) {
          setQuo_D(initAd, DIVM, end_of_l1);
          mapSl.insert(std::pair<uint32_t, uint32_t>(initAd, DCount));
        }
      } else {
        setQuo(initAd, DIVM);
      }
      return initAd;
      // check if it already exists
    } else if ((getQuo(initAd) == DIVM) && (singlepath == false) &&
               (initAd != randRootAdrs)) {
      // option for main
      if (DCount < end_of_l1 || (getD(initAd) < end_of_l1)) {
        if (DCount == getD(initAd)) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // sublayer
      } else if (getD(initAd) == end_of_l1 && DCount >= end_of_l1 &&
                 DCount <= end_of_l2) {
        uint32_t tmpSat = cht_sl.find(initAd);
        if (tmpSat == end_of_l2 + 1) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else if ((tmpSat + end_of_l1) == DCount) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // final c++ hash map
      } else if (getD(initAd) == end_of_l1 && DCount > end_of_l2) {
        if (mapSl.find(initAd) == mapSl.end() ||
            mapSl.find(initAd)->second != DCount) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else {
          return initAd; // mapSl.find(initAd)->second;
        }
      }
      // NOT EMPTY_LOC and NOT SAME_DIV.. MOVE_ON then
    } else {
      ++DCount;
      ++initAd;
      if (initAd >= M)
        initAd = 0;
    }
  } // end while
} // end setAddress

/* Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.*/
void mBonsai::searchBench(char *file) {
  std::ifstream infile;
  infile.open(file);
  std::vector<uint32_t> str;
  std::string rawData;

  while (getline(infile, rawData)) {
    str = getVector(rawData);
    hashFunction *key2 = new hashFunction();
    uint64_t prevInitAd = randRootAdrs;

    for (int i = 0; i < str.size(); ++i) {
      key2->getKey(prevInitAd, (uint64_t)str[i], M, prime, a);
      prevInitAd = searchItem(key2->initAd, key2->quotient, str[i]);
    }
    delete key2;
    str.clear();
  }
} // end searchBench

/* reads transaction by transaction
 * to be searched */
std::vector<uint32_t> mBonsai::getVector(std::string s) {
  char *cstr, *p;
  std::vector<uint32_t> items;
  cstr = new char[s.size() + 1];
  strcpy(cstr, s.c_str());
  p = strtok(cstr, " ");
  while (p != NULL) {
    items.push_back(atoi(p));
    p = strtok(NULL, " ");
  }
  delete[] cstr;
  return items;
} // end getVector

/* searches Items if not found prints error*/
uint64_t mBonsai::searchItem(uint64_t initAd, uint32_t DIVM, uint32_t itemID) {
  uint32_t DCount = 0;
  while (true) {
    // EMPTY LOC so item not Found
    if (getQuo(initAd) == emptyLoc) {
      cout << "We searched every corner of mame-Bonsai universe. Item is not "
              "found! :(  "
           << initAd << " " << itemID << endl;
      return valNotFound;
      // check if it alreadey exists
    } else if ((getQuo(initAd) == DIVM) && (initAd != randRootAdrs)) {
      // option for main
      if (DCount < end_of_l1 || getD(initAd) < end_of_l1) {
        if (DCount == getD(initAd)) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // option for sublayer
      } else if (getD(initAd) == end_of_l1 && DCount >= end_of_l1 &&
                 DCount <= end_of_l2) {
        uint32_t tmpSat = cht_sl.find(initAd);
        if (tmpSat == end_of_l2 + 1) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else if ((tmpSat + end_of_l1) == DCount) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // final option hash map
      } else if (getD(initAd) == end_of_l1 && DCount > end_of_l2) {
        if (mapSl.find(initAd) == mapSl.end() ||
            mapSl.find(initAd)->second != DCount) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else {
          return initAd;
        }
      }
      // NOT EMPTY_LOC NOT SAME_DIV move to next one
    } else {
      ++DCount;
      ++initAd;
      if (initAd >= M)
        initAd = 0;
    }
  } // end while
} // end searchItem

uint64_t mBonsai::getInitAd(uint64_t loc) {
  if (getQuo(loc) == emptyLoc)
    return valNotFound;
  if (getD(loc) < end_of_l1)
    return (loc + M - getD(loc)) % M;
  uint64_t tmpSat = cht_sl.find(loc);
  if (tmpSat != 135)
    return (loc + M - (tmpSat + end_of_l1)) % M;
  return (loc + M - mapSl.find(loc)->second) % M;
}

uint64_t mBonsai::getParent(uint64_t loc) {
  uint64_t initAd = getInitAd(loc);
  if (initAd == valNotFound)
    return valNotFound;
  hashFunction h;
  return h.recoverParentLoc(initAd, getQuo(loc), M, prime, aInv);
}
uint64_t mBonsai::getItemLabel(uint64_t loc) {
  uint64_t initAd = getInitAd(loc);
  if (initAd == valNotFound)
    return valNotFound;
  if (loc == randRootAdrs)
    return rootID;
  hashFunction h;
  uint64_t label = h.recoverID(initAd, getQuo(loc), M, prime, aInv);
  return label;
}

mBonsai_expand::mBonsai_expand(uint64_t n, uint64_t M, uint64_t sigma) {
  uint32_t w = sdsl::bits::hi(sigma) + 1;
  degree_cntr = sdsl::int_vector<0>(M, 0, w);
  unary_bit = sdsl::bit_vector(M + n + 1);
  labels = sdsl::int_vector<0>(n, sigma + 1, w);
  displ_level1 = sdsl::int_vector<0>(n, 0, 3);
  displ_level2 = cht(n, 1.25 * ((double)n * 0.062303) + 1.0, 7, 7);
}

void mBonsai::extendTrie(double expandRatio = 2.0) {
  auto begin = std::chrono::high_resolution_clock::now();
  uint64_t n = nodeNumberCount;
  // 1) create degree_cntr array of Mlogsigma
  mbe = mBonsai_expand(n, M, sigma);
  for (uint64_t i = 0; i < M; ++i) {
    if (getQuo(i) != emptyLoc && i != randRootAdrs) {
      uint64_t parLoc = getParent(i);
      if (parLoc != valNotFound)
        mbe.degree_cntr[parLoc]++;
    }
  } // end for 1

  // 2) represent mbe.degree_cntr in unary bit_vec of M+n bits
  uint64_t offset = 0;
  for (uint64_t i = 0; i < M; ++i) {
    uint64_t end_of_unary = offset + mbe.degree_cntr[i];
    while (offset < end_of_unary)
      mbe.unary_bit[offset++] = 1;
    mbe.unary_bit[offset++] = 0;
  } // end for 2
  for (uint64_t i = 0; i < M; ++i) {
    mbe.degree_cntr[i] = 0;
  } // end for 3
  // create select of unary bit
  mbe.unary_sel = sdsl::select_support_mcl<0, 1>(&mbe.unary_bit);

  // print time
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - begin;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "init degree_counter(1) + init unary bitvector(2) + init "
               "select(3)+initlabels tmpDaray\n[ "
            << ns / 1000000000 << " s]" << std::endl;

  // step 2 ->start insertion to n mbe.labels
  begin = std::chrono::high_resolution_clock::now(); // wall time
  uint64_t label, parLoc, labelPos, displValue;
  for (uint64_t i = 0; i < M; ++i) {
    if (!(getQuo(i) == emptyLoc || i == randRootAdrs)) {
      label = getItemLabel(i);
      parLoc = getParent(i) + 1;
      labelPos =
          mbe.unary_sel.select(parLoc) - parLoc - mbe.degree_cntr[parLoc - 1];
      mbe.degree_cntr[parLoc - 1]++; // increase offset
      displValue = getDisplVal(i);   // get_D from original DArray
      // insert D in temp DArray
      if (displValue < end_of_l1) {
        mbe.displ_level1[labelPos] = displValue;
      } else if (displValue >= end_of_l1 && displValue <= end_of_l2) {
        mbe.displ_level1[labelPos] = end_of_l1;
        mbe.displ_level2.insert(labelPos, displValue);
      } else {
        mbe.displ_level1[labelPos] = end_of_l1;
        mbe.displ_level3.insert(
            std::pair<uint32_t, uint32_t>(labelPos, displValue));
      }
      mbe.labels[labelPos] = label; // insert label
    }
  } // end for 4
  end = std::chrono::high_resolution_clock::now();
  dur = end - begin;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "set labels and displ_values in labels and displ array\n[ "
            << ns / 1000000000 << " s]" << std::endl;

  // expand temp data structure
  // step 3 -> traverse old insert in new
  // inorder traversal
  mBonsai tmp_mbr(n * expandRatio, sigma, 0.8, ":p");
  begin = std::chrono::high_resolution_clock::now(); // wall time
  inOrderExpand(randRootAdrs, tmp_mbr, tmp_mbr.randRootAdrs);
  end = std::chrono::high_resolution_clock::now();
  dur = end - begin;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "init new tmp Bonsai + traverse old and insert into new replace "
               "old with new\n[ "
            << ns / 1000000000 << " s]" << std::endl;
  resize();
  replace(tmp_mbr);
}

void mBonsai::inOrderExpand(uint64_t oldParentId, const mBonsai &tmp_mbr,
                            uint64_t newParentId) {
  const uint64_t parent = oldParentId;
  const uint64_t newParent = newParentId;
  hashFunction key;
  uint64_t label, labelPos;
  uint64_t initLabel = mbe.unary_sel.select(parent + 1) - (parent + 1);
  // stop when siblings finish
  while (mbe.degree_cntr[parent] != 0) {
    mbe.degree_cntr[parent]--;
    labelPos = initLabel - mbe.degree_cntr[parent];
    label = mbe.labels[labelPos];
    // calc old child ID
    key.getKey(parent, label, M, prime, a);
    oldParentId = (key.initAd + getDisplVal_tmp(labelPos)) % M;
    // calc new child ID
    key.getKey(newParent, label, tmp_mbr.M, tmp_mbr.prime, tmp_mbr.a);
    newParentId = tmp_mbr.setAddress(key.initAd, key.quotient);
    // pass them as parents
    inOrderExpand(oldParentId, tmp_mbr, newParentId);
  }
}

uint64_t mBonsai::getDisplVal(uint64_t loc) {
  if (getD(loc) < end_of_l1)
    return getD(loc);
  uint64_t tmpSat = cht_sl.find(loc);
  if (tmpSat != end_of_l2 + 1)
    return (tmpSat + end_of_l1);
  return mapSl.find(loc)->second;
}
uint64_t mBonsai::getDisplVal_tmp(uint64_t loc) {
  if (mbe.displ_level1[loc] < end_of_l1)
    return mbe.displ_level1[loc];
  uint64_t tmpSat = mbe.displ_level2.find(loc);
  if (tmpSat != end_of_l2 + 1)
    return (tmpSat + end_of_l1);
  return mbe.displ_level3.find(loc)->second;
}

void mBonsai::replace(const mBonsai &other) {
  sigma = other.sigma;
  M = other.M;
  valNotFound = other.valNotFound;
  // dWidth = other.dWidth;
  prime = other.prime;
  a = other.a;
  aInv = other.aInv;
  emptyLoc = other.emptyLoc;
  rootID = other.rootID;
  uint32_t w = sdsl::bits::hi(emptyLoc) + 1 + dWidth;
  uint64_t initVal = emptyLoc << dWidth;
  quotient_D = sdsl::int_vector<0>(M, initVal, w);
  cht_sl =
      cht(M, 1.25 * ((double)M * 0.062303) + 1.0, (1 << dWidth) - 1, end_of_l1);
  randRootAdrs = other.randRootAdrs;
  mapSl = other.mapSl;
  for (uint64_t i = 0; i < M; ++i) {
    quotient_D[i] = other.quotient_D[i];
  }
  for (uint64_t i = 0; i < cht_sl.M; ++i) {
    cht_sl.quotient_items_C[i] = other.cht_sl.quotient_items_C[i];
  }
  for (uint64_t i = 0; i < cht_sl.M; ++i) {
    cht_sl.V[i] = other.cht_sl.V[i];
  }
  other.resize();
}

mBonsai::~mBonsai() {
  quotient_D.resize(0);
  cht_sl.resize();
  mapSl = std::map<uint32_t, uint32_t>();
}
void mBonsai::resize() {
  quotient_D.resize(0);
  cht_sl.resize();
  mapSl = std::map<uint32_t, uint32_t>();
}