g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../DArray/mBonsai_recursive/subLayer.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  -DSLEN2=5 -DSAT=7
echo comp subLayer 

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../Hash/mBonsaiHash.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../DArray/mBonsai_recursive/DArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp DArray

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp mBonsai

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib subLayer.o DArray.o mBonsaiHash.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64
echo ready to run

./mBonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat

./mBonsai 3095560 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat



