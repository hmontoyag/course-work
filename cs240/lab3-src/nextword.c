
#include <stdio.h>
#include <stdlib.h>

// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c; 
        wordLength =0;
	
	while((c=fgetc(fd))!=-1) {

	  if((c>='A'&&c<='Z')||(c>='a'&&c<='z')){
	    word[wordLength] = c;
	    wordLength++;
	  } else {
	    word[wordLength] ='\0';
	    if(wordLength > 0){
	    return word;
	    }
	    wordLength = 0;
	    word[wordLength]='\0';
	  }
	  
	 }
	 if (wordLength > 0) {
	    return word;
	 } else {
	 return NULL;
}
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	return NULL;
}

