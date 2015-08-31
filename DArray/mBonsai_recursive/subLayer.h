#include "sdsl/int_vector.hpp"

using namespace sdsl;

class SubLayer {

public:
//structure
int_vector<SLEN2> hashTable;
bit_vector V;
bit_vector C;
int_vector<SAT> satData;

//init
SubLayer(){}
SubLayer(double perOfM, unsigned long long M, unsigned int difference);

//misc
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

//build phase
void insert (unsigned long long key, unsigned int value);
unsigned long long getChangeBitLoc(unsigned long long curAddress);
void findSpace(unsigned long long vVal,unsigned long long cVal,unsigned long long quotient);
unsigned long long find(unsigned long long key);
void startNewBlock(unsigned int vVal,unsigned int cVal);
bool itemExists(unsigned long long cVal,unsigned long long quotient);

//fetch displacement value stored as satelite data
unsigned int getSatelite(unsigned int vVal, unsigned int cVal, unsigned int quotients);
unsigned int nodeNumberCount;

private:
unsigned int dif;
unsigned long long cmax;
unsigned long long valNotFound;
unsigned long long sigma;
unsigned long long Msl;
unsigned long long prime;
unsigned long long a;
unsigned long long aInv;
unsigned int emptyLoc;
unsigned int curEmptySlot;

};
