#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	// Add your code here
	void * temp  = malloc(elementSize);
	int i, j=0;
        int did = 0;

	do{
        did = 0;
//	j++;
	for(i=0;i<n-1;i++){

	  for(j=0;j<n-i-1;j++){
	    void *e1 = (void*)((char*)array+j*elementSize);
	    void *e2 = (void*)((char*)array+(j+1)*elementSize);

	    if(ascending==0){
	      if(compFunc(e1,e2)<0){
	        did = 1;
	        memcpy(temp, e1, elementSize);
		memcpy(e1,e2,elementSize);
		memcpy(e2,temp,elementSize);
	       }
	    } 
	    if(ascending!=0){
	      if(compFunc(e1,e2)>0){
	         did = 1;
	         memcpy(temp,e1,elementSize);
		 memcpy(e1,e2,elementSize);
		 memcpy(e2,temp,elementSize);
	      }
	    }
	  }
	 }
       
	} while(did==0);
	 free(temp);
	    
	   
}

