#include "sdsl/int_vector.hpp"
#include "../readio/data.h"
#include "../DArray/mBonsai_gamma/blockedDArray.h"
using namespace sdsl;

class mBonsaiGm {

public:
mBonsaiGm(){}

mBonsaiGm(unsigned int nodeNumber, unsigned int sigma, double loadFactor,char* file,unsigned int blockSize, unsigned int numBlocks);
void setData(char *file){data = new Data(file);}
void readDataset();
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);
void insertTrans(Transaction *t);
unsigned long long setAddress(unsigned long long initAd, unsigned int DIVM, unsigned int itemID);
unsigned long long mBonsaiGm::searchItem(unsigned long long initAd, unsigned int DIVM, unsigned int itemID);
vector<unsigned int> mBonsaiGm::getVector(string s);

int_vector<SLEN> hashTable;
blockedDArray *D;
Data* data ;

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
//unsigned int searchItems;
//unsigned int  searchTrans;

};
