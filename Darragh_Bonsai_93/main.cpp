#include "Bonsai.h"
#include <iostream>
using namespace std;


// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 searchFile
double printSpace(Bonsai);

int main(int argc, char *argv[]) {
  ofstream outdata;
  outdata.open("benchmarksDarragh.csv", ios::app);

  uint32_t nodeNum = atol(argv[1]);
  uint32_t sigma = atoi(argv[2]);
  char *file = argv[3];
  double loadFactor = atof(argv[4]);
  char *searchFile = argv[5];

  Bonsai b(nodeNum, sigma, loadFactor, file);
  auto begin = std::chrono::high_resolution_clock::now(); // wall time
  b.build();
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = end - begin;
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();  
  std::cout << "Total wall time Build[ " << ns / 1000000 << " ms]"
            << std::endl;
  std::cout << "node Count: " << b.nodeNumberCount << std::endl;
  outdata << file<<", "<< b.nodeNumberCount<<", "<<sigma<<", " << ns / 1000000<<", ";
  begin = std::chrono::high_resolution_clock::now(); // wall time
  uint64_t schCounter = b.searchBench(searchFile);
  end = std::chrono::high_resolution_clock::now();
  dur = end - begin;
  ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
  std::cout << "Total wall time searchbench[ " << ns / 1000000 << " ms]"
            << std::endl;
  outdata << ns / 1000000 << ", "<<(ns /(double)schCounter) << ","<<printSpace(b)<< endl;

  return 0;
}

double printSpace(Bonsai b) {
  double quotientSpace =
      sdsl::size_in_bytes(b.quotient) / (double)b.nodeNumberCount * 8.0;
  double VCspace = (sdsl::size_in_bytes(b.V) + sdsl::size_in_bytes(b.C)) /
                   (double)b.nodeNumberCount * 8.0;
  std::cout << "space in bits (in detail): " << std::endl;
  std::cout << "\tquotient: " << quotientSpace << std::endl;
  std::cout << "\tD subLayer (C+V): " << std::endl;
  std::cout << "\t\t" << VCspace << std::endl;
  std::cout << "Total space (per N): " << quotientSpace + VCspace << std::endl;
  return quotientSpace + VCspace;
}