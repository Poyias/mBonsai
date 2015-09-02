g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I~/include -L~/lib ../Hash/orighashFunc.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp origHash

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I~/include -L~/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64
echo comp data

g++  -O3 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I~/include -L~/lib Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9
echo comp Bonsai

g++  -O3 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I~/include -L~/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9
echo ready to run

./Bonsai 17183926 5 ../datasets/splitAccidents.dat 0.8 ../datasets/splitAccidents.dat

./Bonsai 3095560 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat



