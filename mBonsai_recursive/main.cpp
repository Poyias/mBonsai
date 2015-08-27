#include "mBonsai.h"
#include "limits.h"
/* arguments
 * 1 nodeNum
 * 2 alphabet = sigma
 * 3 dataset
 * 4 loadFactor
*/
int main(int argc, char *argv[])
{
	//arguments
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);
	char* searchFile= argv[5];

	double buildClockTime;
	cout<<file<<","<<nodeNum<<","<<sigma<<endl;
	clock_t start; //clock time
        auto begin = chrono::high_resolution_clock::now(); // wall time 
	start = clock();
	//mBonsai recursive init
	mBonsai *mbr =  new mBonsai(nodeNum, sigma, loadFactor, file);
	mbr->build();
	//calc time
	buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	auto end = chrono::high_resolution_clock::now();
    	auto dur = end - begin;
   	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	//printing
	//time
    	cout << "Trie built Wall [" << ms*0.001 << "s]" << endl;
	cout << "Trie built [" << buildClockTime << "s]" << endl;
	//nodeCount
	cout<<"node Count: "<<mbr->nodeNumberCount<<endl;
	cout<<"original node Count: "<<mbr->origNodeCount<<endl;
	//space per part of mBonsai
	cout << "ht: " << size_in_bytes(mbr->hashTable) << ", darray: " << size_in_bytes(mbr->D->D) << ", sl HT: " <<size_in_bytes(mbr->sl->hashTable) <<", V+C: "<< size_in_bytes(mbr->sl->V)+size_in_bytes(mbr->sl->C)<<", sl SATD: "<<size_in_bytes(mbr->sl->satData)<<endl;
	//average space per M
	double avgSize = (size_in_bytes(mbr->hashTable)+ size_in_bytes(mbr->D->D) + size_in_bytes(mbr->sl->hashTable) + size_in_bytes(mbr->sl->V)+size_in_bytes(mbr->sl->C) + size_in_bytes(mbr->sl->satData))*8.0;
	avgSize=avgSize/(double)mbr->M;
	cout<<avgSize<<endl;
	cout<<"---------------------------------"<<endl;	
return 0;
}

