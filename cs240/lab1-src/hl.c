#include <stdio.h>
//

int
main(int argc, char **argv) {
  printf("Welcome to the High Low game...\n");

  // Write your implementation here...
  int low=1;
  int high=100;
  int  mid= (low+high)/2;
char selec;
do{
  printf("Think of a number between 1 and 100 and press <enter>");
  getchar();
  //
int p=1;
  while(!(high<low)){
p=1;
	while (p=1){
	printf("Is it higher than %d? (y/n)\n", mid);
	char ans;
	ans=getchar();
getchar();
	//
	if (ans=='y'){
	  low=mid+1;
	  mid=(low+high)/2;
p=0;
	} if (ans=='n') {
	  high = mid-1;
	  mid = (low+high)/2;
p=0;
	}else{ 
	 p=1; }
  }
  printf("\n");
  printf(">>>>>> The number is %d\n", low);
  printf("\n");
  printf("Do you want to continue playing (y/n)?");
  scanf("%c",&selec);
  getchar();
  high=100;
  low=1;
  mid=(low+high)/2;
//
}while (selec=='y');
printf("Thanks for playing!!!\n");

}

