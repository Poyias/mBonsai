#include "limits.h"
#include "mBonsai.h"

/* arguments
 * 1 nodeNum
 * 2 alphabet = sigma
 * 3 dataset
 * 4 loadFactor = 0.8
 * 5 searchFile
*/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
void printSpace(mBonsai);
void printCHTSpace(mBonsai);

int main(int argc, char *argv[]) {
  // arguments
  uint64_t nodeNum = atoi(argv[1]);
  uint64_t sigma = atoi(argv[2]);
  char *file = argv[3];
  double loadFactor = atof(argv[4]);
  char *searchFile = argv[5];
  if (argc < 5) {
    std::cerr << "Use " << argv[0]
              << " <nodeNum> <sigma> <file_path> <1+epsilon> [searchFile]"
              << std::endl;
    exit(-1);
  }
  mBonsai mbr(nodeNum, sigma, loadFactor, file);
  auto begin = std::chrono::high_resolution_clock::now(); // wall time
  mbr.build();                                            // build
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - begin;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "Total wall time Build[ " << ns / 1000000 << " ms]" << std::endl;
  std::cout << "nodeNum: " << mbr.nodeNumberCount << std::endl;
  std::cout << "capacity: "
            << (double)mbr.cht_sl.nodeNumberCount /
                   (double)mbr.cht_sl.quotient_items_C.size()
            << std::endl;

  double traverseTimeMs = mbr.traverse();
  std::cout << "Total wall time simple traverse[ " << traverseTimeMs << " ms]"
            << std::endl;
  /*begin = std::chrono::high_resolution_clock::now(); // wall time
mbr.naiveTraverse();
end = std::chrono::high_resolution_clock::now();
dur = end - begin;
ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
std::cout << "Total wall time naiveTraverse[ " << ns / 1000000 << " ms]"
          << std::endl;*/
  begin = std::chrono::high_resolution_clock::now(); // wall time
  uint64_t schCounter = mbr.searchBench(searchFile);
  end = std::chrono::high_resolution_clock::now();
  dur = end - begin;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "Total wall time searchbench[ " << ns / 1000000 << " ms]"
            << std::endl;
  std::cout << "===" << std::endl;
  // mbr.extendTrie();
  printSpace(mbr);

  return 0;
}

/*
 * Prints the Compact hash table per CHT_size
*/
void printCHTSpace(mBonsai mbr) {
  std::cout << "CHT space(per cht_M): " << std::endl;
  std::cout << "quotients_sat_C: "
            << sdsl::size_in_bytes(mbr.cht_sl.quotient_items_C) /
                   (double)mbr.cht_sl.M * 8.0
            << std::endl;
  std::cout << "bitvectors (V): "
            << sdsl::size_in_bytes(mbr.cht_sl.V) / (double)mbr.cht_sl.M * 8.0
            << std::endl;
  std::cout << "==========" << std::endl;
}
/*
 * Prints detailed space sage of mBonsai
*/
void printSpace(mBonsai mbr) {
  std::cout << "space in bits (in detail): " << std::endl;
  std::cout << "\tquotient_D: "
            << sdsl::size_in_bytes(mbr.quotient_D) /
                   (double)mbr.nodeNumberCount * 8.0
            << std::endl;
  std::cout << "\tDArray cht_sublayer: " << std::endl;
  std::cout << "\t\t"
            << (sdsl::size_in_bytes(mbr.cht_sl.quotient_items_C) /
                (double)mbr.nodeNumberCount) *
                   8.0
            << std::endl;
  std::cout << "\tD subLayer (V): " << std::endl;
  std::cout << "\t\t"
            << (sdsl::size_in_bytes(mbr.cht_sl.V) /
                (double)mbr.nodeNumberCount) *
                   8.0
            << std::endl;
  std::cout << "\tmapsl : " << std::endl;
  std::cout << "\t\t"
            << 48.0 * 8.0 * mbr.mapSl.size() / (double)mbr.nodeNumberCount
            << std::endl;

  // average space per M
  double avgSize =
      (sdsl::size_in_bytes(mbr.cht_sl.quotient_items_C) +
       sdsl::size_in_bytes(mbr.cht_sl.V) + (mbr.mapSl.size() * 48.0)) *
      8.0;
  avgSize = avgSize / (double)mbr.nodeNumberCount;
  std::cout << "Space summary: " << std::endl;
  std::cout
      << "quotient only: "
      << ((sdsl::size_in_bytes(mbr.quotient_D) / (double)mbr.nodeNumberCount) *
          8.0) -
             3.0
      << " bits \nTotal DArray size: "
      << (3.0 +
          (((sdsl::size_in_bytes(mbr.cht_sl.quotient_items_C) +
             sdsl::size_in_bytes(mbr.cht_sl.V) + 48.0 * mbr.mapSl.size()) *
            8.0)) /
              (double)mbr.nodeNumberCount)
      << " bits\n"
      << "===========" << std::endl;
}