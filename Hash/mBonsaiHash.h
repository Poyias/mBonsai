#ifndef HASH_RECANDGAMMA
#define HASH_RECANDGAMMA
class hashFunction {
public:
  unsigned long long initAd;
  unsigned long long quotient;

  hashFunction getKey(unsigned long long parentLoc, unsigned long long itemID,
                      unsigned long long M, unsigned long long prime,
                      unsigned long long a);

  inline unsigned long long getInitAd() { return initAd; }
  inline unsigned int getQuotient() { return quotient; }
};
#endif
