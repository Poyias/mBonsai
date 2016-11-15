#include "mBonsai.h"
#include "../Hash/mBonsaiHash.h"
/*
 * Constructor initialise trie
*/
mBonsai::mBonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file)
{
	srand(time(NULL));
	this->sigma=sigma;
	M=(unsigned long long) (nodeNumber)/loadFactor;
	setData(file); 
	valNotFound = M+10; //dummy value
	nodeNumberCount=1;
	origNodeCount=1; // in case of split nums
	unsigned long long cmax=sigma*M+(M-1);
	prime=nextPrimeNumber(cmax);
	euclAlgorithm(prime);

	// a = ULONG_MAX/prime;
	emptyLoc= sigma+2;
	rootID = rand() % (sigma-1);
	// hashTable= int_vector <SLEN> (M,emptyLoc);
	hashTable = int_vector <0> (0);
	hashTable.width(log2(emptyLoc)+1);
	hashTable.resize(M);
	for(unsigned long long i=0; i<M; i++) hashTable[i] = emptyLoc;
	D=new DArray(M);
	sl= new SubLayer(0.062303, M, 7);	
	randRootAdrs=(long) (rand() % M); 
	hashTable[randRootAdrs]=rootID;	
}

// A naive method to find modulor multiplicative inverse of
// 'a' under modulo 'm'
long long mBonsai::getModInverse(long long a, unsigned long long prime){
  a = a%prime;
  for (long long x=1; x<prime; x++)
    if ((a*x) % prime == 1)
      return x;
  return -1;
}

void  mBonsai::euclAlgorithm(unsigned long long prime){

  long long aTemp = (long long)(0.31*(double)prime); // 0.71
  long long aInvTemp = -1;
  while(true){
    aInvTemp= getModInverse(aTemp, prime);
    if(aInvTemp == -1)
      aTemp++;
    else
      break;
  }
  a = aTemp;
  aInv = aInvTemp;
  // cout<<"a: "<< a <<" aInv: "<< aInv <<endl;
}
/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool mBonsai::isPrime(unsigned long long input){
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
unsigned long long mBonsai::nextPrimeNumber(unsigned long long inputNumber){
	unsigned long long nextPrimeNumber;
	if(inputNumber<=0){
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
 * It goes through the dataset transaction by transaction
*/
void mBonsai::build()
{
	while(Transaction *t = data->getNext()) 
	{
		insert(t);
		delete t;
	}
	delete data;
}
/* 
 * called in build()
 * param: transaction of items where trans[0] is parent of trans[1] and so on. 
 * it calculates hashkey for every item and calls the setAddress 
 */
void mBonsai::insert(Transaction *t)
{
	singlepath = false;
	hashFunction *key = new hashFunction();
	unsigned long long prevInitAd=randRootAdrs;

	for(int i=0; i<t->length;++i)
	{
		key->getKey(prevInitAd, (unsigned long long)t->t[i],M,prime,a);
		prevInitAd=setAddress(key->initAd, key->quotient);
	}// end first for
	delete key;
}// end of insert

unsigned long long mBonsai::getInitAd(unsigned long long loc)
{
	//check if empty
	if (hashTable[loc]==emptyLoc  || (loc==randRootAdrs)) return valNotFound;
	if (D->D[loc]<7) return D->D[loc];
	unsigned long long tmpSat = sl->find (loc);	
	if (tmpSat != 135) return tmpSat+7;
	return mapSl.find(loc)->second;

}

unsigned long long mBonsai::getParent(unsigned long long location){
	unsigned long long initAd = getInitAd(location);
	if(initAd == valNotFound) return valNotFound;
	hashFunction h;
	return h.recoverParentLoc(initAd, hashTable[location], M, prime, aInv);	
}

/* 
 * called by insert
 * it sets the quotient value in the correct location
 * It handles displacement value accordingly
 * returns the hash loc so the next item (its child) can use it
 */
unsigned long long mBonsai::setAddress(unsigned long long initAd, unsigned int DIVM){

	unsigned int DCount=0;
	while(true)
	{
		//EMPTY LOC soo insert
		if(hashTable[initAd]==emptyLoc && (initAd!=randRootAdrs)){
			singlepath=true;
			hashTable[initAd]=DIVM;
			//if (itemID==5) origNodeCount++;
			++nodeNumberCount;
			if(DCount!=0){
				if(DCount<7){
					D->D[initAd]=DCount;
				}else if(DCount>=7 && DCount<=134){
					D->D[initAd]=7;
					sl->insert(initAd,DCount);
				}else if(DCount>134){
					D->D[initAd]=7;
					mapSl.insert ( std::pair <unsigned int, unsigned int> (initAd,DCount) );
				}
			}
			return initAd;
		 // check if it already exists 
		 }else if ( (hashTable[initAd]==DIVM) && (singlepath==false) && (initAd!=randRootAdrs) ){	
			//option for main
			if(DCount<7 || D->D[initAd]<7){
				if (DCount==D->D[initAd]){
				 	return initAd;
				}else{
					++DCount;
					++initAd;
					if (initAd>=M) initAd=0;
				}  
			//sublayer
			}else if (D->D[initAd]==7 && DCount>=7 && DCount<=134){
				unsigned int tmpSat = sl->find (initAd);
			     	if (tmpSat==135){ 
					++DCount;
					++initAd;
					if(initAd>=M) initAd=0;
				}else if ((tmpSat+7)==DCount){
				 	return initAd;
				}else{
					++DCount;
					++initAd;
					if(initAd>=M) initAd=0;
				}
			// final c++ hash map
			}else if (D->D[initAd]==7 && DCount>134){
				if(mapSl.find(initAd)==mapSl.end() || mapSl.find(initAd)->second!=DCount){ 
					++DCount;
					++initAd;
					if(initAd>=M) initAd=0;
				}else{
					return initAd;//mapSl.find(initAd)->second;
				}
			}
		// NOT EMPTY_LOC and NOT SAME_DIV.. MOVE_ON then
		}else{
			++DCount;
			++initAd;
			if(initAd>=M)	initAd=0;
		}
	}//end while

}//end setAddress

/* Search phase
 * Used for searchBenchmarks
 * Goes through a search file searching transactions by transactions.
 * This bench is designed spesifically for successful search operations
 * Outputs error if search is unsuccessful.
*/
void mBonsai::searchBench(char* file)
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
			prevInitAd=searchItem(key->initAd, key->quotient,str[i]);
		}
		delete key;
		str.clear();	
	}	
}//end searchBench

