#include "Bonsai.h"

Bonsai::Bonsai(uint32_t nodeNumber, uint32_t alphabet, double loadFactor,
               char *file)
    : sigma(alphabet + 1), M((nodeNumber * 1) / (loadFactor)), noValue(M + 10),
      nodeNumberCount(1), origNodeCount(1), lambda(32) {
  srand(time(NULL));
  setData(file);
  cmax = (((lambda * (sigma - 1)) + lambda - 1) * M) + (M - 1);
  prime = nextPrimeNumber(cmax);
  a = ULONG_MAX / prime;
  emptySymbol = lambda * sigma + 2;
  rootID = (uint32_t)lambda * sigma + 1;
  rootLambda = 0;
  uint32_t w = sdsl::bits::hi(emptySymbol) + 1;
  quotient = sdsl::int_vector<0>(M, emptySymbol, w);
  V = sdsl::bit_vector(M, 0);
  C = sdsl::bit_vector(M, 1);
  rootAddress = (long)(rand() % M);
  quotient[rootAddress] = rootID;
  V[rootAddress] = 1;
}

/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool Bonsai::isPrime(uint64_t input) {
  int i;
  bool prime = true;
  if (input == 2)
    return true;

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
uint64_t Bonsai::nextPrimeNumber(uint64_t inputNumber) {
  uint64_t nextPrimeNumber;
  if (inputNumber <= 0) {
    std::cout << "The number you have entered is zero or negative.\n";
  } else {
    while (inputNumber != 0) {

      nextPrimeNumber = inputNumber + 1;
      // if the number is even, make it odd (2 is special case)
      if (nextPrimeNumber % 2 == 0 && nextPrimeNumber != 2) {
        nextPrimeNumber += 1;
      }
      // while its not a prime number, check the next odd number
      while (!isPrime(nextPrimeNumber)) {
        nextPrimeNumber += 2;
      }
      if (isPrime(nextPrimeNumber))
        return nextPrimeNumber;
    }
  }
  return nextPrimeNumber;
} // end nextPrimeNumber

/* build phase
 * It goes through the dataset transaction by transaction
*/
void Bonsai::build() {
  int count = 0;
  while (Transaction *t = data->getNext()) {
    count++;
    insert(t, count);
    delete t;
  }
} // end build

/*
 * Inserts nodes to appropriate positions
 * handles Virgin and Change bit
 * handles collisions and groups according to const lambda
*/
uint32_t Bonsai::insert(Transaction *t, uint32_t line) {
  uint64_t prevInitAd = rootAddress;
  uint32_t prevJ = rootLambda;
  uint32_t curAddress;
  uint32_t associatedC;
  origHash *key = new origHash();
  for (uint32_t i = 0; i < t->length; i++) {
    key->getKey(prevInitAd, t->t[i], prevJ, M, prime, a);
    if (quotient[key->initAd] == emptySymbol) {
      quotient[key->initAd] = key->quotient;
      V[key->initAd] = 1;
      C[key->initAd] = 1;
      prevInitAd = key->initAd;
      prevJ = 0;
      nodeNumberCount++;
      if (t->t[i] == 5)
        origNodeCount++;
    } else {
      associatedC = getAssociatedC(key->initAd);
      if (V[key->initAd] == 0) { // start of block
        if (associatedC != noValue)
          startNewBlock(key->initAd, associatedC);
        prevJ = 0;
        nodeNumberCount++;
        if (t->t[i] == 5)
          origNodeCount++;
        V[key->initAd] = 1;
        C[curEmptySlot] = 1;
        quotient[curEmptySlot] = key->quotient;
        prevInitAd = key->initAd;
      } else { // block already exists
        prevJ = findSpace(associatedC, key->quotient);

        if (prevJ < lambda) { // if item doesn't exist
          if (t->t[i] == 5)
            origNodeCount++;
          nodeNumberCount++;
          quotient[curEmptySlot] = key->quotient;
          C[curEmptySlot] = 0;
        } else { // prepare for next insertion
          prevJ -= lambda;
        }
        prevInitAd = key->initAd;
      }
      prevInitAd = key->initAd;
      curEmptySlot = noValue;
    }
  }
  delete key;
  return curEmptySlot;
}
/*
 * returns 32 + curJ if item exists
 * returns curJ if item does not exist
*/

uint32_t Bonsai::findSpace(uint32_t cVal, uint32_t quo) {
  // we have curEmptySlot & assoC
  uint32_t curJ = 0;
  uint32_t curC;
  // check if the value is already inserted
  uint32_t tmpSlot;
  // j is 0
  if (itemExists(cVal, quo)) {
    curEmptySlot = cVal;
    return lambda; // 0+lambda
  } else if (quotient[cVal] == emptySymbol) {
    curEmptySlot = cVal;
    return 0;
  }
  // start going upwards until block ends where c!=0
  // increment curJ to return for the next item
  if (cVal == M - 1)
    curC = 0;
  else
    curC = cVal + 1; // curC=cVal++
  curJ++;
  // go upwards towards the end of the block
  while (C[curC] == 0) {
    if (itemExists(curC, quo)) {
      curEmptySlot = curC;
      return lambda + curJ;
    }
    if (curC == M - 1)
      curC = 0;
    else
      curC++;
    curJ++;
  }

  if (curC == 0)
    curC = M - 1;
  else
    curC--; // go one back to stay in the block

  // push all the slots upto curC to insert it in curC
  while (curEmptySlot != curC) {
    if (curEmptySlot == M - 1)
      tmpSlot = 0;
    else
      tmpSlot = curEmptySlot + 1;

    quotient[curEmptySlot] = quotient[tmpSlot];
    C[curEmptySlot] = C[tmpSlot];

    if (curEmptySlot == M - 1)
      curEmptySlot = 0;
    else
      curEmptySlot++;
  }
  curEmptySlot = curC;
  return curJ;
} // end findSpace

/*
 * starts a new block/group of collisions
*/
void Bonsai::startNewBlock(uint32_t vVal, uint32_t cVal) {
  uint32_t tmpSlot;
  uint32_t curC;
  // increase c loc
  if (cVal == M - 1)
    curC = 0;
  else
    curC = cVal + 1;
  // reach the end of the current block
  while (C[curC] == 0) {
    if (curC == M - 1)
      curC = 0;
    else
      curC++;
  }
  // push items to make space
  while (curEmptySlot != curC) {
    if (curEmptySlot == M - 1)
      tmpSlot = 0;
    else
      tmpSlot = curEmptySlot + 1;

    quotient[curEmptySlot] = quotient[tmpSlot];
    C[curEmptySlot] = C[tmpSlot];
    curEmptySlot = tmpSlot;
  }
  if (curEmptySlot == 0)
    curEmptySlot = M - 1;
  else
    curEmptySlot--;
}
/*
 * returns the locations of the associated change bit
 * or noValue if not found.
*/
uint32_t Bonsai::getAssociatedC(uint32_t curAddress) {
  // count ones in V and C
  uint32_t vOnesDown = 0;
  uint32_t cOnesUp = 0;
  uint32_t posMoves = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  // start moving downwards
  if (curAddress == 0)
    curAddress = M - 1;
  else
    curAddress--;
  posMoves++;
  // go downwards untill empty slot and count Vones
  while (quotient[curAddress] != emptySymbol) {
    if (V[curAddress] == 1)
      vOnesDown++;
    if (curAddress == 0)
      curAddress = M - 1;
    else
      curAddress--;
    posMoves++;
  }
  // get emptyslot and start moving upwards
  curEmptySlot = curAddress;
  if (vOnesDown == 0)
    return noValue;

  if (curAddress == M - 1)
    curAddress = 0;
  else
    curAddress++;

  // go upwards
  // count cOnes AFTER emptySlot until conesUp==vOnes down

  while (cOnesUp < vOnesDown) {
    if (C[curAddress] == 1)
      cOnesUp++;
    if (curAddress == M - 1)
      curAddress = 0;
    else
      curAddress++;
  }
  // return associated C value, sta
  if (curAddress == 0)
    return (M - 1);
  else
    return --curAddress;
}

/*
 * return if th item exists
*/
bool Bonsai::itemExists(uint32_t cVal, uint32_t quo) {
  if (quotient[cVal] == quo)
    return true;
  else
    return false;
}

uint32_t Bonsai::findItem(uint32_t vVal, uint32_t cVal, uint32_t quo) {
  uint32_t JVal = 0;
  uint32_t curC;
  // check if the value is already inserted
  bool itExists = itemExists(cVal, quo);
  if (itExists)
    return 0;

  if (cVal == M - 1)
    curC = 0;
  else
    curC = cVal + 1;
  // go upwards towards the end of the block
  while (C[curC] == 0) {
    itExists = itemExists(curC, quo);
    if (itExists) {
      return ++JVal;
    }
    if (curC == M - 1)
      curC = 0;
    else
      curC++;
    JVal++;
  }
  return noValue;
} // end findItem

/* Search phase
 * Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.
*/
void Bonsai::searchBench(char *file) {
  std::ifstream infile;
  infile.open(file);
  std::vector<uint32_t> str;
  std::string rawData;
  while (getline(infile, rawData)) {
    str = getVector(rawData);
    search(str);
    str.clear();
  }
}

/*
 * reads transaction by transaction
 * to be searched
*/
std::vector<uint32_t> Bonsai::getVector(std::string s) {
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
} // getVector

/*
 * searches Items if not found prints error
*/
uint32_t Bonsai::search(std::vector<uint32_t> t) {
  // initialize variables
  uint64_t prevInitAd = rootAddress;
  uint32_t prevJ = rootLambda;
  uint32_t associatedC;
  origHash *key = new origHash();
  for (uint32_t i = 0; i < t.size(); i++) {
    key->getKey(prevInitAd, (uint64_t)t[i], prevJ, M, prime, a);
    if (V[key->initAd] == 0) {
      std::cout << "We searched every corner of bonsai universe. Item is not "
                   "found! :("
                << std::endl;
      return noValue;
    } else {
      associatedC = getAssociatedC(key->initAd);
      prevJ = findItem(key->initAd, associatedC, key->quotient);
    }
    if (prevJ == noValue)
      return noValue;
    else
      prevInitAd = key->initAd;
  }
  return associatedC;
}
