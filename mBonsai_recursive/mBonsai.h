#include "sdsl/int_vector.hpp"
#include "../readio/data.h"
#include "../DArray/mBonsai_recursive/DArray.h"
#include "../DArray/mBonsai_recursive/subLayer.h"
#include "limits.h"

using namespace sdsl;

class mBonsai {

public:
//structure
int_vector<SLEN> hashTable;
DArray *D; //displacement array 
SubLayer *sl; //sublayer displacement array 
map<unsigned int,unsigned int> mapSl; // overflown Displacement

//init
mBonsai(){}
mBonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file);
void setData(char *file){data = new Data(file);}

//build
void build();
void insert(Transaction *t);
unsigned long long setAddress(unsigned long long initAd, unsigned int DIVM);

//search bencmarks
void searchBench(char * file);
vector <unsigned int> getVector(string s); //readio
unsigned long long searchItem(unsigned long long initAd, unsigned int DIVM, unsigned int itemID);

//misc
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

//args for printing and counting
unsigned long long sigma;
unsigned long long M;
unsigned int nodeNumberCount;
unsigned int origNodeCount;

private:
bool singlepath;
unsigned long long rootID;
unsigned long long prime;
unsigned long long a;
unsigned long long valNotFound;
unsigned long long randRootAdrs;
unsigned long long emptyLoc;
Data* data; // readio
};





