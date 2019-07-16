#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	// Add your code here
	int i;
	int bin[32];
        for(i=0;i!=32;i++){
	 bin[i] = (bitmap >> (32-i)-1) & 1;
	}
	int a = 0;
	for(a = 0; a<32; a++){
	  printf("%i",bin[a]);
	}
	printf("\n");
	printf("10987654321098765432109876543210\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	// Add your code here
	unsigned y;
	if (bitValue == 1){
	   unsigned mask = (1 << i);
	   *bitmap = (*bitmap|mask);
	}
	if (bitValue ==0) {
	   unsigned mask = ~(1<<i);
	   *bitmap = (*bitmap&mask);
        }
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
	unsigned x = (bitmap >> i) & 1;
	return x;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
	unsigned x = bitmap;
	unsigned int count = 0;
        if(bitValue ==1){
	   while(x){
             count = count + (x&1);
	     x = x >> 1;
	   }
	 }
	 if (bitValue == 0){
	   while(x){
	     if((x&1)==0){
	      count++;
	     }
	     x = x>>1;
	    }
            if(count>0){
	      count++;
	    }
	 }
	 return count;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
	//
	//
	unsigned x = bitmap;
	unsigned y = x;
	int count = 0;
	while(x!=0){
          x = (x & (x << 1));
	  count++;
	}

        int i, c=0;
	for (i = 0; i!=count-1; i++){
	  y = (y & (y >> 1));
        }
	
        while(y!=1){
	  y = y>>1;
	  c++;
	}
	
	*position =c ;
	return count;
}


