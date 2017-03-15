#include "cht.h"

cht::cht(uint64_t universe, uint64_t Mnew, uint32_t sat, uint32_t difference,
         double up = 0.80, double down = 0.60)
    : dif(difference), M(Mnew), nodeNumberCount(0), satWidth(sat), up_limit(up),
      down_limit(down), expand_shrink_by((2.0 * up * down) / (up + down)) {
  if (M < 10)
    M = 10;
  uint64_t cmax = universe - 1;
  valNotFound = M + 10;
  valExists = valNotFound + 10;
  prime = nextPrimeNumber(cmax);
  euclAlgorithm(prime);
  keyNotFound = prime + 10;
  // mersenne_twister_engine::seed
  emptyLoc = ceil(prime / M) + 1;

  uint32_t w = sdsl::bits::hi(emptyLoc) + 1 + satWidth + 1;
  uint64_t initVal = (emptyLoc << (satWidth + 1)) | 1;
  quotient_items_C = sdsl::int_vector<0>(M, initVal, w);
  V = sdsl::bit_vector(M, 0);
}
cht::~cht() {
  quotient_items_C.resize(0);
  V.resize(0);
}
void cht::resize() {
  quotient_items_C.resize(0);
  V.resize(0);
}

void cht::resize(uint64_t universe, uint64_t Mnew, uint64_t satWidthnew,
                 uint32_t difference, double up = 0.80, double down = 0.60) {
  if (M < 10)
    M = 10;

  up_limit = up;
  down_limit = down;
  expand_shrink_by = (2.0 * up * down) / (up + down);
  dif = difference;
  satWidth = satWidthnew;
  M = Mnew;
  nodeNumberCount = 0;
  expectedNodes = (0.80 * M) + 1;
  valNotFound = M + 10;
  valExists = valNotFound + 10;
  prime = nextPrimeNumber(universe);
  euclAlgorithm(prime);
  keyNotFound = prime + 10;

  emptyLoc = ceil(prime / M) + 1;
  uint32_t w = sdsl::bits::hi(emptyLoc) + 1 + satWidth + 1;
  uint64_t initVal = (emptyLoc << (satWidth + 1)) | 1;
  quotient_items_C = sdsl::int_vector<0>(M, initVal, w);
  V = sdsl::bit_vector(M, 0);
}

uint64_t cht::minorExpand(uint64_t universe, double expandRatio = 0) {
  uint64_t newM;
  if (expandRatio)
    newM = (uint64_t)((M * expandRatio) + 1);
  else
    newM = (uint64_t)((double)(up_limit * M) / expand_shrink_by);
  cht cht_new(universe, newM, satWidth, 0);
  uint64_t key;
  for (uint64_t i = 0; i < M; i++) {
    key = getKey(i);
    if (key != keyNotFound) {
      cht_new.insert(key, getSat(i));
    }
  }
  quotient_items_C.resize(0);
  V.resize(0);
  resize(universe, newM, satWidth, 0);
  for (uint32_t i = 0; i < newM; i++) {
    quotient_items_C[i] = cht_new.quotient_items_C[i];
    V[i] = cht_new.V[i];
  }
  cht_new.quotient_items_C.resize(0);
  cht_new.V.resize(0);
  return newM;
}

uint64_t cht::minorShrink(uint64_t universe, double shrinkRatio = 0) {
  uint64_t newM;
  if (shrinkRatio)
    newM = (uint64_t)((M * shrinkRatio) + 1);
  else
    // newM = (uint64_t)((M * expand_shrink_by)+1);
    newM = (uint64_t)((double)(down_limit * M) / expand_shrink_by);
  cht cht_new(universe, newM, satWidth, 0);
  uint64_t key;
  for (uint64_t i = 0; i < M; i++) {
    key = getKey(i);
    if (key != keyNotFound) {
      cht_new.insert(key, getSat(i));
    }
  }
  quotient_items_C.resize(0);
  V.resize(0);
  resize(universe, newM, satWidth, 0);
  for (uint32_t i = 0; i < newM; i++) {
    quotient_items_C[i] = cht_new.quotient_items_C[i];
    V[i] = cht_new.V[i];
  }
  cht_new.quotient_items_C.resize(0);
  cht_new.V.resize(0);
  return newM;
}

