mame-Bonsai
=========
Description
-----------
mame-Bonsai or m-Bonsai is a compact representation of tries using hashtables.

Making use of any mame-Bonsai or Bonsai implementation for research or commercial purposes, the reference will be:

A. Poyias and R. Raman. [Improved Practical Compact Tynamic Tries.](http://dblp.uni-trier.de/pers/hd/p/Poyias:Andreas) Proc. SPIRE 2015, pp. 324-336.

Paper .pdf
-----------
See the .pdf file for more details.

Implementations:
-----------
1. mame-Bonsai(recursive),proposed by A. Poyias and R. Raman.
2. mame-Bonsai(gamma), proposed by A. Poyias and R. Raman.
3. Bonsai, proposed by J. Darragh and J. Cleary.

m-Bonsai approaches:
1. m-Bonsai(recursive):
    Fast and compact approach.
2. m-Bonsai (gamma):
    Even more compact approach but slower than m-Bonsai(recursive).

ADT:
-----------
1. create(): Create a new empty tree.
2. getRoot(): return the root of the current tree.
3. getChild (v, c): return child node of node v with symbol c, if any (and return −1 if no such child exists).
4. getParent(v): return the parent of node v.
5. addChild (v, c): add a new child of v with symbol c and return the newly created node.
6. delLeaf (v, c): delete the child of v with symbol c, provided that the child indicated is a leaf (if the user asks to delete a child that is not a leaf, the subsequent operations may not execute correctly).

Installation
-----------

To be able to compile the m-Bonsai libraries.

1. Install sdsl-lite.
   Follow the installation guide here:
   https://github.com/simongog/sdsl-lite
3. run .sh file


Datasets
-----------
Given two datasets in the format of transaction database where each line is a sequence of characters.
1. Frequent Itemset Mining (FIM) dataset
transSortedAccidents.dat  dataset is used for FIM applications taken from FIMI repository. http://fimi.ua.ac.be/data/
2. FASTQ format dataset
FASTQ format is a text-based format for storing both a biological sequence (usually nucleotide sequence) and its corresponding quality scores. Both the sequence letter and quality score are each encoded with a single ASCII character for brevity.
We transformed each chararacter in the dataset from {A,G,C,T,N} to {0,1,2,3,4}.


