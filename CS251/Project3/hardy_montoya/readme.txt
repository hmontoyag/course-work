Hardy Montoya
CS 251

to compile a file:  javac -cp .:stdlib.jar:algs4.jar *filename*.java

to run: java -cp .:stdlib.jar:algs4.jar *filename*

*************************

Both classes average acceptable times.  Query goes high if output is printed to terminal, but for Query3, time when outputed to a file is just under 3 seconds usually.

Query doesn't use a tree.  It starts with the same organization system used for Filter, finds the first X greater than a, and compares the records below it (greater x's) for greater y's.

They both output a message if n is below 0, instead of not doing anything.

All tests made worked as expected at least, I think I did cover most cases.
