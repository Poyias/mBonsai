#include "mBonsaiGm.h"
#include "../Hash/mBonsaiHash.h"


mBonsaiGm::mBonsaiGm(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file, unsigned int blockSize, unsigned int numBlocks){

	srand(time(NULL));
	this->sigma=sigma;
	M= ((nodeNumber*1)/(loadFactor));

	setData(file); // 3 is for flat numbered datasets

	nodeNotFound = M+10;
	nodeNumberCount=1;

	unsigned long long cmax=sigma*M+(M-1);
	prime=nextPrimeNumber(cmax);

	//calcAandInv(prime+1);
	a = ULONG_MAX/prime;
	emptyLoc= sigma+2;
	rootID = rand() % (sigma-1);

	hashTable= int_vector <SLEN> (M,emptyLoc);
	D=new blockedDArray(blockSize,numBlocks);

	randRootAdrs= (long) (rand() % M); //17;//
	hashTable[randRootAdrs]=rootID;
}

/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool mBonsaiGm::isPrime(unsigned long long input){
	int i;
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
unsigned long long mBonsaiGm::nextPrimeNumber(unsigned long long inputNumber){
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



/* uses Data to read next Transaction
 * creates transaction object passes it to insertTrans(t)
*/
void mBonsaiGm::build()
{
	while(Transaction *t = data->getNext()) {
		insertTrans(t);
		delete t;
	}
}// end build

/* During the build phase
 * called in build 
 * param: trans[] of items where trans[0] is parent of trans[1] and so on. 
 * it calculates the quotient value and mod hash location
 * it calles the setAddress with the required data to handle collision and correct node match
 */
void mBonsaiGm::insertTrans(Transaction *t)
{
	hashFunction *key = new hashFunction();
	unsigned long long prevInitAd=randRootAdrs;
	for(int i=0; i<t->length;i++)
	{
		key->getKey(prevInitAd, t->t[i],M,prime,a);
		prevInitAd=setAddress(key->initAd, key->quotient);
	}// end first for
	delete key;
}// end of manageDeltaTrie


/* During the build phase
 * called in insertTrans
 * it sets the quotient value in the correct mod hash location
 * it inserts the respective value in DArray
 * returns the hash loc so the next item (its child) can use it
 */
unsigned long long mBonsaiGm::setAddress(unsigned long long initAd, unsigned int DIVM)
{
	unsigned int DCount=0;
	while(true){
		//insert value in empty loc
		if(hashTable[initAd]==emptyLoc){
			hashTable[initAd]=DIVM;
			nodeNumberCount++;
			if(DCount!=0) D->setT(initAd,DCount);
			return initAd;
		}
		else if ( (hashTable[initAd]==DIVM)  && (initAd!=randRootAdrs) )
		{
			// item found don't set DArray
			if (DCount==D->get(initAd))
			{
				return initAd;
			}else{
				DCount++;
				initAd++;
				if (initAd>=M)	initAd=0;
			}		
		}
		else
		{
			DCount++;
			initAd++;
			if (initAd>=M)	initAd=0;
		}
	}
	
}//end setAddress

/* Search phase
 * Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.
*/
void mBonsaiGm::searchBench(char* file)
{ 
	ifstream infile;
	infile.open(file);
	vector <unsigned int> str;
	string rawData;

	while(getline(infile,rawData))
	{  
		str=getVector(rawData);
		hashFunction *key = new hashFunction();
		unsigned long long prevInitAd=randRootAdrs;
		for(int i=0; i<str.size();++i)
		{		
			key->getKey(prevInitAd, (unsigned long long)str[i],M,prime,a);
			prevInitAd=searchItem(key->initAd, key->quotient);
		}
		delete key;
		str.clear();	
	}	
}//end searchBench

/*
 * reads transaction by transaction
 * to be searched
*/
vector<unsigned int> mBonsaiGm::getVector(string s)
{
	char* cstr, *p;
	vector<unsigned int> items;
	cstr= new char[s.size()+1];
	strcpy(cstr, s.c_str());
	p=strtok(cstr," ");
	while( p != NULL ){
		items.push_back(atoi(p));
		p=strtok( NULL," ") ;
	}
	delete[] cstr;
	return items;
}// end getVector

/*
 * searches Items if not found prints error
*/ 
unsigned long long mBonsaiGm::searchItem(unsigned long long initAd, unsigned int DIVM)
{
	unsigned int DCount=0;
	  while(true){
		//insert value in empty loc
		if(hashTable[initAd]==emptyLoc)
		{
			cout<<"We searched every corner of mB universe. Item is not found! :("<<endl;
       			return nodeNotFound;
		}
		else if ( (hashTable[initAd]==DIVM) && (initAd!=randRootAdrs)  )
		{
			// item found don't set DArray
			if (DCount==D->get(initAd))
			{
				return initAd;
			}else{
				DCount++;
				initAd++;
				if (initAd>=M)	initAd=0;
			}		
		}
		else
		{
			DCount++;
			initAd++;
			if (initAd>=M)	initAd=0;
		}
	  }
}//end setAddress
