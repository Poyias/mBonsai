#include "Bonsai.h"

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor

int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);

	cout<<nodeNum<<", "<<sigma<<", "<<file<<", "<<loadFactor<<endl;
        auto begin = chrono::high_resolution_clock::now();    
	clock_t start;
	start = clock();

	Bonsai *b =  new Bonsai(nodeNum, sigma, loadFactor, file);
	b->readDataset();

	double buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	auto end = chrono::high_resolution_clock::now();
    	auto dur = end - begin;
   	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    	cout << "Trie built Wall [" << ms*0.001 << "s]" << endl;
	cout << "Trie built [" << buildClockTime << "s]" << endl;
	cout<<"node Count: "<<b->nodeNumberCount<<endl;
	cout<<"original node Count: "<<b->origNodeCount<<endl;
	double avgSize = (size_in_bytes(b->hashTable) +size_in_bytes(b->V) + size_in_bytes(b->C) ) *8.0;
	avgSize=avgSize/(double)b->M;
	cout<<avgSize<<endl;

return 0;
}


