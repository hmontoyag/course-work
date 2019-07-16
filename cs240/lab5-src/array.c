
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
  if(n<=0||array==NULL){
     return 0;
  } else {
    int i;
    double max = *array;
    for ( i = 0; i!=n;i++){
      double a=*(array+i);
      if(max<a){
        max = a;
      }
    }
    return max;
  }
 // return 0;
}

// Return minimum element of array
double minArray(int n, double * array) {

  if(n<=0||array==NULL){ return 0;}
  int i;
  double min=*array;
  for(i=0;i!=n;i++){
    double a=*(array+i);
    if(min>a){
      min =a;
    }
  }
  return min;
  
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
  if(n<=0||array==NULL){return-1;}
  int isF = 1;
  int i;
  int index =-1;
  double a = *array;
  for(i=0;i!=n;i++){
    a=*(array+i);
    if(isF){
      if(a<=max&&a>=min){
        index = i;
	isF=0;
      }
    }
  }
  return index;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
  int i;
  int j;
  int tmp;
  for(i=0;i<n;i++){
    for(j=i+1;j<n;j++){
      if(*(array+i)>*(array+j)){
        tmp = *(array+i);
	*(array+i)=*(array+j);
	*(array+j)=tmp;
      }
     }
   }

return 1;
}

// Print array
void printArray(int n, double * array) {
  if(n<=0||array==NULL){}
  int i;
  double a=*(array);
  for(i=0;i!=n;i++){
     a=*(array+i);
     printf("%d:%f\n",i,a);
  }

}

