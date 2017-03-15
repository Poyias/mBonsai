g++  -O3 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib ../Hash/orighashFunc.cpp ../readio/data.cpp Bonsai.cpp main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64
echo ready to run

# ./Bonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat
# ./Bonsai 3095560 5    ../datasets/SRR034939.dat       0.8 ../datasets/SRR034939.dat 

./Bonsai 3095561 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat
./Bonsai 21005059 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034944.txt  0.8 /cxml-data/ap480/Datasets/dnaStrings/SRR034944.txt
./Bonsai 1556235309 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034940_1.txt  0.8 /cxml-data/ap480/Datasets/dnaStrings/SRR034940_1.txt
./Bonsai 1728553810 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034945_1.txt  0.8 /cxml-data/ap480/Datasets/dnaStrings/SRR034945_1.txt

./Bonsai 35004 119 /cxml-data/ap480/Datasets/tranSortedMushroom.dat 0.8 /cxml-data/ap480/Datasets/tranSortedMushroom.dat
 ./Bonsai 38610 75 /cxml-data/ap480/Datasets/tranSortedChess.dat 0.8 /cxml-data/ap480/Datasets/tranSortedChess.dat

./Bonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat

 ./Bonsai 63985704 364 /cxml-data/ap480/Datasets/tranSortedWebdocs8.dat 0.8 /cxml-data/ap480/Datasets/tranSortedWebdocs8.dat

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp Bonsai.cpp main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -Dretail

./Bonsai 653217 8919 /cxml-data/ap480/Datasets/tranSortedRetail.dat 0.8 /cxml-data/ap480/Datasets/tranSortedRetail.dat

g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp Bonsai.cpp main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -Dwebdocs
./Bonsai 231232676 59717 /cxml-data/ap480/Datasets/tranSortedWebdocs.dat 0.8 /cxml-data/ap480/Datasets/tranSortedWebdocs.dat
