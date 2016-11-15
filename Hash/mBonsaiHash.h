#ifndef REC_HASH
#define REC_HASH

class hashFunction
{
 public:

unsigned long long initAd;
unsigned long long quotient;

hashFunction getKey(unsigned long long parentLoc, unsigned long long itemID, unsigned long long M,unsigned long long prime, unsigned long long a);

unsigned long long getInitAd(){return initAd;}
unsigned int getQuotient(){return quotient;}
/*
 *** The functions below work only if a is carefully selected such that its mod inverse (aInv)
 *** will be able to reverse the hashfunction
*/
unsigned int recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv);
unsigned long long recoverParentLoc(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv);
};
#endif
