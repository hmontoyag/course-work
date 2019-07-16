
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	//
	//
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
//	        printf("EN=%d\n",i);
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
//			printf("BBB\n");
			
			return;
		}
         }
	
	// Word not found

	// Make sure that the array has space.
	// Expand the wordArray he
	WordInfo * new = NULL;
	int p = wtable->maxWords;
	if(wtable->maxWords == wtable->nWords){
//          printf("INCREMENTA\n");   
          wtable->maxWords= wtable->maxWords*2;

	  new = (WordInfo *) realloc(wtable->wordArray, wtable->maxWords *sizeof(WordInfo));
	 }
	 if(new!=NULL){
//	   printf("ACA\n");
	  wtable->wordArray = new;
	 }
         for(int i =p;i<wtable->maxWords;i++){
//	   printf("PARA=%d\n",i);
	   llist_init(&wtable->wordArray[i].positions);
	 }
	


	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_init(&wtable->wordArray[wtable->nWords].positions);
//	printf("CC\n");
        	
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;

//	printf("AAA\n");
//printf("NNNN = %d\n",wtable->nWords);
	return;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here
	int c;

	wordLength = 0;
	while((c=fgetc(fd))!=-1){
	   
	   if((c>='A'&&c<='Z')||(c>='a'&&c<='z')){
	     word[wordLength] = c;
	     if(wordLength == 0){wordPos=charCount;}
	     wordLength++;
	   } else {
	     word[wordLength] = '\0';
	     if(wordLength >0){
	       return word;
	     }
	     wordLength =0;

	     word[wordLength] ='\0';
	  }
	}
	if(wordLength > 0){
	  return word;
	} else {
	  return NULL;
        }
        return NULL;
}

// Conver string to lower case
void toLower(char *s) {
// Write your code here
	int i;
	for(i=0;s[i];i++){
	  if(s[i]>='A'&&s[i]<='Z'){
	    s[i] = s[i] +32;
	    }
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	// Write your code here
	FILE * fd = fopen(fileName,"r");
	if(fd==NULL) { return 0;}
        int pos = 0;
        char * word;
	int len;
	int index;
	int list = 0;
	while((word = nextword(fd))!= NULL){
	  len = strlen(word);
	  index = ftell(fd);
	  pos = index - (len+1);
          toLower(word);
	  wtable_add(wtable,word,pos);
	  if(verbose==1) {
	    printf("%d: word=%s, pos=%d\n",list,word,pos);
	    list++;
	  }
        }
	fclose(fd);
	return 0;

	   

}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
   int sort = 1;
   int i;
   int j;
   char * temp;
   LinkedList pt;

   do{
       sort =0;
       for(i=0;i<wtable->nWords-1;i++){
	  int r =  (strcmp(wtable->wordArray[i].word,wtable->wordArray[i+1].word));
	  if(r>0){
	    temp = wtable->wordArray[i].word;
	    wtable->wordArray[i].word = wtable->wordArray[i+1].word;
	    wtable->wordArray[i+1].word=temp;
	    pt = wtable->wordArray[i].positions;
	    wtable->wordArray[i].positions = wtable->wordArray[i+1].positions;
	    wtable->wordArray[i+1].positions = pt;
	    sort = 1;
	  }
        }
      } while(sort);
	     
   
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	// Write your code here
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n",word,fileName);
	int i;
	int h;
	for(i=0; i<wtable->nWords;i++){
	  if(strcmp(wtable->wordArray[i].word,word)==0){
	    h = i;
	  }
	}
        int num = llist_number_elements(&wtable->wordArray[h].positions);
	FILE * fd = fopen(fileName,"r");
	char seg[200];
	for(i=0;i<num;i++){
	  
	  int *value =(int*) malloc(sizeof(int));
	  llist_remove_first(&wtable->wordArray[h].positions,value);
	  printf("---------- pos=%d-----\n",*value);
	  fseek(fd,*value,SEEK_SET);
          char *pe = (char*)malloc(sizeof(char)*500);
          fread(pe,sizeof(char),200,fd);
	  printf("......");
          for(int j=0; j<200;j++){
	    seg[j]=pe[j];
	  }
          printf("%s", seg);
	  printf("......\n");
	  
        


	}
	  
     


}

