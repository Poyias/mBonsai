#include "sdsl/int_vector.hpp"
#include "../readio/data.h"
#include "../DArray/mBonsai_gamma/blockedDArray.h"
#include "limits.h"

using namespace sdsl;

class mBonsaiGm {

public:

//structure
int_vector<SLEN> hashTable;
blockedDArray *D;

//init
mBonsaiGm(){}
mBonsaiGm(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file,unsigned int blockSize, unsigned int numBlocks);
void setData(char *file){data = new Data(file);}

//build
void build();
void insertTrans(Transaction *t);
unsigned long long setAddress(unsigned long long initAd, unsigned int DIVM);

//search benchmarks
void searchBench(char * file);
vector <unsigned int> getVector(string s); // readio
unsigned long long searchItem(unsigned long long initAd, unsigned int DIVM);

//misc
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

// args for printing and counting
unsigned long long sigma;
unsigned long long M;
unsigned int nodeNumberCount;


private:

unsigned long long nodeNotFound;
unsigned int rootID;
unsigned long long prime;
unsigned long long a;
unsigned long long aInv;
unsigned int randRootAdrs;
unsigned int emptyLoc;
Data* data ; //readio
};
