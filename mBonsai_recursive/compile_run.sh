g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp mBonsai.cpp main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64

./mBonsai 3095560 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat
./mBonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat
