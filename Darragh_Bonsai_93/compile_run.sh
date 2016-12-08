g++  -O3 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../Hash/orighashFunc.cpp ../readio/data.cpp Bonsai.cpp main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64
echo ready to run

./Bonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat
./Bonsai 3095560 5    ../datasets/SRR034939.dat       0.8 ../datasets/SRR034939.dat 