g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp mBonsai.cpp main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64

./mBonsai 3095561 5 ../datasets/SRR034939.dat 0.8 ../datasets/SRR034939.dat #0.72
#./mBonsai 35004 300 /cxml-data/ap480/sortedMushroom.dat 0.8 /cxml-data/ap480/sortedMushroom.dat
./mBonsai 35004 300 /cxml-data/ap480/Datasets/tranSortedMushroom.dat 0.8 /cxml-data/ap480/Datasets/tranSortedMushroom.dat
#./mBonsai 38610 300 /cxml-data/ap480/sortedChess.dat 0.8 /cxml-data/ap480/sortedChess.dat 
 ./mBonsai 38610 300 /cxml-data/ap480/Datasets/tranSortedChess.dat 0.8 /cxml-data/ap480/Datasets/tranSortedChess.dat

./mBonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 ../datasets/sortedAccidents.dat #0.66
#./mBonsai 653217 16471 /cxml-data/ap480/sortedRetail.dat 0.8 /cxml-data/ap480/sortedRetail.dat
#./mBonsai 653217 8919 /cxml-data/ap480/sortedRetail.dat 0.8 /cxml-data/ap480/sortedRetail.dat

 ./mBonsai 63985704 364 /cxml-data/ap480/Datasets/tranSortedWebdocs8.dat 0.8 /cxml-data/ap480/Datasets/tranSortedWebdocs8.dat
g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp mBonsai.cpp main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -Dretail

./mBonsai 653217 8919 /cxml-data/ap480/Datasets/tranSortedRetail.dat 0.8 /cxml-data/ap480/Datasets/tranSortedRetail.dat

#./mBonsai 63985704 364 /cxml-data/ap480/sortedWebdocs8.dat 0.8 /cxml-data/ap480/sortedWebdocs8.dat 
g++ -O3 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I ~/include -L ~/lib cht.cpp ../Hash/mBonsaiHash.cpp ../readio/data.cpp mBonsai.cpp main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -Dwebdocs
./mBonsai 231232676 59717 /cxml-data/ap480/Datasets/tranSortedWebdocs.dat 0.8 /cxml-data/ap480/Datasets/tranSortedWebdocs.dat

#./mBonsai 231232676 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8 /cxml-data/ap480/sortedWebdocs.dat 
