#include "mBonsaiHash.h"
#include <stdio.h>
#define mulmod(a, b, m) (uint64_t)(((sdsl::uint128_t)(a) * (sdsl::uint128_t)(b)) % ((sdsl::uint128_t)(m)))
/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
void hashFunction::getKey(uint64_t parentLoc,
    uint64_t itemID,
    uint64_t M,
    uint64_t prime,
    uint64_t a)
{
    uint64_t c = (itemID * M) + parentLoc;
    uint64_t cRand = mulmod(a, c, prime); //(c * a) % prime;
    initAd = cRand % M;
    quotient = cRand / M;
}

/*
 * reverses the hashfunction to get the itemID
*/
uint64_t hashFunction::recoverID(uint64_t initAd, uint64_t DIVM, uint64_t M, uint64_t prime, uint64_t aInv)
{
    sdsl::uint128_t cRandRec = ((sdsl::uint128_t)DIVM * (sdsl::uint128_t)M + (sdsl::uint128_t)initAd);
    uint64_t cRec = mulmod(aInv, cRandRec, prime); //(aInv*cRandRec)%prime;
    uint64_t IDRec = cRec / M;
    return IDRec;
}
/*
 * reverses the hashfunction to get the parent location
*/
uint64_t hashFunction::recoverParentLoc(uint64_t initAd, uint64_t DIVM, uint64_t M, uint64_t prime, uint64_t aInv)
{
    sdsl::uint128_t cRandRec = ((sdsl::uint128_t)DIVM * (sdsl::uint128_t)M + (sdsl::uint128_t)initAd);
    uint64_t cRec = mulmod(aInv, cRandRec, prime); //aInv % prime;
    //cRec = (cRec * cRandRec) % prime;  (a*b)%c  == (a%c)*(b%c)
    uint64_t parentLoc = cRec % M;
    return parentLoc;
}

/*
// A naive method to find modulor multiplicative inverse of
// 'a' under modulo 'm'
long long mBonsai::getModInverse(long long a, uint64_t prime) {
  a = a % prime;
  for (uint64_t x = 1; x < prime; x++)
    if (((a * x) % prime == 1) && x!=0)
      return x;
  return 0;
}

void mBonsai::euclAlgorithm(uint64_t prime) {
  uint64_t aTemp = (uint64_t)(0.72 * (double)prime);
  uint64_t aInvTemp = 0;
  while (true) {
    aInvTemp = getModInverse(aTemp, prime);
    if (aInvTemp == 0)
      aTemp++;
    else
      break;
  }
  a = aTemp;
  aInv = aInvTemp;
  cout<<"a: "<<a<<" aInv: "<< aInv<<endl;
}*/