#include "sdsl/int_vector.hpp"
#include <sdsl/bit_vectors.hpp>
#include "../readio/data.h"
#include "../Hash/orighashFunc.h"

using namespace sdsl;
using namespace std;

class Bonsai {

public:
Bonsai(){}
Bonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor, char* file);
void setData(char *file){data = new Data(file);}
void readDataset();

unsigned int insert (Transaction *t,unsigned int line);
unsigned int getAssociatedC(unsigned int curAddress);
unsigned int findSpace(unsigned int cVal, unsigned int quotient, unsigned int initAd);
bool itemExists(unsigned int cVal,unsigned int quotient, unsigned int initAd);
unsigned int findItem(unsigned int vVal,unsigned int cVal,
		unsigned int quotient, unsigned int initAd);
void startNewBlock(unsigned int vVal,unsigned int cVal);

bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);
vector <unsigned int> getVector(string s);

unsigned int search (vector<unsigned int> t);
void searchBench(char* file);
Data* data ;

int_vector<SLEN> hashTable;
bit_vector V;
bit_vector C;

unsigned long long sigma;
unsigned long long M;
unsigned int nodeNumberCount;
unsigned int origNodeCount;

private:

unsigned long long cmax;
unsigned long long noValue;
unsigned int rootID;
unsigned int rootLambda;
unsigned long long lambda;
unsigned long long prime;
unsigned int a;
unsigned int rootAddress;
unsigned int emptySymbol;
unsigned int curEmptySlot;
unsigned int searchItems;
unsigned int searchTrans;
};
