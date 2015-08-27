#include "orighashFunc.h"


origHash origHash::getKey(unsigned long long parentLoc, unsigned long long itemID,
unsigned long long keyJ,unsigned long long M,unsigned long long prime, unsigned long long a)
{
	origHash key;
	unsigned long long c= (itemID*(unsigned long long)32+keyJ)*M+parentLoc;
	unsigned long long cRand= ((c %prime)*a)%prime;
	//cRand=cRand%prime;
	initAd= cRand % M;
	quotient= cRand/M; //it includes the parents J
	return key;
}


unsigned int origHash::recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
//according to Bonsai paper
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned int IDRec = cRec/(32*M);
	return IDRec;	
}

unsigned long long origHash::recoverParentLoc(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
//according to Bonsai paper
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long  parentLoc = cRec % M;
	return parentLoc;	
}

unsigned long long origHash::recoverJ(unsigned long long initAd, unsigned int DIVM, 	unsigned long long M,unsigned long long prime, unsigned long long aInv)
{
//according to Bonsai paper
	unsigned long long cRandRec = (DIVM*M+initAd);
	unsigned long long cRec = (aInv*cRandRec)%prime;
	unsigned long long JNumber = (cRec % (32*M))/M;
	return JNumber;	
}
