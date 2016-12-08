#ifndef DARRAGH_HASH
#define DARRAGH value
#include "orighashFunc.h"

/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
origHash origHash::getKey(uint64_t parentLoc,
                          uint64_t itemID, uint64_t keyJ,
                          uint64_t M, uint64_t prime,
                          uint64_t a) {
  origHash key;
  uint64_t c =
      (itemID * (uint64_t)32 + keyJ) * M + parentLoc;
  uint64_t cRand = ((c % prime) * a);
  cRand = cRand % prime;
  initAd = cRand % M;
  quotient = cRand / M; // it includes the parents J
  return key;
}

#endif
/*
 * reverses the hashfunction to get the itemID
*/
/*uint32_t origHash::recoverID(uint64_t initAd, uint32_t DIVM,
                                 uint64_t M, uint64_t prime,
                                 uint64_t aInv) {
  uint64_t cRandRec = (DIVM * M + initAd);
  uint64_t cRec = (aInv * cRandRec) % prime;
  uint32_t IDRec = cRec / (32 * M);
  return IDRec;
}*/

/*
 * reverses the hashfunction to get the parent location
*/
/*uint64_t origHash::recoverParentLoc(uint64_t initAd,
                                              uint32_t DIVM,
                                              uint64_t M,
                                              uint64_t prime,
                                              uint64_t aInv) {
  uint64_t cRandRec = (DIVM * M + initAd);
  uint64_t cRec = (aInv * cRandRec) % prime;
  uint64_t parentLoc = cRec % M;
  return parentLoc;
}*/

/*
 * reverses the hashfunction to get the lambda value
*/
/*uint64_t origHash::recoverJ(uint64_t initAd,
                                      uint32_t DIVM, uint64_t M,
                                      uint64_t prime,
                                      uint64_t aInv) {
  uint64_t cRandRec = (DIVM * M + initAd);
  uint64_t cRec = (aInv * cRandRec) % prime;
  uint64_t JNumber = (cRec % (32 * M)) / M;
  return JNumber;
}*/
