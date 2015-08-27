#include "mBonsaiHash.h"

hashFunction hashFunction::getKey(unsigned long long parentLoc, unsigned long long itemID, unsigned long long M,unsigned long long prime, unsigned long long a)
{
	hashFunction key;
	unsigned long long c= (itemID * M)+parentLoc;
	unsigned long long cRand= ((c %prime)*a)%prime;
	initAd= cRand % M;
	quotient= cRand/M;
	return key;
}


unsigned int hashFunction::recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
//according to Bonsai paper
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned int IDRec = cRec/M;
	return IDRec;	
}

unsigned long long hashFunction::recoverParentLoc(unsigned long long initAd, unsigned int DIVM, 	unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
//according to Bonsai paper
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long  parentLoc = cRec % M;
	return parentLoc;	
}
