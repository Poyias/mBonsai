#include "blockedDArray.h"

blockedDArray::blockedDArray(unsigned int size, unsigned int numBlocks)
{	
	this->size=size;
	darray = new gammaBlock*[numBlocks];
	for(unsigned int i=0; i<numBlocks;i++){
		darray[i] = new gammaBlock(size);
	}
}

unsigned int blockedDArray::get(unsigned int loc)
{
	unsigned int gammaBlock= loc/size;
	return darray[gammaBlock]->get(loc%size);
}

void blockedDArray::setT(unsigned int loc,unsigned int item)
{
	unsigned int gammaBlock= loc/size;    //get gammaBlock
	darray[gammaBlock]->set ((unsigned int)(loc%size), item );
	
}
