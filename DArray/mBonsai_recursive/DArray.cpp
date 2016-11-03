#include "DArray.h"

DArray::DArray(unsigned long long size)
{	
	D = int_vector <3> (size,0);
	this->size=size;
}

