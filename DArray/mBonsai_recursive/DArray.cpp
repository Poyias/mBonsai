#include "DArray.h"

DArray::DArray(unsigned long long size)
{	
	D = int_vector <DARRAYSIZE> (size,0);
	this->size=size;
}

