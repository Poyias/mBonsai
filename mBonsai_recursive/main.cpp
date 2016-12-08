#include "limits.h"
#include "mBonsai.h"
/* arguments
 * 1 nodeNum
 * 2 alphabet = sigma
 * 3 dataset
 * 4 loadFactor = 0.8
 * 5 searchFile
*/
void printSpace(mBonsai);
void printCHTSpace(mBonsai);
int main(int argc, char *argv[]) {
  // arguments

  unsigned int nodeNum = atoi(argv[1]);
  unsigned int sigma = atoi(argv[2]);
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
  // mbr.searchBench(searchFile); //search benchmark
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - begin;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "Total wall time[ " << ns / 1000000000 << " s]" << std::endl;
  std::cout << "nodeNum: " << mbr.nodeNumberCount << std::endl;
  printSpace(mbr);
  // printCHTSpace(mbr);
  return 0;
}

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

void printSpace(mBonsai mbr) {
  std::cout << "space in bits (in detail): " << std::endl;
  std::cout << "\tquotient_D: "
            << sdsl::size_in_bytes(mbr.quotient_D) /
                   (double)mbr.nodeNumberCount * 8.0
            << std::endl;
  std::cout << "\tDArray cht_sublayer: " << std::endl;
  std::cout << "\t\t"
            << sdsl::size_in_bytes(mbr.cht_sl.quotient_items_C) /
                   (double)mbr.nodeNumberCount * 8.0
            << std::endl;
  std::cout << "\tD subLayer (V): " << std::endl;
  std::cout << "\t\t"
            << (sdsl::size_in_bytes(mbr.cht_sl.V)) /
                   (double)mbr.nodeNumberCount * 8.0
            << std::endl;
  std::cout << "\tmapsl : " << endl;
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
  << "quotient_D: "
  << sdsl::size_in_bytes(mbr.quotient_D) / (double)mbr.nodeNumberCount * 8.0
  << " bits \nTotal DArray size: " << avgSize << " bits \nTotal: "
  << (sdsl::size_in_bytes(mbr.quotient_D) / (double)mbr.nodeNumberCount * 8.0) +
          avgSize
  << " bits\n"
  << "===========" << std::endl;
}