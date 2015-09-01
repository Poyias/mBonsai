#include "Bonsai.h"

Bonsai::Bonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file)
{
  	srand(time(NULL));
	this->sigma=++sigma;
	M= ((nodeNumber*1)/(loadFactor));
	setData(file);
	noValue = M+10;
	nodeNumberCount=1;
	origNodeCount=1;
	lambda=32;
	cmax= ( ( (lambda*(sigma-1))+lambda-1 ) *M )+(M-1);
	prime=nextPrimeNumber(cmax);
	a = ULONG_MAX/prime;
	emptySymbol= lambda*sigma+2;
	rootID = (unsigned int) lambda*sigma+1;
	rootLambda=0;
	hashTable= int_vector <SLEN> (M,emptySymbol);
	V = bit_vector(M,0);
	C = bit_vector(M,1);
	rootAddress = (long) (rand() % M);
	hashTable[rootAddress]=rootID;
	V[rootAddress]=1;
}


/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool Bonsai::isPrime(unsigned long long input){
	int i;
	bool prime = true;
	if(input == 2)  return true;

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
unsigned long long Bonsai::nextPrimeNumber(unsigned long long inputNumber){
	unsigned long long nextPrimeNumber;
	if(inputNumber<=0){
		cout<<"The number you have entered is zero or negative.\n";
	}else{
		while(inputNumber != 0){

			nextPrimeNumber = inputNumber + 1;		 
			// if the number is even, make it odd (2 is special case) 
			if(nextPrimeNumber%2 == 0 && nextPrimeNumber != 2){
				nextPrimeNumber+=1;
			}		 
			//while its not a prime number, check the next odd number
			while(!isPrime(nextPrimeNumber)){
				nextPrimeNumber+=2;
			}
			if(isPrime(nextPrimeNumber)) return nextPrimeNumber;
		}
	}
	return nextPrimeNumber;
}//end nextPrimeNumber

/* build phase
 * It goes through the dataset transaction by transaction
*/
void Bonsai::build()
{	
	int count=0;
	while(Transaction *t = data->getNext()) {
		count++;
		insert(t,count);
		delete t;
	}
}// end build

/*
 * Inserts nodes to appropriate positions
 * handles Virgin and Change bit
 * handles collisions and groups according to const lambda
*/
unsigned int Bonsai::insert (Transaction *t,unsigned int line)
{
	unsigned long long prevInitAd=rootAddress;
	unsigned int prevJ= rootLambda;
	unsigned int curAddress;
	unsigned int associatedC;
	origHash *key = new origHash();
	for(unsigned int i=0;i<t->length;i++)
	{
	  key->getKey(prevInitAd, t->t[i], prevJ,M,prime,a);	  
	  if (hashTable[ key->initAd]==emptySymbol)
	    {
	      hashTable[key->initAd]=key->quotient;
	      V[key->initAd]=1;
	      C[key->initAd]=1; 
	      prevInitAd= key->initAd;
	      prevJ=0;
	      nodeNumberCount++;
	      if (t->t[i]==5) origNodeCount++;
	    }
	  else
	    {
	      associatedC=getAssociatedC(key->initAd);
	      if(V[key->initAd]==0){ //start of block
		if (associatedC!=noValue)
		  startNewBlock(key->initAd,associatedC);
		prevJ=0;
		nodeNumberCount++;
		if (t->t[i]==5) origNodeCount++;
		V[key->initAd]=1;
		C[curEmptySlot]=1;
		hashTable[curEmptySlot]=key->quotient;
		prevInitAd= key->initAd;
	      }else{// block already exists
		prevJ=findSpace(associatedC, key->quotient);
		
		if(prevJ<lambda){//if item doesn't exist
		  if (t->t[i]==5) origNodeCount++;
		  nodeNumberCount++;
		  hashTable[curEmptySlot]=key->quotient;
		  C[curEmptySlot]=0;	  
		}else{//prepare for next insertion
		  prevJ-=lambda;
		}
		prevInitAd= key->initAd;
	      }
	      prevInitAd= key->initAd;
	      curEmptySlot=noValue;	
	    }
	}
	delete key;
	return curEmptySlot;
}
/*
 * returns 32 + curJ if item exists
 * returns curJ if item does not exist
*/

unsigned int Bonsai::findSpace(unsigned int cVal, unsigned int quotient)
{
	//we have curEmptySlot & assoC
	unsigned int curJ=0;
	unsigned int curC;
	//check if the value is already inserted
	unsigned int tmpSlot;
	//j is 0
	if (itemExists(cVal, quotient)){
		curEmptySlot=cVal;
		return lambda; // 0+lambda
	}else if(hashTable[cVal]==emptySymbol){
		curEmptySlot=cVal;
		return 0;	
	}
	// start going upwards until block ends where c!=0
	// increment curJ to return for the next item
	if (cVal==M-1) curC=0;
	else curC=cVal+1;	// curC=cVal++
	curJ++;
	//go upwards towards the end of the block
	while (C[curC] == 0)
	{	
		if (itemExists(curC, quotient)){
			curEmptySlot=curC;
			return lambda+curJ;
		}
		if (curC==M-1) curC=0;
		else curC++;
		curJ++;	
	}
	
	if (curC==0) curC=M-1;
	else curC--;		//go one back to stay in the block

	// push all the slots upto curC to insert it in curC
	while(curEmptySlot!=curC){
		if (curEmptySlot==M-1) tmpSlot=0;
		else tmpSlot=curEmptySlot+1;	
		
		hashTable[curEmptySlot] = hashTable[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];

		if (curEmptySlot==M-1) curEmptySlot=0;
		else curEmptySlot++;	
	}
	curEmptySlot=curC;
	return curJ;
} // end findSpace

/* 
 * starts a new block/group of collisions
*/
void Bonsai::startNewBlock(unsigned int vVal,unsigned int cVal)
{
	unsigned int tmpSlot;
	unsigned int curC;
	//increase c loc
	if (cVal==M-1) curC=0;
	else curC=cVal+1;
	// reach the end of the current block
	while (C[curC] == 0)
	{	
		if (curC==M-1) curC=0;
		else curC++;
	}
	// push items to make space
	while(curEmptySlot!=curC){
		if (curEmptySlot==M-1) tmpSlot=0;
		else tmpSlot=curEmptySlot+1;

		hashTable[curEmptySlot] = hashTable[tmpSlot];
		C[curEmptySlot] = C[tmpSlot];
		curEmptySlot=tmpSlot;	
	}
		if ( curEmptySlot==0 ) curEmptySlot=M-1;
		else curEmptySlot--;
}
/*
 * returns the locations of the associated change bit
 * or noValue if not found.
*/
unsigned int Bonsai::getAssociatedC(unsigned int curAddress)
{
	//count ones in V and C
	unsigned int vOnesDown=0;
	unsigned int cOnesUp=0;
	unsigned posMoves=0;
	// count vOnes downwards including current address
	if (V[curAddress]==1) vOnesDown++;
	//start moving downwards
	if (curAddress==0) curAddress=M-1;
	else curAddress--;  
	posMoves++;
	// go downwards untill empty slot and count Vones
	while(hashTable[curAddress] != emptySymbol)
	{
		if ( V[curAddress]==1 ) vOnesDown++;		
		if ( curAddress==0 ) curAddress=M-1;
		else curAddress--;
	posMoves++;
	}
	// get emptyslot and start moving upwards
	curEmptySlot=curAddress;
	if (vOnesDown==0) return noValue;

	if (curAddress==M-1) curAddress=0;
	else curAddress++; 

	// go upwards 
	// count cOnes AFTER emptySlot until conesUp==vOnes down

	while(cOnesUp<vOnesDown)
	{
		if(C[curAddress]==1) cOnesUp++;	
		if (curAddress==M-1) curAddress=0;
		else curAddress++;
	}
	//return associated C value, sta
	if (curAddress==0) return (M-1);
	else return --curAddress;
}

/*
 * return if th item exists
*/
bool Bonsai::itemExists(unsigned int cVal, unsigned int quotient)
{
	if (hashTable[cVal]==quotient)
		return true;
	else
		return false;
}

unsigned int Bonsai::findItem(unsigned int vVal,unsigned int cVal, unsigned int quotient){
	unsigned int JVal=0;
	unsigned int curC;
	//check if the value is already inserted
	bool itExists= itemExists(cVal, quotient);
	if (itExists) return 0;

	if (cVal==M-1) curC=0;
	else curC=cVal+1;
	//go upwards towards the end of the block 
	while (C[curC] == 0){
		itExists= itemExists(curC, quotient);
		if (itExists){
			return ++JVal;
		}
		if (curC==M-1) curC=0;
		else curC++;
		JVal++;	
	}
	return noValue;
}// end findItem

/* Search phase
 * Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.
*/
void Bonsai::searchBench(char* file)
{
	ifstream infile;
	infile.open(file);
	vector <unsigned int> str;
	string rawData;
	while(getline(infile,rawData))
	{
		str=getVector(rawData);
		//if(search(str)==noValue) cout<<"error"<<endl;;
		search(str);
		str.clear();	
	}
}

/*
 * reads transaction by transaction
 * to be searched
*/
vector<unsigned int> Bonsai::getVector(string s){
  char* cstr, *p;
  vector<unsigned int> items;
  cstr= new char[s.size()+1];
  strcpy(cstr, s.c_str());
  p=strtok(cstr," ");
  while(p!=NULL){
    items.push_back(atoi(p));
    p=strtok(NULL," ");
  }
  delete[] cstr;
  return items;
} // getVector

/*
 * searches Items if not found prints error
*/ 
unsigned int Bonsai::search (vector <unsigned int> t){
	//initialize variables
	unsigned long long prevInitAd=rootAddress;
	unsigned int prevJ= rootLambda;
	unsigned int associatedC;
	origHash *key = new origHash();
	for(unsigned int i=0;i<t.size();i++){
		key->getKey(prevInitAd, (unsigned long long)t[i], prevJ,M,prime,a);
		if (V[key->initAd]==0){
			cout<<"We searched every corner of bonsai universe. Item is not found! :("<<endl;
			return noValue;
		}else{
			associatedC=getAssociatedC(key->initAd);
			prevJ=findItem(key->initAd,associatedC, key->quotient);
		}
		if (prevJ==noValue) return noValue;
		else prevInitAd= key->initAd;
	}
		return associatedC;
}

