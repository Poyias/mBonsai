#mame-Bonsai

##Description
m-Bonsai is a compact representation of tries using hashtables.

Making use of any mame-Bonsai or Bonsai implementation for research or commercial purposes, the reference will be:

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
Given two dtasets in the format of transaction database where each line
is a sequence of characters.
##sortedAccidents dataset is used for Frequent Itemset Mining (FIM) taken from FIMI repository. http://fimi.ua.ac.be/data/
##FASTQ format dataset
FASTQ format is a text-based format for storing both a biological sequence (usually nucleotide sequence) and its corresponding quality scores. Both the sequence letter and quality score are each encoded with a single ASCII character for brevity.
We transformed each chararacter in the dataset from {A,G,C,T,N} to {0,1,2,3,4}.


