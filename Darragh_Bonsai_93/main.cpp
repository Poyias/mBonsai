#include "Bonsai.h"

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 searchFile
void printSpace(Bonsai);

int main(int argc, char *argv[]) {
  uint32_t nodeNum = atol(argv[1]);
  uint32_t sigma = atoi(argv[2]);
  char *file = argv[3];
  double loadFactor = atof(argv[4]);

  Bonsai b(nodeNum, sigma, loadFactor, file);
  b.build();
  std::cout << "node Count: " << b.nodeNumberCount << std::endl;
  b.searchBench(argv[5]);
  printSpace(b);

  return 0;
}

void printSpace(Bonsai b) {
  double quotientSpace =
      sdsl::size_in_bytes(b.quotient) / (double)b.nodeNumberCount * 8.0;
  double VCspace = (sdsl::size_in_bytes(b.V) + sdsl::size_in_bytes(b.C)) /
                   (double)b.nodeNumberCount * 8.0;
  std::cout << "space in bits (in detail): " << std::endl;
  std::cout << "\tquotient: " << quotientSpace << std::endl;
  std::cout << "\tD subLayer (C+V): " << std::endl;
  std::cout << "\t\t" << VCspace << std::endl;
  std::cout << "Total space (per N): " << quotientSpace + VCspace << std::endl;
}