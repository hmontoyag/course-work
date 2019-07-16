CS 251
Hardy Montoya

Compile and Run:

javac -cp .:stdlib.jar:algs4.jar file.java
java -cp .:stdlib.jar:algs4.jar file

requires both stdlib and algs4 jars

In lab machines, Filter took roughly more than a second to process filter3.txt without including the printing (only the algorithms for filtering).

Query took roughly under 3 second to process query3.txt without printing.

ssh'ing, for the same inputs, Filter took roughly 4 seconds, and Query around 12.


For both I've tried to cover cases with bad input so that it prints a message instead of just crashing, either Invalid input. or Empty, might be printed(i might have missed another message from bad organization).

But assuming the input was correct (as expected), the output will also be the one expected.

Query doesn't use a tree really. It starts using the same system for organizing the X,Y's sorted by X that i use for Filter, and then just finds the first X greater than a, and goes down from there looking for Y's greater than b. 
