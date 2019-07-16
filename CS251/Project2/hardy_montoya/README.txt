CS251 Project 2:   Hardy Montoya 
hmontoya
***Im using 1 late day***

to compile a file:  javac -cp .:stdlib.jar:algs4.jar file.java

to run: java -cp .:stdlib.jar:algs4.jar filename

stdlib.jar and algs4.jar are required

algs4.jar is required because Insertion Sort is used to do the insertion sort when the subarray is 8 or less.

Quick3wayBM and the visualizer both have values of p,q,hi,lo that meet the requirements set by the formula.  There was an undefined (as in, couldnt figure out exactly why it happened) situation
where i and j would mess up and the whole sorting would then mess up.  A quick fix utilizing only a if statement was applied that solves said problem, for every case tested, including all the ones provided and some of my own (with both
smaller and larger arrays).

So, after that fix, both classes perform as desired while meeting all conditions established and still in good time.


--

There's no implementation of the second part. I tried using some of the classes from algs4 to build it up but I simply started to late.
