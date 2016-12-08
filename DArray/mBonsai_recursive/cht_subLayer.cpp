#include "cht_subLayer.h"
#include "limits.h"
cht_subLayer::cht_subLayer(double perU, uint64_t universe, uint32_t sat,
                           double epsilon, uint32_t difference)
    : dif(difference), M((1.0 + epsilon) * ((double)universe * perU) + 1.0),
      nodeNumberCount(0), cmax(universe - 1), satWidth(sat) {

  valNotFound = M + 10;
  prime = nextPrimeNumber(cmax);
  a = ULONG_MAX / prime; // need to randomize that
  // mersenne_twister_engine::seed
  emptyLoc = ceil(cmax / M) + 1;
  uint64_t w = sdsl::bits::hi(emptyLoc) + 1 + satWidth + 1;
  uint64_t initVal = (emptyLoc << (satWidth + 1)) | 1;
  quotient_items_C = sdsl::int_vector<0>(M, initVal, w);
  V = sdsl::bit_vector(M, 0);
}

/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool cht_subLayer::isPrime(uint64_t input) {
  uint64_t i;
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
uint64_t cht_subLayer::nextPrimeNumber(uint64_t inputNumber) {
  uint64_t nextPrimeNumber;
  if (inputNumber <= 0) {
    // cout<<"The number you have entered is zero or negative.\n";
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
 * Searches items by key, called in mBonsai.cpp.
 * Possible return: dif<=x<=(127+dif) //satelite data
 * If search fails return 127+dif+1
*/
uint64_t cht_subLayer::find(uint64_t key) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t initAd = cRand % M;
  uint64_t quotient = cRand / M;

  if (V[initAd] == 0) {
    return (1 << satWidth) + dif; // 127+dif+1;
  } else {
    uint64_t exists = getSatelite(initAd, (getChangeBitLoc(initAd)), quotient);
    if (exists != valNotFound) {
      return getSat(curEmptySlot);
    }
    return (1 << satWidth) + dif;
  }
} // end find

/* Returns the location of the displacement value
 * which is stored as satelite data.
 * Called in find only when node exists.
*/
uint64_t cht_subLayer::getSatelite(uint64_t vVal, uint64_t cVal,
                                   uint64_t quotient) {
  uint64_t curC;
  uint64_t tmpSlot;
  // check if the value is already inserted
  if ((item_exists(cVal, quotient))) {
    curEmptySlot = cVal;
    return cVal;
  } else if (is_empty(cVal)) {
    curEmptySlot = cVal;
    return valNotFound;
  }
  // start going upwards until block ends where c!=0
  curC = (cVal + 1) % M;
  // go upwards towards the end of the block
  while (getC(curC) == 0) {
    if (item_exists(curC, quotient)) {
      curEmptySlot = curC;
      return curC;
    }
    curC = (curC + 1) % M;
  }
  return valNotFound;
} // end getSatelite

/* inserts new displacement value at the correct location
 * as satelite data
*/
void cht_subLayer::insert(uint64_t key, uint32_t value) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t initAd = cRand % M;
  uint64_t quotient = cRand / M;
  nodeNumberCount++;

  if (is_empty(initAd)) {
    setItem(initAd, quotient, (value - dif), 1);
    V[initAd] = 1;
  } else {
    uint64_t changeBit = getChangeBitLoc(initAd);
    if (V[initAd] == 0) {
      if (changeBit != valNotFound)
        startNewBlock(initAd, changeBit);
      V[initAd] = 1;
      setItem(curEmptySlot, quotient, (value - dif), 1);
    } else {
      findSpace(changeBit, quotient);
      setItem(curEmptySlot, quotient, (value - dif), 0);
    }
  }
}
/* We already found our associateC location.
 * We push c values and hashtables accordingly,
 * so we make room to insert the new node in the associateC location
 * return boolean if we found the item in the
*/
void cht_subLayer::findSpace(uint64_t cVal, uint64_t quotient) {
  uint64_t curC;
  // check if the value is already inserted
  uint64_t tmpSlot;

  if ((item_exists(cVal, quotient)) || is_empty(cVal)) {
    curEmptySlot = cVal;
    return;
  }
  // start going upwards until block ends where c!=0
  curC = (cVal + 1) % M;
  // go upwards towards the end of the block
  while (getC(curC) == 0) {
    if (item_exists(cVal, quotient)) {
      curEmptySlot = curC;
      return;
    }
    curC = (curC + 1) % M;
  }
  // go one back to stay in the block
  // curC = (curC-1)%M;
  if (curC == 0)
    curC = M - 1;
  else
    curC--;
  // push all the slots upto curC to insert it in curC
  while (curEmptySlot != curC) {
    tmpSlot = (curEmptySlot + 1) % M;
    quotient_items_C[curEmptySlot] = quotient_items_C[tmpSlot];
    curEmptySlot = (curEmptySlot + 1) % M;
  }
  curEmptySlot = curC;
} // end findSpace

/* In case we eant to start a new Block
 * and the changeBit lies in another block.
 * We handle this situation differently.
*/
void cht_subLayer::startNewBlock(uint64_t vVal, uint64_t cVal) {

  uint32_t tmpSlot;
  uint64_t curC;
  curC = (cVal + 1) % M;

  while (getC(curC) == 0)
    curC = (curC + 1) % M;

  while (curEmptySlot != curC) {
    tmpSlot = (curEmptySlot + 1) % M;
    quotient_items_C[curEmptySlot] = quotient_items_C[tmpSlot];
    curEmptySlot = tmpSlot;
  }
  if (curEmptySlot == 0)
    curEmptySlot = M - 1;
  else
    curEmptySlot--;
} // end startNewBlock

/*
 * changeBit Loc must be in a specific location relative to the virgin bit.
*/
uint64_t cht_subLayer::getChangeBitLoc(uint64_t curAddress) {
  uint32_t vOnesDown = 0;
  uint32_t cOnesUp = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  // start moving downwards
  if (curAddress == 0)
    curAddress = M - 1;
  else
    curAddress--;
  // go downwards untill empty slot and count Vones
  while (!is_empty(curAddress)) {
    if (V[curAddress] == 1)
      vOnesDown++;
    if (curAddress == 0)
      curAddress = M - 1;
    else
      curAddress--;
  }
  // get emptyslot and start moving upwards
  curEmptySlot = curAddress;
  if (vOnesDown == 0)
    return valNotFound;
  curAddress = (curAddress + 1) % M;

  // go upwards
  // count cOnes AFTER emptySlot until conesUp==vOnes down
  while (cOnesUp < vOnesDown) {
    if (getC(curAddress) == 1)
      cOnesUp++;
    curAddress = (curAddress + 1) % M;
  }
  // return associated C value, sta
  if (curAddress == 0)
    return (M - 1);
  else
    return curAddress - 1;
}
