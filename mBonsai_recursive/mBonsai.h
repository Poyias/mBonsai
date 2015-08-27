#include "sdsl/int_vector.hpp"
#include "../readio/data.h"
#include "../DArray/mBonsai_recursive/DArray.h"
#include "../DArray/mBonsai_recursive/subLayer.h"
#include "limits.h"

using namespace sdsl;

class mBonsai {

public:
mBonsai(){}

 mBonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file);
void setData(char *file){data = new Data(file);}
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

void build();
void insert(Transaction *t);
unsigned long long setAddress(unsigned long long initAd, unsigned int DIVM);
void searchBench(char * file);
vector <unsigned int> getVector(string s);
unsigned long long searchItem(unsigned long long initAd, unsigned int DIVM, unsigned int itemID);

int_vector<SLEN> hashTable;

DArray *D;
SubLayer *sl;
map<unsigned int,unsigned int> mapSl;


unsigned long long sigma;
unsigned long long M;
unsigned int nodeNumberCount;
 unsigned int origNodeCount;
 unsigned int searchItems;
 unsigned int searchTrans;
private:
bool singlepath;
unsigned int rootID;
unsigned long long prime;
unsigned long long a;
unsigned long long valNotFound;
unsigned int randRootAdrs;
unsigned int emptyLoc;
Data* data ;
};





