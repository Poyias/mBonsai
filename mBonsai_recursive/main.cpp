#include "mBonsai.h"
#include "limits.h"
/* arguments
 * 1 nodeNum
 * 2 alphabet = sigma
 * 3 dataset
 * 4 loadFactor = 0.8
 * 5 searchFile
*/
void printSpace(mBonsai*);
void printCHTSpace(mBonsai*);
int main(int argc, char *argv[])
{
	//arguments

	unsigned int nodeNum = atoi(argv[1]);
	unsigned int sigma = atoi(argv[2]);
	char* file = argv[3];
	double loadFactor = atof(argv[4]);
	char* searchFile= argv[5];

	mBonsai *mbr =  new mBonsai(nodeNum, sigma, loadFactor, file);
    auto begin = chrono::high_resolution_clock::now(); // wall time 
	mbr->build(); // build
	// cout<<"nodeNumberCount: "<<mbr->nodeNumberCount<<endl;
	// mbr->searchBench(searchFile); //search benchmark
	auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    cout << "Total wall time[ "<<ns/1000000000<<" s]" << endl;
	/*printSpace(mbr);*/
	printCHTSpace(mbr);
return 0;
}

void printCHTSpace(mBonsai* mbr){
cout<<"CHT space(per M): "<<endl;
cout<<"quotients_sat: " 	<< size_in_bytes(mbr->sl->quotient_items)/(double)mbr->sl->M*8.0 << endl <<"bitvectors (V+C): " << (size_in_bytes(mbr->sl->V)+size_in_bytes(mbr->sl->C))/(double)mbr->sl->M*8.0<< endl<<"=========="<<endl;
}

void printSpace(mBonsai* mbr){
cout << "space in bits (in detail): "<<"\tht: "  << size_in_bytes(mbr->hashTable)/(double)mbr->nodeNumberCount*8.0 << endl <<
	"\t\tmain D layer: " 	<< size_in_bytes(mbr->D->D)/(double)mbr->nodeNumberCount*8.0 << endl <<
	"\t\tD sublayer: " 	<< size_in_bytes(mbr->sl->quotient_items)/(double)mbr->nodeNumberCount*8.0 << endl <<
	"\t\tD subLayer (V+C): " << (size_in_bytes(mbr->sl->V)/*+size_in_bytes(mbr->sl->C)*/)/(double)mbr->nodeNumberCount*8.0<< endl<<
	// "\t\tD sublayer satellite: " << 8.0*(size_in_bytes(mbr->sl->satData))/(double)mbr->nodeNumberCount<< endl <<
	"\t\tmapsl : "	<< 48.0*8.0*mbr->mapSl.size()/(double)mbr->nodeNumberCount<<endl;

	//average space per M
	double avgSize = (  //size_in_bytes(mbr->hashTable)+ // Qarray
						size_in_bytes(mbr->D->D) + //D_0
						size_in_bytes(mbr->sl->quotient_items) + //BonOr Qarray
						size_in_bytes(mbr->sl->V) + //BonOr Virgin bit
						// size_in_bytes(mbr->sl->C) + //BonOr Change bit
						// size_in_bytes(mbr->sl->satData) +//BonOr sat Data
						(mbr->mapSl.size()*48.0)
					 )*8.0;
	avgSize=avgSize/(double)mbr->nodeNumberCount;
	cout<< "Space summary: "<<endl<<
	"hashTable: "<<  size_in_bytes(mbr->hashTable)/(double)mbr->nodeNumberCount*8.0<< " bits \nTotal DArray size: "<<
	avgSize<<" bits \nTotal: "<<  (size_in_bytes(mbr->hashTable)/(double)mbr->nodeNumberCount*8.0 ) + avgSize<<" bits\n"<<
	"==========="<<endl;
}