#include "Bonzai.h"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>  
#include <cmath>
#include <iostream>
#include <math.h>       /* ceil */
using namespace std;
double vmBefore, rssBefore;
double vmAfter, rssAfter;
/**
   * Fetches virtual memory and resident memory
   * from "proc/self/stat" file
   * gets VM and physical memory currently used in KB
   * @param double vm_usage, double resident_set
   * @return void.
   */
        void process_mem_usage(double * vm_usage, double * resident_set){
                *vm_usage     = 0.0;
                *resident_set = 0.0;

                FILE * memFile = fopen("/proc/self/stat", "r");

                unsigned long vsize;
                long rss;

                char str[60];
                int tmp = 0;
                for (unsigned int i=0; i < 22; i++)
                tmp = fscanf(memFile, "%s", str);

                tmp = fscanf(memFile, "%ld", &vsize);
                tmp = fscanf(memFile, "%ld", &rss);
                *vm_usage = tmp; // just to stop warning about unused variable
                long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
                *vm_usage     = vsize / 1024.0;
                *resident_set = rss * page_size_kb;

                fclose(memFile);
        }//end process_mem_usage

// arguments
// 1 nodeNum
// 2 type
// 3 alphabet
// 4 dataset
// 5 loadFactor
// 6 blockSize

int main(int argc, char *argv[])
{
	unsigned int nodeNum = atoi(argv[1]);
	unsigned int type = atoi(argv[2]);
	unsigned int sigma = atoi(argv[3]);
	char* file = argv[4];
	double loadFactor = atof(argv[5]);
	unsigned int blockSize = atoi(argv[6]);
	char* searchFile=argv[7];
	double numBl = (double) ( ((double)nodeNum/loadFactor)/(double)blockSize)-0.0005;
	unsigned int numBlocks = numBl+1;
	double buildClockTime;

	ofstream myfile;
	myfile.open("gamma search-benchmarks.csv",ios::app);
	cout<<file<<","<<nodeNum<<","<<sigma<<endl;

	clock_t start;
        auto begin = chrono::high_resolution_clock::now();    
	start = clock();

	Bonzai *b =  new Bonzai(nodeNum, sigma, loadFactor, file, type, blockSize, numBlocks);
	b->readDataset();

	buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	auto end = chrono::high_resolution_clock::now();
    	auto dur = end - begin;
   	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	myfile<<file<<",";
    	cout << "Trie built Wall [" << ms*0.001 << "s]" << endl;
	myfile<< ms*0.001 << ",";
	myfile<< buildClockTime << ",";
	cout << "Trie built [" << buildClockTime << "s]" << endl;

 
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
	myfile<< DArrayCost<<",,";

	  begin = chrono::high_resolution_clock::now();    
	  start = clock();

	  b->searchBench(searchFile);

	  buildClockTime = (clock()-start)/double(CLOCKS_PER_SEC);
	  end = chrono::high_resolution_clock::now();
	  dur = end - begin;
	  ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	  //////////

	  myfile<<b->searchItems<<","<<b->searchTrans<<",";

	  myfile<< ms*0.001<<",";
	  myfile<<buildClockTime<<",";
	  double perItem=(double)ms*0.001/(double)b->searchItems;
	  double perTrans=(double)ms*0.001/(double)b->searchTrans;
	  myfile<<perItem<<","<<perTrans<<endl;
	  cout << "Search time(wall) [" << ms*0.001 << "s]" << endl;
	  cout << "Search Time(clock) [" << buildClockTime << "s]" << endl;
	  cout<<"node Count: "<<b->nodeNumberCount<<endl;
	 
return 0;
}

