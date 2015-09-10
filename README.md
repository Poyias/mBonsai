#mame-Bonsai

##Description
m-Bonsai is a compact representation of tries using hashtables.
If you make use of any mame-Bonsai or Bonsai implementation for research or commercial purposes, the reference will be:

A. Poyias and R. Raman. [Improved Practical Compact Tynamic Tries.](http://dblp.uni-trier.de/pers/hd/p/Poyias:Andreas) Proc. SPIRE 2015, pp. 324-336.

###Implementations:
1. mame-Bonsai(recursive),proposed by A. Poyias and R. Raman.
2. mame-Bonsai(gamma), proposed by A. Poyias and R. Raman.
3. Bonsai, proposed by J. Darragh and J. Cleary.


###m-Bonsai approaches:
1. m-Bonsai(recursive):
    Fast and compact approach.
2. m-Bonsai (gamma):
    Even more compact approach but slower than m-Bonsai(recursive).

###Installation

To be able to compile the m-Bonsai libraries.

1. Install sdsl-lite.
   Follow the installation guide here:
   https://github.com/simongog/sdsl-lite
3. run .sh file


###dataset
It is a fastq format dataset where we selected the second line of each sequence.
We transformed each chararacter from {A,G,C,T,N} to {0,1,2,3,4}.