bool cht::remove(uint64_t key) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t initAd = cRand % M;
  uint64_t quot = cRand / M;
  uint64_t c = findByC(key);
  uint64_t tmpSlot = c;

  if (c == valNotFound)
    return false;
  // if the group leader is in the initAd, then there was no collision
  if (c == initAd && getC(c) == 1) {
    V[c] = 0;
    setItem(c, emptyLoc, 0, 1);
    return true;
  }
  if (getC(c) == 1) {
    (tmpSlot == M - 1) ? tmpSlot = 0 : tmpSlot++;
    if (getC(tmpSlot) == 0) {
      quotient_items_C[tmpSlot] = quotient_items_C[tmpSlot] | 1;
    } else {
      V[initAd] = 0;
    }
  }
  tmpSlot = c;
  uint64_t vCnt = 0, cCnt = 0;
  while (getQuo(tmpSlot) != emptyLoc)
    (tmpSlot == 0) ? tmpSlot = M - 1 : tmpSlot--;
  uint64_t checkPoint = tmpSlot, empt = tmpSlot;
  // move one step after empty
  (tmpSlot == M - 1) ? tmpSlot = 0 : tmpSlot++;
  while (tmpSlot != c) {
    if (V[tmpSlot] == 1)
      vCnt++;
    if (getC(tmpSlot) == 1)
      cCnt++;
    (tmpSlot == M - 1) ? tmpSlot = 0 : tmpSlot++;
    if (vCnt == cCnt)
      checkPoint = tmpSlot;
  }
  uint64_t i, j;
  tmpSlot = c;
  j = tmpSlot;
  (tmpSlot == 0) ? i = M - 1 : i = tmpSlot - 1;
  while (j != checkPoint) {
    quotient_items_C[j] = quotient_items_C[i];
    j = i;
    (i == 0) ? i = M - 1 : i--;
  }
  setItem(checkPoint, emptyLoc, 0, 1);
  return true;
}

