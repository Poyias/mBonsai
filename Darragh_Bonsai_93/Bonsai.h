#include "sdsl/int_vector.hpp"
#include <sdsl/bit_vectors.hpp>
#include "../readio/data.h"
#include "../Hash/orighashFunc.h"
#include "limits.h"

using namespace sdsl;
using namespace std;

class Bonsai {

public:
//structure
int_vector<SLEN> hashTable;
bit_vector V;
bit_vector C;

//init
Bonsai(){}
Bonsai(unsigned int nodeNumber, unsigned int sigma, double loadFactor, char* file);
void setData(char *file){data = new Data(file);}

//build phase
void build();
unsigned int insert (Transaction *t,unsigned int line);
//navigations collision handling
unsigned int getAssociatedC(unsigned int curAddress);
unsigned int findSpace(unsigned int cVal, unsigned int quotient);
bool itemExists(unsigned int cVal,unsigned int quotient);
void startNewBlock(unsigned int vVal,unsigned int cVal);
unsigned int findItem(unsigned int vVal,unsigned int cVal, unsigned int quotient);

//misc
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

//search phase
void searchBench(char* file);
vector <unsigned int> getVector(string s);
unsigned int search (vector<unsigned int> t);

//args for printing and counting
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
Data* data; //readio
};
