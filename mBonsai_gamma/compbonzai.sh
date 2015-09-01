g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib ../DArray/mBonsai_gamma/gammaBlock.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  

echo comp gammaBlock


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib ../DArray/mBonsai_gamma/blockedDArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64

echo comp blockedDArray 

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib ../Hash/mBonsaiHash.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib  mBonsaiGm.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 

echo comp mBonsaiGm
g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/"USERNAME"/include -L/home/"USERNAME"/lib  data.o gammaBlock.o blockedDArray.o mBonsaiHash.o mBonsaiGm.o main.cpp -o mBonsaiGm -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 

echo ready to run

./mBonsaiGm 17183926 5 ../datasets/splitAccidents.dat 0.8 256 ../datasets/splitAccidents.dat
./mBonsaiGm 3095560 5 ../datasets/SRR034939.dat 0.8 256 ../datasets/SRR034939.dat

