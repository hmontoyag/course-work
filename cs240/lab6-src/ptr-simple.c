
#include <stdio.h>

int a; 
int *p; 
int b[20];

int
main() {
  a=5;
  p=&a;  

  printf("a=5\n");
  printf("p=&a\n");
  printf("a=%d\n",a);
  printf("&a=%ld\n",(long)&a);      //adress of a
  printf("p=%ld\n",(long)p);	    //p is the adress of a
  printf("&p=%ld\n",(long)&p);      //adress of p
  printf("*p=%d\n",*p);             //value p points to

  printf("\n");

  p=&b[0];                           
  printf("&b[0]=%ld\n",(long)&b[0]); //adress of b[0]
  printf("p=%ld\n\n",(long)p);       // value of p, now adress of b[0] since p=&b[0];

  p++;   //p goes up by 4 since its an int
  printf("p++\n");
  printf("&b[1]=%ld\n",(long)&b[1]); //adress of b[1], 4 more than b[0] since b is array of ints
  printf("p=%ld\n\n",(long) p); // ^^

  p++;
  printf("p++\n");  // 4 more
  printf("&b[2]=%ld\n",(long) &b[2]); //same
  printf("p=%ld\n\n",(long)p); // ^^ same
  
  
}


