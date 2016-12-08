#include "mBonsaiHash.h"
/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
hashFunction hashFunction::getKey(unsigned long long parentLoc,
                                  unsigned long long itemID,
                                  unsigned long long M,
                                  unsigned long long prime,
                                  unsigned long long a) {
  hashFunction key;
  unsigned long long c = (itemID * M) + parentLoc;
  unsigned long long cRand = ((c % prime) * a);
  cRand = cRand % prime;
  initAd = cRand % M;
  quotient = cRand / M;
  return key;
}