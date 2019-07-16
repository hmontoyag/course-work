
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
  FILE * fd  = fopen(fileName, "r");
  if (fd == NULL){
    printf("Could not open file %s\n", fileName);
    exit(1);
  }
  char * w;
  int wc;
  double f, s, r;
  while((w = nextword(fd)) != NULL){
      wc++;
      if((!(strcmp(w,"+"))) || (!(strcmp(w,"-")))||(!(strcmp(w,"/")))||(!(strcmp(w,"*")))||(!(strcmp(w,"pow")))) {
      if(stack_top() < 2) {
         printf("Stack underflow\n");
	 exit(1);
      } else {
         //
	 if(!(strcmp(w,"+"))){
	    f = stack_pop();
	    s = stack_pop();
	    r = f + s;
	    stack_push(r);

	 } else if(!(strcmp(w,"-"))){
	    f = stack_pop();
	    s = stack_pop();
	    r = s - f;
	    stack_push(r);

	 } else if(!(strcmp(w,"*"))){
	    f = stack_pop();
	    s = stack_pop();
	    r = f * s;
	    stack_push(r);

	 } else if(!(strcmp(w,"/"))){
	    f = stack_pop();
	    s = stack_pop();
	    r = s/f;
	    stack_push(r);

	 } else { //pow
	    f = stack_pop();
	    s = stack_pop();
	    r = pow(s,f);
	    stack_push(r);

	 }
       } // end of two num operations
     }
     else  if ((!(strcmp(w,"sin")))||(!(strcmp(w,"cos")))||(!(strcmp(w,"exp")))||(!(strcmp(w,"log")))){
       if (stack_top() < 1) {
          printf("Stack underflow");
	  exit(1);
       } else {
         //
	 if(!(strcmp(w,"sin"))){
	    f=stack_pop();
	    r = sin(f);
	    stack_push(r);

	  } else if(!(strcmp(w,"cos"))){
	    f = stack_pop();
	    r = cos(f);
	    stack_push(r);

	  }else if (!(strcmp(w,"log"))){
	    f = stack_pop();
	    r = log(f);
	    stack_push(r); 

	  } else { //exp
	    f = stack_pop();
	    r = exp(f);
	    stack_push(r);

	  }
	}
     } // end of one num operations
     else if(!(strcmp(w, "x"))){
        stack_push(x);
     } else {
        double a = atof(w);
	stack_push(a);
      } 
     }
     fclose(fd);
     if (stack_top() > 1) {
       printf("Elements remain in the stack\n");
       exit(1);
     } else {
     double ret = r;
     stack_clear();
       return ret;
     }
     
}


	    
