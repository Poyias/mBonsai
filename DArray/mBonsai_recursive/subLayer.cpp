#include "subLayer.h"
#include "limits.h"

SubLayer::SubLayer(double perOfM,unsigned long long M,unsigned int difference)
{
	srand(time(NULL));
	dif=difference;
	Msl =1.25* (((double)M*perOfM)+1.0);
	nodeNumberCount=0;
	valNotFound = Msl+10;
	cmax= M-1;
	prime=nextPrimeNumber(cmax);
	a = ULONG_MAX/prime;
	emptyLoc= (cmax/Msl)+2;
	hashTable= int_vector <SLEN2> (Msl,emptyLoc);
	satData = int_vector <SAT>(Msl,0);
	V = bit_vector(Msl,0);
	C = bit_vector(Msl,1);
}


/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool SubLayer::isPrime(unsigned long long input){
	unsigned int i;
	bool prime = true;

	if(input == 2){
		return true;
	}

	if(input%2 == 0 || input <= 1){
		prime = false;
	} else {
		for(i=3; i<=sqrt(input); i+=2){
			if(input%i == 0){
				prime = false;
			}
		}
	}
	return prime;
}//end isPrime

/*
 * Function for determining the next prime number 
 */
unsigned long long SubLayer::nextPrimeNumber(unsigned long long inputNumber){
	unsigned long long nextPrimeNumber;
	if(inputNumber<=0){
		//cout<<"The number you have entered is zero or negative.\n";
	}else{
		while(inputNumber != 0){

			nextPrimeNumber = inputNumber + 1;		 
			if(nextPrimeNumber%2 == 0 && nextPrimeNumber != 2){
				nextPrimeNumber+=1;
			}		 
			while(!isPrime(nextPrimeNumber)){
				nextPrimeNumber+=2;
			}
			if(isPrime(nextPrimeNumber)) return nextPrimeNumber;
		}
	}
	return nextPrimeNumber;
}//end nextPrimeNumber

/* 
 * Searches items by key, called in mBonsai.cpp.
 * Possible return: dif<=x<=(127+dif) //satelite data
 * If search fails return 127+dif+1
*/
unsigned long long SubLayer::find(unsigned long long key)
{
	unsigned long long cRand= ((key %prime)*a)%prime;
	unsigned long long initAd= cRand % Msl;
	unsigned long long quotient= cRand/Msl;

	if (V[initAd]==0)
	{
std::cout<<"lolllla"<<std::endl;
		return 127+dif+1;
	}
	else
	{
		unsigned long long exists=getSatelite(initAd,(getChangeBitLoc(initAd)), quotient); 
		if(exists!=valNotFound){
			return satData[curEmptySlot];
		}
std::cout<<"lalllla"<<std::endl;
		return  135;//satData[exists];
	}	
}//end find

/* Returns the location of the displacement value 
 * which is stored as satelite data.
 * Called in find only when node exists.
*/
unsigned int SubLayer::getSatelite(unsigned int vVal,unsigned int cVal,
			unsigned int quotient)
{
	unsigned int curC;
	unsigned int tmpSlot;
	//check if the value is already inserted
	if ((itemExists(cVal, quotient))){
		curEmptySlot=cVal;
		return cVal; 
	}else if(hashTable[cVal]==emptyLoc){
		curEmptySlot=cVal;
		return valNotFound;	
	}
	// start going upwards until block ends where c!=0
	if (cVal==Msl-1) curC=0;
	else curC=cVal+1;

	//go upwards towards the end of the block	
	while (C[curC] == 0)
	{	
		if (itemExists(curC, quotient)){
			curEmptySlot=curC;
			return curC;
		}
		if (curC==Msl-1) curC=0;
		else curC++;
	}
	return valNotFound;
}//end getSatelite

