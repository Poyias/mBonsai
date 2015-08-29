#include "mBonsaiGm.h"
#include <math.h>       /* ceil */

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 blockSize
// 6 searchFile

int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);
	unsigned int blockSize = atoi(argv[5]);
	unsigned int numBlocks = ceil((double) ( ((double)nodeNum/loadFactor)/(double)blockSize) );

	mBonsaiGm *mbGm =  new mBonsaiGm(nodeNum, sigma, loadFactor, file, blockSize, numBlocks);
	mbGm->build();
	cout << mbGm->nodeNumberCount<<endl;
	mbGm-> searchBench(argv[6]);

return 0;
}

