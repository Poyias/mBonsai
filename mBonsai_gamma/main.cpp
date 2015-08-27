#include "mBonsaiGm.h"
// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 blockSize

int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);
	unsigned int blockSize = atoi(argv[5]);
	double numBl = (double) ( ((double)nodeNum/loadFactor)/(double)blockSize)-0.0005;
	unsigned int numBlocks = numBl+1;
	double buildClockTime;
	cout<<file<<","<<nodeNum<<","<<sigma<<endl;

	mBonsaiGm *b =  new mBonsaiGm(nodeNum, sigma, loadFactor, file, blockSize, numBlocks);
	
	clock_t start;
        auto begin = chrono::high_resolution_clock::now();    
	start = clock();
	b->readDataset();

	buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	auto end = chrono::high_resolution_clock::now();
    	auto dur = end - begin;
   	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    	cout << "Trie built Wall [" << ms*0.001 << "s]" << endl;
	cout << "Trie built [" << buildClockTime << "s]" << endl;
	cout << b->nodeNumberCount<<endl;

	//myfile << ( ((double)vmAfter-(double)vmBefore)/(double)b->M)*(1024.0*8.0) << ", " << ( ((double)rssAfter-(double)rssBefore)/(double)b->M )*(1024.0*8.0) <<",";

 
//cout << "vm: "<< ( ((double)vmAfter-(double)vmBefore)/(double)b->M )*(1024.0*8.0) << ", " << "rss: "<< ( ((double)rssAfter-(double)rssBefore)/(double)b->M )*(1024.0*8.0) << endl;
/*
 
 double DArrayCost = 0;
 for (unsigned int i=0; i<numBlocks;i++){
   DArrayCost +=(size_in_bytes(b->D->darray[i]->dBlock)*8);
 }
 DArrayCost= DArrayCost/numBlocks;
 cout<<"avg gamma block space: "<< DArrayCost<<endl;
 DArrayCost= DArrayCost/blockSize;
 cout<<"avg space per value: "<< DArrayCost<<endl;
 DArrayCost+=(((double)numBlocks*64.0)/(double) b->M);
 cout<<"Total DArrayCost incl pointers(per M): "<<  DArrayCost<<endl;
 //myfile<< DArrayCost<<endl;
*/
return 0;
}

