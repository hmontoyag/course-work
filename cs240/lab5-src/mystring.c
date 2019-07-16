
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
//     
// 
   int i=0;
   while(*s!='\0'){
     i++;
     *s++;
   }
   return i;
}

char * mystrcpy(char * dest, char * src) {
       int i = 0;
       while(*src){
       *dest = *src;
 	dest++;
	src++;
	i++;
       }
       if(src == NULL) { dest == NULL;}
       *dest = '\0';
        return src - i;
}

char * mystrcat(char * dest, char * src) {
	int i=0;
	while(*dest){ dest++;
	 i++;}
//	while(*dest++=*src++){i++;}

	return dest-i-1;
}

int mystrcmp(char * s1, char * s2) {
	//
        int le1 = 0;
	int le2 = 0;
	while(*s1){
	  le1++;
	  s1++;
	}
	while(*s2){
	  le2++;
	  s2++;
	}
	if(le1>le2) {
	  return 1;
	} else if (le2 > le1){
	  return -1;
	} else {
	return 0;
      }
}

char * mystrstr(char * hay, char * needle) {
	if(*needle=='\0') { return hay;}
	if(*hay=='\0'){return NULL;}

	char * c = hay;
	char * k;
	while(*c!='\0') {
	  
	  k = c;
	  char * t = needle;
	  while(*k!='\0' && *t!='\0' && *k ==*t) {
	    k++;
	    t++;
	  }
	  if(*t=='\0'){
	    return c;
	  }
	  c++;
        }
	return NULL;
}

char * mystrdup(char * s) {
     
   int i=0;
   int j = mystrlen(s);
   //  s = s-i-1;
      char * dup = (char*)malloc((j)*sizeof(char));
      while(*s){
        *dup = *s;
	dup++;
	s++;
        i++;
      }
     // *dup='\0';

   
    
     return dup-i;
}

char * mymemcpy(char * dest, char * src, int n)
{
        int i;
        for(i=0; i<n; i++) { 
	   *dest = *src;
	   dest++;
	   src++;
	 }
	 return dest;
//	char * s = mystrcpy(dest,src);
//	return s;
}

