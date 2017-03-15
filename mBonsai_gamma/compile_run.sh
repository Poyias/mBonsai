g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib DArray/gammaBlock.cpp DArray/blockedDArray.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp mBonsaiGm.cpp main.cpp -o mBonsaiGm -lsdsl -ldivsufsort -ldivsufsort64

echo ready to run

./mBonsaiGm 3095560 5 ../datasets/SRR034939.dat 0.8 256 ../datasets/SRR034939.dat
./mBonsaiGm 4242318 442 ../datasets/tranSortedAccidents.dat 0.8 256 ../datasets/tranSortedAccidents.dat
