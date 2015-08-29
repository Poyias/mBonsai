#include "mBonsai.h"
#include "limits.h"
/* arguments
 * 1 nodeNum
 * 2 alphabet = sigma
 * 3 dataset
 * 4 loadFactor = 0.8
 * 5 searchFile
*/
int main(int argc, char *argv[])
{
	//arguments
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);
	char* searchFile= argv[5];

	mBonsai *mbr =  new mBonsai(nodeNum, sigma, loadFactor, file);
	mbr->build(); // build
	mbr->searchBench(searchFile); //search benchmark
	cout<<"nodeNumberCount: "<<mbr->nodeNumberCount<<endl;

return 0;
}

