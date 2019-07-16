
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    
    int i;
    int d =0;
    int f=0;
    int count = 1;
    fprintf(fd, "0x%016lX: ", (unsigned long) p); // Print address of the beginning of p. You need to print it every 16 bytes

    for (i=0; i < len; i++) {
        
        
        int c = p[i]&0xFF; // Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.

        // Print first byte as hexadecimal
        fprintf(fd, "%02X ", c);
        // Print first byte as character. nly print characters >= 32 that are the printable characters
       // fprintf(fd, "%c ", (c>=32&&c<127)?c:'.');
       if(count==16||i+1==len){
        if(count !=16){
	  for(f = count; f <16; f++) { fprintf(fd, "   ");}}
        fprintf(fd," ");
         for(d = i - count+1; d < i+1; d++){
	   int cd = p[d]&0xFF; 
	   fprintf(fd, "%c", (cd>=32&&cd<127)?cd:'.');
	 }
         fprintf(fd, "\n");
	 if(i+1!= len) {
	 fprintf(fd, "0x%016lX: ", (unsigned long) p+(i+1));
	 }
	 count = 0;
	 f =i;
       }
     count++;
   }
  // if(len % 15 != 0) {
     
}

