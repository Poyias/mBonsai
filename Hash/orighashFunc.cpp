#include "orighashFunc.h"

/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
origHash origHash::getKey(unsigned long long parentLoc, unsigned long long itemID,
unsigned long long keyJ,unsigned long long M,unsigned long long prime, unsigned long long a)
{
	origHash key;
	unsigned long long c= (itemID*(unsigned long long)32+keyJ)*M+parentLoc;
	unsigned long long cRand= ((c %prime)*a);
	cRand = cRand % prime;
	initAd= cRand % M;
	quotient= cRand/M; //it includes the parents J
	return key;
}

/*
 *** The functions below work only if a is carefully selected such that its mod inverse (aInv)
 *** will be able to reverse the hashfunction
*/

/*
 * reverses the hashfunction to get the itemID
*/
unsigned int origHash::recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned int IDRec = cRec/(32*M);
	return IDRec;	
}

/*
 * reverses the hashfunction to get the parent location
*/
unsigned long long origHash::recoverParentLoc(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long  parentLoc = cRec % M;
	return parentLoc;	
}

/*
 * reverses the hashfunction to get the lambda value
*/
unsigned long long origHash::recoverJ(unsigned long long initAd, unsigned int DIVM, 	unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long JNumber = (cRec % (32*M))/M;
	return JNumber;	
}
