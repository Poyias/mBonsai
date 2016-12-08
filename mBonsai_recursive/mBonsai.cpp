#include "mBonsai.h"
#include "../Hash/mBonsaiHash.h"
/*
 * Constructor initialise trie
*/
mBonsai::mBonsai(uint32_t nodeNumber, uint32_t sigma, double loadFactor,
                 char *file)
    : sigma(sigma), M((uint64_t)(nodeNumber) / loadFactor), valNotFound(M + 10),
      dWidth(3), nodeNumberCount(1), origNodeCount(1) {
  srand(time(NULL));
  setData(file);
  uint64_t cmax = sigma * M + (M - 1);
  prime = nextPrimeNumber(cmax);
  euclAlgorithm(prime);
  emptyLoc = sigma + 2;
  rootID = rand() % (sigma - 1);
  uint32_t w = sdsl::bits::hi(emptyLoc) + 1 + dWidth;
  uint64_t initVal = emptyLoc << dWidth;
  quotient_D = sdsl::int_vector<0>(M, initVal, w);
  cht_sl = cht_subLayer(0.062303, M, 7, 0.25, 7);
  randRootAdrs = (long)(rand() % M);
  quotient_D[randRootAdrs] = rootID << dWidth;
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

  long long aTemp = (long long)(0.31 * (double)prime);
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
  hashFunction *key = new hashFunction();
  uint64_t prevInitAd = randRootAdrs;

  for (int i = 0; i < t->length; ++i) {
    key->getKey(prevInitAd, (uint64_t)t->t[i], M, prime, a);
    prevInitAd = setAddress(key->initAd, key->quotient);
  } // end first for
  delete key;
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
      // if (itemID==5) origNodeCount++;
      ++nodeNumberCount;
      if (DCount != 0) {
        if (DCount < 7) {
          setQuo_D(initAd, DIVM, DCount);
        } else if (DCount >= 7 && DCount <= 134) {
          setQuo_D(initAd, DIVM, 7);
          cht_sl.insert(initAd, DCount);
        } else if (DCount > 134) {
          setQuo_D(initAd, DIVM, 7);
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
      if (DCount < 7 || (getD(initAd) < 7)) {
        if (DCount == getD(initAd)) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // sublayer
      } else if (getD(initAd) == 7 && DCount >= 7 && DCount <= 134) {
        uint32_t tmpSat = cht_sl.find(initAd);
        if (tmpSat == 135) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else if ((tmpSat + 7) == DCount) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // final c++ hash map
      } else if (getD(initAd) == 7 && DCount > 134) {
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

/* Search phase
 * Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.
*/
void mBonsai::searchBench(char *file) {
  std::ifstream infile;
  infile.open(file);
  std::vector<uint32_t> str;
  std::string rawData;

  while (getline(infile, rawData)) {
    str = getVector(rawData);
    hashFunction *key = new hashFunction();
    uint64_t prevInitAd = randRootAdrs;

    for (int i = 0; i < str.size(); ++i) {
      key->getKey(prevInitAd, (uint64_t)str[i], M, prime, a);
      prevInitAd = searchItem(key->initAd, key->quotient, str[i]);
    }
    delete key;
    str.clear();
  }
} // end searchBench

/*
 * reads transaction by transaction
 * to be searched
*/
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

/*
 * searches Items if not found prints error
*/
uint64_t mBonsai::searchItem(uint64_t initAd, uint32_t DIVM, uint32_t itemID) {
  uint32_t DCount = 0;
  while (true) {
    // EMPTY LOC so item not Found
    if (getQuo(initAd) == emptyLoc) {
      std::cout
          << "We searched every corner of mame-Bonsai universe. Item is not "
             "found! :("
          << std::endl;
      return valNotFound;
      // check if it alreadey exists
    } else if ((getQuo(initAd) == DIVM) && (initAd != randRootAdrs)) {
      // option for main
      if (DCount < 7 || getD(initAd) < 7) {
        if (DCount == getD(initAd)) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // option for sublayer
      } else if (getD(initAd) == 7 && DCount >= 7 && DCount <= 134) {
        uint32_t tmpSat = cht_sl.find(initAd);
        if (tmpSat == 135) {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        } else if ((tmpSat + 7) == DCount) {
          return initAd;
        } else {
          ++DCount;
          ++initAd;
          if (initAd >= M)
            initAd = 0;
        }
        // final option hash map
      } else if (getD(initAd) == 7 && DCount > 134) {
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

/*uint64_t mBonsai::getInitAd(uint64_t loc) {
  // check if empty
  if (getQuo(loc) == emptyLoc || (loc == randRootAdrs))
    return valNotFound;
  if (getD(loc) < 7)
    return getD(loc);
  uint64_t tmpSat = cht_sl.find(loc);
  if (tmpSat != 135)
    return tmpSat + 7;
  return mapSl.find(loc)->second;
}
*/
/*uint64_t mBonsai::getParent(uint64_t location) {
  uint64_t initAd = getInitAd(location);
  if (initAd == valNotFound)
    return valNotFound;
  hashFunction h;
  return h.recoverParentLoc(initAd, getQuo(location), M, prime, aInv);
}*/
