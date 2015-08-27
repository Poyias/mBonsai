g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_recursive/subLayer.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  -DSLEN2=5 -DSAT=7
echo comp subLayer 

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../Hash/mBonsaiHash.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../DArray/mBonsai_recursive/DArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DDARRAYSIZE=3
echo comp DArray

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=15 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo comp mBonsai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o mBonsaiHash.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=15 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

#./mBonsai 35004 300 ../../../../Desktop/sortedMushroom.dat 0.8 searchFile 
#./mBonsai 38610 300 ../../../../Desktop/sortedChess.dat 0.8 searchFile 
#./mBonsai 4242318 442 ../../../../Desktop/sortedAccidents.dat 0.8 756665 #9,2,3,7
./mBonsai 653217 16471 ../../../../Desktop/sortedRetail.dat 0.8 searchFile
#./mBonsai 63985704 5577 ../../../../Desktop/sortedWebdocs8.dat 0.8 11454600 

################
#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
#echo comp mBonsai

#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o hashFunction.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
#echo ready to run

#./mBonsai 4242318 3 442 /cxml-data/ap480/sortedAccidents.dat 0.8 756665 #9,2,3,7

##########
#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
#echo comp mBonsai

#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o hashFunction.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
#echo ready to run

#./mBonsai 63985704 3 5577 /cxml-data/ap480/sortedWebdocs8.dat 0.8 11454600 #13,2

###############
#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=23 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
#echo comp mBonsai

#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o hashFunction.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=23 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
#echo ready to run

#./mBonsai 231232676 3 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8 39584007 #2

 
#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib mBonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
#echo comp mBonsai

#g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib subLayer.o DArray.o hashFunction.o data.o mBonsai.o main.cpp -o mBonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
#echo ready to run

#./mBonsai 6702990 3 5 /cxml-data/ap480/splitPumsb.txt 0.8 1038187 #13
#./mBonsai 17183926 3 5 /cxml-data/ap480/splitAccidents.txt 0.8 2708826 #9
#./mBonsai 333444484 3 5 /cxml-data/ap480/splitWebdocs8.txt 0.8 51995392 #13
#./mBonsai 1448707216 3 5 /cxml-data/ap480/splitWebdocs.txt 0.8 226092668 #23
