#include "sdsl/int_vector.hpp"
#include <iostream>
using namespace sdsl;
using namespace std;

#ifndef SUBLAYER
#define SUBLAYER 
class SubLayer {

public:
//structure
int_vector<0> quotient_items;
bit_vector V;
bit_vector C;

//init
SubLayer(){}
SubLayer(double perOfM, unsigned long long universe, unsigned int difference);

//misc
bool isPrime(unsigned long long input);
unsigned long long nextPrimeNumber(unsigned long long inputNumber);

//build phase
void insert (unsigned long long key, unsigned int value);
unsigned long long getChangeBitLoc(unsigned long long curAddress);
void findSpace(unsigned long long cVal,unsigned long long quotient);
unsigned long long find(unsigned long long key);
void startNewBlock(unsigned long long vVal,unsigned long long cVal);
bool itemExists(unsigned long long cVal,unsigned long long quotient);
//fetch displacement value stored as satelite data
unsigned long long getSatelite(unsigned long long vVal, unsigned long long cVal, unsigned long long quotients);
inline unsigned long long getC(unsigned long long loc){return quotient_items[loc]&1;}

unsigned int nodeNumberCount;
unsigned long long M;
private:
unsigned int dif;
unsigned long long cmax;
unsigned long long valNotFound;
unsigned long long sigma;
unsigned long long prime;
unsigned long long a;
unsigned long long aInv;
unsigned long long emptyLoc;
unsigned long long curEmptySlot;
unsigned long long satWidth;

};
#endif
