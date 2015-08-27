g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_gamma/gammaBlock.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  

echo comp gammaBlock


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_gamma/blockedDArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64

echo comp blockedDArray 

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../Hash/mBonsaiHash.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib  mBonsaiGm.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 

echo comp mBonsaiGm
g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib  data.o gammaBlock.o blockedDArray.o hashFunction.o mBonsaiGm.o main.cpp -o mBonsaiGm -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 

echo ready to run
./mBonsaiGm 35004 300 ../../../../Desktop/sortedMushroom.dat 0.8 256 

#./mBonsaiGm 3095560  3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034939.txt 0.8 256
#./mBonsaiGm 21005059 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034944.txt 0.8 256
#./mBonsaiGm 1556235309 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034940_1.txt 0.8 256
#./mBonsaiGm 1728553810 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034945_1.txt 0.8 256


#g++ -std=c++11 -Wall -Wextra  -DNDEBUG  -O3 -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib expl-03.cpp -o expl3 -lsdsl -ldivsufsort -ldivsufsort64 

#./mBonsaiGm 10 3 6 sample 0.8 1

#echo chess

#./mBonsaiGm 38610 3 75 /cxml-data/ap480/sortedChess.dat 0.8 256
#./mBonsaiGm 359292 3 129 /cxml-data/ap480/sortedConnect.dat 0.8 256
#./mBonsaiGm 27349 3 119 /cxml-data/ap480/sortedMushroom.dat 0.8 256
#./mBonsaiGm 44746 3 884 /cxml-data/ap480/sortedAmerican.dat 0.8 256
#./mBonsaiGm 1125376 3 7117 /cxml-data/ap480/sortedPumsb.dat 0.8 256
#./mBonsaiGm 4242318 3 442 /cxml-data/ap480/sortedAccidents.dat 0.8 256
#./mBonsaiGm 653218 3 16471 /cxml-data/ap480/sortedRetail.dat 0.8 256
#./mBonsaiGm 63985704 3 5577 /cxml-data/ap480/sortedWebdocs8.dat 0.8 256
#./mBonsaiGm 231232676 3 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8 256

#./mBonsaiGm 130437 3 5 /cxml-data/ap480/splitChess.txt 0.8 256
#./mBonsaiGm 6702990 3 5 /cxml-data/ap480/splitPumsb.txt 0.8 256
#./mBonsaiGm 17183926 3 5 /cxml-data/ap480/splitAccidents.txt 0.8 256
#./mBonsaiGm 333444484 3 5 /cxml-data/ap480/splitWebdocs8.txt 0.8 256
#./mBonsaiGm 1448707215 3 5 /cxml-data/ap480/splitWebdocs.txt 0.8 256

#./mBonsaiGm 38610 3 75 /cxml-data/ap480/sortedChess.dat 0.8 128
#./mBonsaiGm 359292 3 129 /cxml-data/ap480/sortedConnect.dat 0.8 128
#./mBonsaiGm 27349 3 119 /cxml-data/ap480/sortedMushroom.dat 0.8 128
#./mBonsaiGm 44746 3 884 /cxml-data/ap480/sortedAmerican.dat 0.8 128
#./mBonsaiGm 1125376 3 7117 /cxml-data/ap480/sortedPumsb.dat 0.8 128
#./mBonsaiGm 4242318 3 442 /cxml-data/ap480/sortedAccidents.dat 0.8 128
#./mBonsaiGm 653218 3 16471 /cxml-data/ap480/sortedRetail.dat 0.8 128
#./mBonsaiGm 63985704 3 5577 /cxml-data/ap480/sortedWebdocs8.dat 0.8 128 > check
#./mBonsaiGm 231232676 3 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8 128

#./mBonsaiGm 38610 3 75 /cxml-data/ap480/sortedChess.dat 0.8 256
#./mBonsaiGm 38610 3 75 /cxml-data/ap480/sortedChess.dat 0.8 512
#./mBonsaiGm 38610 3 75 /cxml-data/ap480/sortedChess.dat 0.8 1024

#echo connect


#./mBonsaiGm 359292 3 129 /cxml-data/ap480/sortedConnect.dat 0.8 256
#./mBonsaiGm 359292 3 129 /cxml-data/ap480/sortedConnect.dat 0.8 512
#./mBonsaiGm 359292 3 129 /cxml-data/ap480/sortedConnect.dat 0.8 1024

#echo mushroom


#./mBonsaiGm 27349 3 119 /cxml-data/ap480/sortedMushroom.dat 0.8 256
#./mBonsaiGm 27349 3 119 /cxml-data/ap480/sortedMushroom.dat 0.8 512
#./mBonsaiGm 27349 3 119 /cxml-data/ap480/sortedMushroom.dat 0.8 1024

#echo american


#./mBonsaiGm 44746 3 744 /cxml-data/ap480/sortedAmerican.dat 0.8 256
#./mBonsaiGm 44746 3 744 /cxml-data/ap480/sortedAmerican.dat 0.8 512
#./mBonsaiGm 44746 3 744 /cxml-data/ap480/sortedAmerican.dat 0.8 1024

#echo accidents


#./mBonsaiGm 4242318 3 290 /cxml-data/ap480/sortedAccidents.dat 0.8 256
#./mBonsaiGm 4242318 3 290 /cxml-data/ap480/sortedAccidents.dat 0.8 512
#./mBonsaiGm 4242318 3 290 /cxml-data/ap480/sortedAccidents.dat 0.8 1024

#echo pumsb


#./mBonsaiGm 1125376 3 1734 /cxml-data/ap480/sortedPumsb.dat 0.8 256
#./mBonsaiGm 1125376 3 1734 /cxml-data/ap480/sortedPumsb.dat 0.8 512
#./mBonsaiGm 1125376 3 1734 /cxml-data/ap480/sortedPumsb.dat 0.8 1024

#echo retail


#./mBonsaiGm 653218 3 8919 /cxml-data/ap480/sortedRetail.dat 0.8 256
#./mBonsaiGm 653218 3 8919 /cxml-data/ap480/sortedRetail.dat 0.8 512
#./mBonsaiGm 653218 3 8919 /cxml-data/ap480/sortedRetail.dat 0.8 1024

#echo webdocs


#./mBonsaiGm 38610 3 364 /cxml-data/ap480/sortedWebdocs8.dat 0.8 256
#./mBonsaiGm 38610 3 364 /cxml-data/ap480/sortedWebdocs8.dat 0.8 512
#./mBonsaiGm 38610 3 364 /cxml-data/ap480/sortedWebdocs8.dat 0.8 1024