/*
 * reads transaction by transaction
 * to be searched
*/
vector<unsigned int> mBonsai::getVector(string s){
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
} // end getVector

/*
 * searches Items if not found prints error
*/ 
unsigned long long mBonsai::searchItem(unsigned long long initAd, unsigned int DIVM, unsigned int itemID)
{
	unsigned int DCount=0;
	while(true){
		//EMPTY LOC so item not Found
		if(hashTable[initAd]==emptyLoc){
			cout<<"We searched every corner of mame-Bonsai universe. Item is not found! :("<<endl;
	  		return valNotFound;
		// check if it alreadey exists 
		}else if((hashTable[initAd]==DIVM)&&(initAd!=randRootAdrs)){	
		//option for main
		if(DCount<7 || D->D[initAd]<7){
			if (DCount==D->D[initAd]){
				return initAd;
			}else{
				++DCount;
				++initAd;
				if (initAd>=M) initAd=0;
			}
		// option for sublayer
		}else if (D->D[initAd]==7 && DCount>=7 && DCount<=134){
			unsigned int tmpSat = sl->find (initAd);
		     	if (tmpSat==135){ 
				++DCount;
				++initAd;
				if(initAd>=M) initAd=0;
			}else if ((tmpSat+7)==DCount){
				return initAd;
			}else{
				++DCount;
				++initAd;
				if(initAd>=M) initAd=0;
			}
		// final option hash map
		}else if (D->D[initAd]==7 && DCount>134){
			if(mapSl.find(initAd)==mapSl.end() || mapSl.find(initAd)->second!=DCount){ 
				++DCount;
				++initAd;
				if(initAd>=M) initAd=0;
			}else{
				return initAd;
			}
		}
		// NOT EMPTY_LOC NOT SAME_DIV move to next one
		}else{
			++DCount;
			++initAd;
			if(initAd>=M)	initAd=0;
		}
	}//end while
}//end searchItem




