#include "Bonsai.h"

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 searchFile

int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);

	Bonsai *b =  new Bonsai(nodeNum, sigma, loadFactor, file);
	b->build();
	cout<<"node Count: "<<b->nodeNumberCount<<endl;
	b->searchBench(argv[5]);
return 0;
}


