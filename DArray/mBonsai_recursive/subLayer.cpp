#include "subLayer.h"
#include "limits.h"

SubLayer::SubLayer(double perOfM,unsigned long long universe,unsigned int difference):
	dif(difference),
	M(1.25* (((double)universe*perOfM)+1.0)),
	nodeNumberCount(0),
	cmax(universe-1),
	satWidth(7)
{
	srand(time(NULL));
	valNotFound = M+10;
	prime=nextPrimeNumber(cmax);
	a = ULONG_MAX/prime;
	emptyLoc= ceil(cmax/M)+1;
	quotient_items = int_vector<0>(0);
	quotient_items.width((unsigned int)log2(emptyLoc)+1 +(satWidth));
	cout<<"universe: "<<cmax<<", M: "<<M<<", U/M(max q): "<< (cmax/M)<<", emptySymbol: "<<emptyLoc<<endl;
	quotient_items.resize(M);
	for(unsigned long long i=0; i<M; i++) quotient_items[i] = (emptyLoc<<satWidth);

	V = bit_vector(M,0);
	C = bit_vector(M,1);
}


/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool SubLayer::isPrime(unsigned long long input){
	unsigned long long i;
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
	unsigned long long initAd= cRand % M;
	unsigned long long quotient= cRand/M;

	if (V[initAd]==0)
	{
		return (1<<satWidth)+dif; //127+dif+1;
	}
	else
	{
		unsigned long long exists=getSatelite(initAd,(getChangeBitLoc(initAd)), quotient); 
		if(exists!=valNotFound){
			return (unsigned long long)(quotient_items[curEmptySlot]&((1<<satWidth)-1));
		}
		return  (1<<satWidth)+dif;
	}	
}//end find

/* Returns the location of the displacement value 
 * which is stored as satelite data.
 * Called in find only when node exists.
*/
unsigned long long SubLayer::getSatelite(unsigned long long vVal,unsigned long long cVal,
			unsigned long long quotient)
{
	unsigned long long curC;
	unsigned long long tmpSlot;
	//check if the value is already inserted
	if ((itemExists(cVal, quotient))){
		curEmptySlot=cVal;
		return cVal; 
	}else if((quotient_items[cVal]>>satWidth)==emptyLoc){
		curEmptySlot=cVal;
		return valNotFound;	
	}
	// start going upwards until block ends where c!=0
	curC = (cVal+1)%M;
	//go upwards towards the end of the block	
	while /*(getC(curC) == 0)   //*/(C[curC] == 0)
	{	
		if (itemExists(curC, quotient)){
			curEmptySlot=curC;
			return curC;
		}
		curC = (curC+1)%M;
	}
	return valNotFound;
}//end getSatelite

/* inserts new displacement value at the correct location
 * as satelite data
*/
void SubLayer::insert (unsigned long long key, unsigned int value)
{
	unsigned long long cRand= ((key %prime)*a)%prime;
	unsigned long long initAd= cRand % M;
	unsigned long long quotient= cRand/M;
	nodeNumberCount++;

	if ((quotient_items[initAd]>>satWidth)==emptyLoc)
	{
		quotient_items[initAd]= (quotient<<satWidth)|(value-dif);
		V[initAd]=1;
		C[initAd]=1;
	}
	else
	{
		unsigned long long changeBit=getChangeBitLoc(initAd);
		if(V[initAd]==0){
			if (changeBit!=valNotFound)
				startNewBlock(initAd,changeBit);
			V[initAd]=1;
			C[curEmptySlot]=1;
			quotient_items[curEmptySlot]=(quotient<<satWidth)|(value-dif);
		}else{
			findSpace(changeBit, quotient); 
			quotient_items[curEmptySlot]=(quotient<<satWidth)|(value-dif);
			C[curEmptySlot]=0;
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
	unsigned long long curC;
	//check if the value is already inserted
	unsigned long long tmpSlot;

	if ( (itemExists(cVal, quotient)) || ((quotient_items[cVal]>>satWidth)==emptyLoc)){
		curEmptySlot=cVal;
		return; 
	}
	// start going upwards until block ends where c!=0
	curC = (cVal+1)%M;
	//go upwards towards the end of the block	
	while (C[curC] == 0)
	{	
		if (itemExists(cVal, quotient)){
			curEmptySlot=curC;
			return;
		}
		curC = (curC+1)%M;

	}
	//go one back to stay in the block
	// curC = (curC-1)%M;
	if(curC==0) curC=M-1;
	else curC--;
	// push all the slots upto curC to insert it in curC
	while(curEmptySlot!=curC){
		tmpSlot = (curEmptySlot+1) % M;
		quotient_items[curEmptySlot] = quotient_items[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];
		curEmptySlot = (curEmptySlot+1)%M;	
	}
	curEmptySlot=curC;
} // end findSpace

/* In case we eant to start a new Block
 * and the changeBit lies in another block.
 * We handle this situation differently.
*/
void SubLayer::startNewBlock(unsigned long long vVal,unsigned long long cVal){

	unsigned int tmpSlot;
	unsigned long long curC;
	curC = (cVal+1)%M;
	
	while (C[curC] == 0) curC = (curC+1)%M;
	
	while (curEmptySlot!=curC){
		tmpSlot = (curEmptySlot+1) % M;
		quotient_items[curEmptySlot] = quotient_items[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];
		curEmptySlot=tmpSlot;	
	}
		if ( curEmptySlot==0 ) curEmptySlot=M-1;
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
	if (curAddress==0) curAddress=M-1;
	else curAddress--;
	// go downwards untill empty slot and count Vones
	while((quotient_items[curAddress]>>satWidth) != emptyLoc)
	{
		if ( V[curAddress]==1 ) vOnesDown++;		
		if ( curAddress==0 ) curAddress=M-1;
		else curAddress--;
	}
	// get emptyslot and start moving upwards
	curEmptySlot=curAddress;
	if (vOnesDown==0) return valNotFound;
	curAddress = (curAddress+1)%M;

	// go upwards 
	// count cOnes AFTER emptySlot until conesUp==vOnes down
	while(cOnesUp<vOnesDown)
	{
		if (C[curAddress]==1) cOnesUp++;	
		curAddress = (curAddress+1)%M;
	}
	//return associated C value, sta
	if (curAddress==0) return (M-1);
	else return --curAddress;
}


bool SubLayer::itemExists(unsigned long long cVal, unsigned long long quotient)
{
	if ((quotient_items[cVal]>>satWidth)==quotient)
		return true;
	return false;
}

