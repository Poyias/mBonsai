g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  -DSLEN2=5 -DSAT=7
echo comp subLayer 


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib hashFunction.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib DArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DDARRAYSIZE=3 
echo comp DArray 



g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o schBench.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

#./bonzai 1125376 3 7117 /cxml-data/ap480/sortedPumsb.dat 0.8 /cxml-data/ap480/Datasets/searchDataset/Pumsb.sch #13,2,3,7

################

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o schBench.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=9 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

#./bonzai 4242318 3 442 /cxml-data/ap480/sortedAccidents.dat 0.8 /cxml-data/ap480/Datasets/searchDataset/Accidents.sch #9,2,3,7

#########
g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o schBench.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

#./bonzai 63985704 3 5577 /cxml-data/ap480/sortedWebdocs8.dat 0.8 /cxml-data/ap480/Datasets/searchDataset/Webdocs8.sch #13,2,3,7

###############
g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=23 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o schBench.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=23 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

#./bonzai 231232676 3 5267657 /cxml-data/ap480/sortedWebdocs.dat 0.8 /cxml-data/ap480/Datasets/searchDataset/Webdocs.sch #23,2,3,7

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/var/autofs/home/home/ap480/include -L/var/autofs/home/home/ap480/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o schBench.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run


#./bonzai 6702990 3 5 /cxml-data/ap480/splitPumsb.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/splitPumsb.sch #13
#./bonzai 17183926 3 5 /cxml-data/ap480/splitAccidents.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/splitAccidents.sch #9
#./bonzai 333444484 3 5 /cxml-data/ap480/splitWebdocs8.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/splitWebdocs8.sch #13
#./bonzai 1448707216 3 5 /cxml-data/ap480/splitWebdocs.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/splitWebdocs.sch #23

#./bonzai 3095560  3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034939.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/SRR034939.sch #23
#./bonzai 21005059 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034944.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/SRR034944.sch #23
./bonzai 1556235309 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034940_1.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/SRR034940-1.sch #23
./bonzai 1728553810 3 5 /cxml-data/ap480/Datasets/dnaStrings/SRR034945_1.txt 0.8 /cxml-data/ap480/Datasets/searchDataset/SRR034945-1.sch #23


