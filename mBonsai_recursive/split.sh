g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib subLayer.cpp -c -lsdsl -ldivsufsort -ldivsufsort64  -DSLEN2=5 -DSAT=7
echo comp subLayer 


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib hashFunction.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp hashF


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime0/include -L/eshime/lib data.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 
echo comp data


g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib DArray.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DDARRAYSIZE=3 
echo comp DArray 



g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o main.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=13 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

 
g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib Bonzai.cpp -c -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7  
echo comp Bonzai

g++ -O6 -Wall -fpermissive -std=c++11 -w -Wall  -Wextra  -DNDEBUG  -g -ffast-math -funroll-loops -msse4.2 -I/eshime/include -L/eshime/lib subLayer.o DArray.o hashFunction.o data.o Bonzai.o main.cpp -o bonzai -lsdsl -ldivsufsort -ldivsufsort64 -DSLEN=3 -DDARRAYSIZE=3 -DSLEN2=5 -DSAT=7
echo ready to run

./bonzai 10000000  3 5 ../../../Desktop/SRR034944.txt 0.8 
