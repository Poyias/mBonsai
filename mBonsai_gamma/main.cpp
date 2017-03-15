#include "mBonsaiGm.h"
#include <iostream>
#include <math.h> /* ceil */
using namespace std;

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 blockSize
// 6 searchFile
void printSpace(mBonsaiGm, uint32_t);

int main(int argc, char* argv[])
{
    uint32_t nodeNum = atoi(argv[1]);
    uint32_t sigma = atoi(argv[2]);
    char* file = argv[3];
    double loadFactor = atof(argv[4]);
    uint32_t blockSize = atoi(argv[5]);
    uint32_t numBlocks = (double)(((double)nodeNum / loadFactor) / (double)blockSize) + 1;
    char* searchFile = argv[6];

    mBonsaiGm mbGm(nodeNum, sigma, loadFactor, file, blockSize, numBlocks);
    auto begin = std::chrono::high_resolution_clock::now(); // wall time
    mbGm.build();
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    std::cout << "Total wall time Build[ " << ns / 1000000 << " ms]" << std::endl;
    std::cout << "NodeNumber : " << mbGm.nodeNumberCount << std::endl;

    begin = std::chrono::high_resolution_clock::now(); // wall time
    uint64_t schCounter = mbGm.searchBench(searchFile);
    end = std::chrono::high_resolution_clock::now();
    dur = end - begin;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    std::cout << "Total wall time searchbench[ " << ns / 1000000 << " ms]"
              << std::endl;
    printSpace(mbGm, numBlocks);
    return 0;
}

void printSpace(mBonsaiGm mbGm, uint32_t numBlocks)
{
    double quotientSpace = sdsl::size_in_bytes(mbGm.quotient) / (double)mbGm.nodeNumberCount * 8.0;
    double sumBlockSpace = 0;
    for (uint32_t i = 0; i < numBlocks; i++) {
        sumBlockSpace += (sdsl::size_in_bytes(mbGm.D.darray[i]->dBlock) * 8.0);
    }
    sumBlockSpace /= (double)mbGm.nodeNumberCount;
    double pointerSpace = (double)numBlocks * 64.0 / (double)(mbGm.nodeNumberCount * 8.0);
    std::cout << "space in bits (in detail): " << std::endl;
    std::cout << "quotient: " << quotientSpace << std::endl;
    std::cout << "DArray Blocked Gamma: " << sumBlockSpace << std::endl;
    std::cout << "Block Pointers: " << pointerSpace << std::endl;
    // average space per M
    std::cout << "Total Space: " << quotientSpace + sumBlockSpace + pointerSpace
              << std::endl;
}
