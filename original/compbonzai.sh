g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../Hash/orighashFunc.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp origHash

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib ../readio/data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64
echo comp data

g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=18
echo comp Bonsai

g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=18
echo ready to run

./Bonsai 4242318 442 ../datasets/sortedAccidents.dat 0.8 .../datasets/sortedAccidents.dat  #756665 #9,3,5,7
#./Bonsai 38610 300 ../../../../Desktop/sortedChess.dat 0.8  
#./Bonsai 63985704 5577 ../../../../Desktop/sortedWebdocs8.dat 0.8
###########################

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib Bonsai.h Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=14

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=14

#./Bonsai 4242317 3 442 /cxml-data/ap480/sortedAccidents.dat 0.8
###########################

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib Bonsai.h Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=18

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=18

#./Bonsai 63985704 3 5577 /cxml-data/ap480/sortedWebdocs8.dat 0.8
###########################

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib Bonsai.h Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=28

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=28

#./Bonsai 231232676 3 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8

###########################

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib Bonsai.h Bonsai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=8

#g++  -O6 -Wall -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/home/eshime/include -L/home/eshime/lib orighashFunc.o data.o Bonsai.o main.cpp -o Bonsai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=8

#./Bonsai 6702990 3 5 /cxml-data/ap480/splitPumsb.txt 0.8
#./Bonsai 17183926 3 5 /cxml-data/ap480/splitAccidents.txt 0.8
#./Bonsai 333444484 3 5 /cxml-data/ap480/splitWebdocs8.txt 0.8
#./Bonsai 1448707215 3 5 /cxml-data/ap480/splitWebdocs.txt 0.8