/* inserts new displacement value at the correct location
 * as satelite data
*/
void SubLayer::insert (unsigned long long key, unsigned int value)
{
	unsigned long long cRand= ((key %prime)*a)%prime;
	unsigned long long initAd= cRand % Msl;
	unsigned long long quotient= cRand/Msl;
	nodeNumberCount++;

	if (hashTable[initAd]==emptyLoc)
	{
		hashTable[initAd]=quotient;
		V[initAd]=1;
		C[initAd]=1;
		satData[initAd]=value-dif;
	}
	else
	{
		unsigned long long changeBit=getChangeBitLoc(initAd);
		if(V[initAd]==0){
			if (changeBit!=valNotFound)
				startNewBlock(initAd,changeBit);
			V[initAd]=1;
			C[curEmptySlot]=1;
			hashTable[curEmptySlot]=quotient;
			satData[curEmptySlot]=value-dif;
		}else{
			findSpace(changeBit, quotient); 
			hashTable[curEmptySlot]=quotient;
			C[curEmptySlot]=0;
			satData[curEmptySlot]=value-dif;
		}
	}
}
/* We already found our associateC location.
 * We push c values and hashtables accordingly,
 * so we make room to insert the new node in the associateC location
 * return boolean if we found the item in the 
*/
void SubLayer::findSpace(unsigned long long cVal, unsigned long long quotient)
{
	unsigned int curC;
	//check if the value is already inserted
	unsigned int tmpSlot;

	if ( (itemExists(cVal, quotient)) || (hashTable[cVal]==emptyLoc)){
		curEmptySlot=cVal;
		return; 
	}
	// start going upwards until block ends where c!=0
	if (cVal==Msl-1) curC=0;
	else curC=cVal+1;

	//go upwards towards the end of the block	
	while (C[curC] == 0)
	{	
		if (itemExists(curC, quotient)){
			curEmptySlot=curC;
			return;
		}
		if (curC==Msl-1) curC=0;
		else curC++;
	}
	if (curC==0) curC=Msl-1;
	else curC--;		//go one back to stay in the block

	// push all the slots upto curC to insert it in curC
	while(curEmptySlot!=curC){
		if (curEmptySlot==Msl-1) tmpSlot=0;
		else tmpSlot=curEmptySlot+1;	
		
		hashTable[curEmptySlot] = hashTable[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];
		satData[curEmptySlot] = satData[tmpSlot];
		if (curEmptySlot==Msl-1) curEmptySlot=0;
		else curEmptySlot++;	
	}
	curEmptySlot=curC;
} // end findSpace

/* In case we eant to start a new Block
 * and the changeBit lies in another block.
 * We handle this situation differently.
*/
void SubLayer::startNewBlock(unsigned int vVal,unsigned int cVal){

	unsigned int tmpSlot;
	unsigned int curC;
	if (cVal==Msl-1) curC=0;
	else curC=cVal+1;
	
	while (C[curC] == 0)
	{	
		if (curC==Msl-1) curC=0;
		else curC++;
	}
	while(curEmptySlot!=curC){
		if (curEmptySlot==Msl-1) tmpSlot=0;
		else tmpSlot=curEmptySlot+1;

		hashTable[curEmptySlot] = hashTable[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];
		satData[curEmptySlot] = satData[tmpSlot];
		curEmptySlot=tmpSlot;	
	}
		if ( curEmptySlot==0 ) curEmptySlot=Msl-1;
		else curEmptySlot--;
}// end startNewBlock

/* 
 * changeBit Loc must be in a specific location relative to the virgin bit.
*/
unsigned long long SubLayer::getChangeBitLoc(unsigned long long curAddress)
{
	unsigned int vOnesDown=0;
	unsigned int cOnesUp=0;
	// count vOnes downwards including current address
	if (V[curAddress]==1) vOnesDown++;
	//start moving downwards
	if (curAddress==0) curAddress=Msl-1;
	else curAddress--;  
	// go downwards untill empty slot and count Vones
	while(hashTable[curAddress] != emptyLoc)
	{
		if ( V[curAddress]==1 ) vOnesDown++;		
		if ( curAddress==0 ) curAddress=Msl-1;
		else curAddress--;
	}
	// get emptyslot and start moving upwards
	curEmptySlot=curAddress;
	if (vOnesDown==0) return valNotFound;
	if (curAddress==Msl-1) curAddress=0;
	else curAddress++; 

	// go upwards 
	// count cOnes AFTER emptySlot until conesUp==vOnes down
	while(cOnesUp<vOnesDown)
	{
		if(C[curAddress]==1) cOnesUp++;	
		if (curAddress==Msl-1) curAddress=0;
		else curAddress++;
	}
	//return associated C value, sta
	if (curAddress==0) return (Msl-1);
	else return --curAddress;
}


bool SubLayer::itemExists(unsigned long long cVal, unsigned long long quotient)
{
	if (hashTable[cVal]==quotient)
		return true;
	return false;
}