uint64_t cht::findByC(uint64_t key) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t curAddress = cRand % M;
  uint64_t quot = cRand / M;
  uint64_t cc = 0;
  uint64_t vOnesDown = 0;
  uint64_t cOnesUp = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  else
    return valNotFound;
  // start moving downwards
  (curAddress == 0) ? curAddress = M - 1 : curAddress--;
  // go downwards untill empty slot and count Vones
  while (getQuo(curAddress) != emptyLoc) {
    if (V[curAddress] == 1)
      vOnesDown++;
    (curAddress == 0) ? curAddress = M - 1 : curAddress--;
  }
  // get emptyslot and start moving upwards
  curEmptySlot = curAddress;
  if (vOnesDown == 0)
    return valNotFound;
  (curAddress == M - 1) ? curAddress = 0 : curAddress++;

  // go upwards
  // count cOnes AFTER emptySlot until conesUp==vOnes down
  while (cOnesUp < vOnesDown) {
    if (getC(curAddress) == 1)
      cOnesUp++;
    (curAddress == M - 1) ? curAddress = 0 : curAddress++;
  }
  // return associated C value, sta
  (curAddress == 0) ? curAddress = M - 1 : curAddress--;
  if (item_exists(curAddress, quot)) {
    return curAddress;
  }
  uint64_t cntr = 0;
  (curAddress == M - 1) ? curAddress = 0 : curAddress++;
  while (getC(curAddress) == 0) {
    if (item_exists(curAddress, quot))
      return curAddress;
    (curAddress == M - 1) ? curAddress = 0 : curAddress++;
  }
  return valNotFound;
}
/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool cht::isPrime(uint64_t input) {
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
uint64_t cht::nextPrimeNumber(uint64_t inputNumber) {
  uint64_t nextPrimeNumber;
  if (inputNumber <= 0) {
    std::cout << "The number you have entered is zero or negative.\n";
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

// A naive method to find modulor multiplicative inverse of
// 'a' under modulo 'm'
uint64_t cht::getModInverse(uint64_t a, uint64_t prime) {
  a = a % prime;
  for (uint64_t x = 1; x < prime; x++)
    if ((a * x) % prime == 1)
      return x;
  return prime;
}

void cht::euclAlgorithm(uint64_t prime) {
  long long aTemp = (long long)(0.66 * (double)prime);
  long long aInvTemp = prime;
  while (true) {
    aInvTemp = getModInverse(aTemp, prime);
    if (aInvTemp == prime)
      aTemp++;
    else
      break;
  }
  a = aTemp;
  aInv = aInvTemp;
}

uint64_t cht::getInitAd(uint64_t loc) {
  // check if empty
  if (getQuo(loc) == emptyLoc)
    return valNotFound;
  // count Cones down including first not the last(the empty one)
  uint64_t cOnes = 0, vOnes = 0, index = loc;
  while (getQuo(index) != emptyLoc) {
    if (getC(index) == 1)
      cOnes++;
    (index == 0) ? index = M - 1 : index--;
  }
  while (vOnes != cOnes) {
    if (V[index] == 1)
      vOnes++;
    (index == M - 1) ? index = 0 : index++;
  }
  return (index == 0) ? index = M - 1 : index - 1;
}

uint64_t cht::getKey(uint64_t loc) {
  if (getQuo(loc) == emptyLoc)
    return keyNotFound;
  uint64_t initAd = getInitAd(loc);
  if (initAd == valNotFound)
    return keyNotFound;
  uint64_t cRand = (getQuo(loc) * M) + initAd;
  uint64_t key = (cRand * aInv) % prime;
  return key;
}

/*
 * Searches items by key, called in mBonsai.cpp.
 * Possible return: dif<=x<=(127+dif) //satelite data
 * If search fails return 127+dif+1
*/
uint64_t cht::find(uint64_t key) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t initAd = cRand % M;
  uint64_t quotient = cRand / M;
  if (V[initAd] == 0) {
    return (1 << satWidth) + dif; // not found
  } else {
    uint64_t sog = getStartOfGroup(initAd);
    uint64_t exists = getSatelite(initAd, sog, quotient);
    if (exists != valNotFound) {
      return getSat(curEmptySlot);
    }
    return (1 << satWidth) + dif; // not found
  }
} // end find

/* Returns the location of the displacement value
 * which is stored as satelite data.
 * Called in find only when node exists.
*/
uint64_t cht::getSatelite(uint64_t vVal, uint64_t cVal, uint64_t quotient) {
  uint64_t curC;
  uint64_t tmpSlot;
  // check if the value is already inserted
  if (item_exists(cVal, quotient)) {
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

/*
 * changeBit Loc must be in a specific location relative to the virgin bit.
*/
uint64_t cht::getChangeBitLoc(uint64_t curAddress) {
  uint32_t vOnesDown = 0;
  uint32_t cOnesUp = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  // start moving downwards
  curAddress = (curAddress + M - 1) % M;

  // go downwards untill empty slot and count Vones
  while (!is_empty(curAddress)) {
    if (V[curAddress] == 1)
      vOnesDown++;
    curAddress = (curAddress + M - 1) % M;
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
  return ((curAddress + M - 1) % M);
}
bool cht::insert(uint64_t key, uint32_t value) {
  uint64_t cRand = ((key % prime) * a) % prime;
  uint64_t initAd = cRand % M;
  uint64_t quotient = cRand / M;
  bool nodeIncrease = true;

  if (is_empty(initAd)) {
    nodeNumberCount++;
    setItem(initAd, quotient, (value - dif), 1);
    V[initAd] = 1;
    return nodeIncrease;
  } else {
    uint64_t changeBit = getItemLocation(initAd);
    if (V[initAd] == 0) {
      if (changeBit != valNotFound)
        startNewBlock(initAd, changeBit);
      V[initAd] = 1;
      setItem(curEmptySlot, quotient, (value - dif), 1);
      nodeNumberCount++;
      return nodeIncrease;
    } else {
      nodeIncrease = findSpace(changeBit, quotient);
      if (nodeIncrease)
        nodeNumberCount++;
      setItem(curEmptySlot, quotient, (value - dif), 0);
      return nodeIncrease;
    }
  }
}

uint64_t cht::getItemLocation(uint64_t curAddress) {
  uint64_t vOnesDown = 0;
  uint64_t cOnesUp = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  // start moving downwards
  curAddress = (curAddress + M - 1) % M;
  // go downwards untill empty slot and count Vones
  while (!is_empty(curAddress)) {

    if (V[curAddress] == 1)
      vOnesDown++;
    curAddress = (curAddress + M - 1) % M;
  }
  // get emptyslot and start moving upwards
  curEmptySlot = curAddress;
  if (vOnesDown == 0)
    return valNotFound;
  // (curAddress == M - 1) ? curAddress = 0 : curAddress++;
  curAddress = (curAddress + 1) % M;
  // go upwards
  // count cOnes AFTER emptySlot until conesUp==vOnes down
  while (cOnesUp < vOnesDown) {
    if (getC(curAddress) == 1)
      cOnesUp++;
    curAddress = (curAddress + 1) % M;
  }
  // return associated C value, sta
  return ((curAddress + M - 1) % M);
}

/* We already found our associateC location.
 * We push c values and hashtables accordingly,
 * so we make room to insert the new node in the associateC location
 * return boolean if we found the item in the
*/
bool cht::findSpace(uint64_t cVal, uint64_t quotient) {
  uint64_t curC;
  // check if the value is already inserted
  uint64_t tmpSlot;
  if (item_exists(cVal, quotient)) {
    curEmptySlot = cVal;
    return false;
  }
  if (is_empty(cVal)) {
    curEmptySlot = cVal;
    return true;
  }
  // start going upwards until block ends where c!=0
  curC = (cVal + 1) % M;
  // go upwards towards the end of the block
  while (getC(curC) == 0) {
    if (item_exists(cVal, quotient)) {
      curEmptySlot = curC;
      return false;
    }
    curC = (curC + 1) % M;
  }
  // go one back to stay in the block
  curC = (curC + M - 1) % M;

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
void cht::startNewBlock(uint64_t vVal, uint64_t cVal) {

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
  curEmptySlot = (curEmptySlot + M - 1) % M;
} // end startNewBlock

/*
 * changeBit Loc must be in a specific location relative to the virgin bit.
*/
uint64_t cht::getStartOfGroup(uint64_t curAddress) {
  uint32_t vOnesDown = 0;
  uint32_t cOnesUp = 0;
  // count vOnes downwards including current address
  if (V[curAddress] == 1)
    vOnesDown++;
  // start moving downwards
  curAddress = (curAddress + M - 1) % M;
  // go downwards untill empty slot and count Vones
  while (!is_empty(curAddress)) {
    if (V[curAddress] == 1)
      vOnesDown++;
    curAddress = (curAddress + M - 1) % M;
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
  return (curAddress + M - 1) % M;
}
