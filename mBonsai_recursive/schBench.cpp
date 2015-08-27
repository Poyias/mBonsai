#include "Bonzai.h"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>  
#include <cmath>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sdsl;

// arguments
// 1 nodeNum
// 2 type
// 3 alphabet
// 4 dataset
// 5 loadFactor
// 6 searchFile
int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int type = atoi(argv[2]);
	unsigned int sigma = atoi(argv[3]);
	char* file = argv[4];
	double loadFactor = atof(argv[5]);
	char* searchFile=argv[6];
	double buildClockTime;
	//build Trie
	Bonzai *b =  new Bonzai(nodeNum, sigma, loadFactor, file, type);
	b->readDataset();

	cout<<file<<","<<b->nodeNumberCount<<","<<sigma<<endl;
	
	cout<<"argc: "<<argc<<endl;
	if (argc>6){
	  //////////
	  clock_t start;
	  auto begin = chrono::high_resolution_clock::now();    
	  start = clock();

	  b->searchBench(argv[6]);

	  buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	  auto end = chrono::high_resolution_clock::now();
	  auto dur = end - begin;
	  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	  //////////
	  ofstream myfile;
	  myfile.open("m-search-bench.csv",ios::app);

	  myfile<<file<<","<<b->nodeNumberCount<<","<<sigma<<",";
	  myfile<<b->searchItems<<","<<b->searchTrans<<",";

	  myfile<< ms*0.001<<",";
	  myfile<<buildClockTime<<",";
	  double perItem=(double)ms*0.001/(double)b->searchItems;
	  double perTrans=(double)ms*0.001/(double)b->searchTrans;
	  myfile<<perItem<<","<<perTrans<<endl;
	  cout << "Search time(wall) [" << ms*0.001 << "s]" << endl;
	  cout << "Search Time(clock) [" << buildClockTime << "s]" << endl;
	  cout<<"node Count: "<<b->nodeNumberCount<<endl;
	  cout<<"original node Count: "<<b->origNodeCount<<endl;
	  cout<<"sl-nodeNumberCount: "<<b->sl->nodeNumberCount<<"  sl->M:"<<b->sl->Msl<<endl;
	 
	}
	cout<<"---------------------------------"<<endl;
	
return 0;
}

