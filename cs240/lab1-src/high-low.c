#include <stdio.h>
//

int main(int argc, char **argv) {
     int high=100;
     int low=1;
     int mid = (low+high)/2;
     char selec;
     char selec2;
   
     printf("Welcome to the High Low game...\n");
     
     do{
         printf("Think of a number between 1 and 100 and press <enter>");
	 getchar();
	 while (!(high<low)){
		
	     printf("Is it higher than %d? (y/n)\n", mid);
	     scanf("%c",&selec);
	     getchar();
	     if (selec=='y'){
	         low = mid + 1;
		 mid = (low+high)/2;

             }  
	     if (selec=='n') {
	         high = mid -1;
		 mid = (low+high)/2;
		 
	    // } else {
	//	printf("Type y or n\n");
	     }if (selec!='n' && selec!='y'){
		printf("Type y or n\n"); }
	  	
	 }
	 printf("\n");
	 printf(">>>>>> The number is %d\n", low);
         printf("\n");
	 printf("Do you want to continue playing (y/n)?");
	 scanf("%c",&selec2);
	 getchar();
	 high=100;
	 low=1;
	 mid=50;

    } while (selec2=='y');
    printf("Thanks for playing!!!\n");



 	// Write your implementation here...
     return 0;
}

