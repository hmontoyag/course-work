
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int i=0;
	while(s[i]!='\0'){
	    i++; }

	return i;
}

char * mystrcpy(char * dest, char * src) {
	int i=0;
	while(src[i]!='\0'){i++;}
	int j;
	for(j = 0; j<i;j++){
	  dest[j]=src[j];
	  }
	  dest[j]='\0';
	return  dest;
}

char * mystrcat(char * dest, char * src) {
	int i=0;
	while(dest[i]!='\0'){i++;}
	int j;
	for(j = 0; src[j]!='\0';j++){
	   dest[i+j]=src[j];
	}
	dest[i+j]='\0';

	return dest;
}

int mystrcmp(char * s1, char * s2) {
	int le1=0;
	int le2=0;
	while(s1[le1]!='\0'){le1++;}
	while(s2[le2]!='\0'){le2++;}
	if (le1 > le2){
	  return 1;
	} else if (le2 > le1) {
	  return -1; 
	} else {
	  return 0;}

}

char * mystrstr(char * hay, char * needle) {
  int c = 0;
  int i = 0;
  int j = 0;
  while(hay[c]!='\0'){
     if(hay[c]==needle[0]){
       i = 1;
       while (needle[i]==hay[c+i] && needle[i]!='\0'){
         i++;
	 if (i == mystrlen(needle)){
	    return hay + c;
	 }
       }
     }
     c++;
  }
  return NULL;
          


	
}


char * mystrdup(char * s) {
	int len = mystrlen(s);
	char* dup = (char*) malloc((len)*sizeof(char));
	int i;
	for (i = 0; i < len; i++) {
	   dup[i] = s[i];
	}
	return dup;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int len = mystrlen(src);
	int i;
	for (i=0; i < len && src != '\0'; i++) {
	   dest[i] = src[i];
	}
	int dl = mystrlen(dest);
	dest[dl] = '\0';
	return dest;
}

