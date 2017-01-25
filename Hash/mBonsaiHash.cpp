#include "mBonsaiHash.h"


/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
hashFunction hashFunction::getKey(uint64_t parentLoc,
                                  uint64_t itemID,
                                  uint64_t M,
                                  uint64_t prime,
                                  uint64_t a) {
  hashFunction key;
  uint64_t c = (itemID * M) + parentLoc;
  uint64_t cRand = ((c % prime) * a);
  cRand = cRand % prime;
  initAd = cRand % M;
  quotient = cRand / M;
  return key;
}

/*
 * reverses the hashfunction to get the itemID
*/
uint32_t hashFunction::recoverID(uint64_t initAd, uint32_t DIVM, uint64_t M,uint64_t prime, uint64_t aInv)
{
  uint64_t cRandRec = (DIVM*M+initAd);
  uint64_t cRec = (aInv*cRandRec)%prime;
  uint32_t IDRec = cRec/M;
  return IDRec; 
}
/*
 * reverses the hashfunction to get the parent location
*/
uint64_t hashFunction::recoverParentLoc(uint64_t initAd, uint32_t DIVM, uint64_t M,uint64_t prime, uint64_t aInv)
{
  uint64_t cRandRec = (DIVM*M+initAd);
  uint64_t cRec = (aInv*cRandRec)%prime;
  uint64_t  parentLoc = cRec % M;
  return parentLoc; 
}
