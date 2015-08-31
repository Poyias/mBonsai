#include "mBonsaiHash.h"
/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
hashFunction hashFunction::getKey(unsigned long long parentLoc, unsigned long long itemID, unsigned long long M,unsigned long long prime, unsigned long long a)
{
	hashFunction key;
	unsigned long long c= (itemID * M)+parentLoc;
	unsigned long long cRand= ((c %prime)*a)%prime;
	initAd= cRand % M;
	quotient= cRand/M;
	return key;
}
/*
 *** The functions below work only if a is carefully selected such that its mod inverse (aInv)
 *** will be able to reverse the hashfunction
*/

/*
 * reverses the hashfunction to get the itemID
*/
unsigned int hashFunction::recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned int IDRec = cRec/M;
	return IDRec;	
}
/*
 * reverses the hashfunction to get the parent location
*/
unsigned long long hashFunction::recoverParentLoc(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long  parentLoc = cRec % M;
	return parentLoc;	
}
