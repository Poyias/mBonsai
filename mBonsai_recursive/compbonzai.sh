g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_recursive/subLayer.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  -DSLEN2=5 -DSAT=7
echo comp subLayer 

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../Hash/mBonsaiHash.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_recursive/DArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DDARRAYSIZE=3
echo comp DArray

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp mBonsai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o mBonsaiHash.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

./mBonsai 17183926 5 ../datasets/splitAccidents.dat 0.5 ../datasets/splitAccidents.dat

#./mBonsai 3095560 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat



