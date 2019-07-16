#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main(int argc, char ** argv){
   if (argc < 4) {
     printf("Usage:  convert <basefrom> <baseto> <number>\n");
     exit(1);
   }
   //
   //
   int basefrom = atoi(argv[1]);
   int baseto = atoi(argv[2]);
  // printf("%d\n",basefrom);
 //  printf("%d\n",baseto);
     int s =0;
     while(argv[3][s]!='\0') {s++;}
     
     char numb[s];
     int i;
     for (i = 0; i !=s; i++){
  //    if(argv[3][i] == 'F') {
    //    numb[i] == 'F';
     // }
     // if(argv[3][i]!='F'){
      numb[i] = argv[3][i]-'0';
      
     }
     //Step 1 del formato dado: number read
     
     printf("Number read in base %d: %s\n", basefrom, argv[3]);
     //^^^^^ s is number of digits, numb is the og number
     //Step 2: revisa que no haya ningun numero no permitido en numb
     for (i = 0; i!=s;i++) {
       if(numb[i]>=basefrom){
         printf("Wrong digit in number.\n");
	 exit(1);
       }
     }

     //Step 3: convierte num a un solo numero en base 10

     int decNum=0;
     int dig = s;
     int dmo = dig-1;
     for(i=0;i!=dig;i++){
        int nume = numb[i];
//	if (numb[i]=='F') { nume = 15;}
        decNum= decNum + nume*(pow(basefrom,dmo-i));
     }
     printf("Converted to base 10: %d\n",decNum);


     //ahora: de base 10 a base baseto
     //caca.

     int index = 0;
     int r;
     char finNum[32];
     while(decNum!=0){
       r = decNum%baseto;
       decNum = decNum/baseto;

       //adjust for diff cases
       if(r==10){ finNum[index] = 'A';}
       if(r==11){ finNum[index] = 'B';}
       if(r==12){ finNum[index] = 'C';}
       if(r==13){ finNum[index] = 'D';}
       if(r==14){ finNum[index] = 'E';}
       if(r==15){ finNum[index] = 'F';}
       if(r==16){ finNum[index] = 'G';}
       if(r==17){ finNum[index] = 'H';}
       if(r==18){ finNum[index] = 'I';}
       if(r==19){ finNum[index] = 'J';}
       if(r==20){ finNum[index] = 'K';}
       if(r==21){ finNum[index] = 'L';}
       if(r==22){ finNum[index] = 'M';}
       if(r==23){ finNum[index] = 'N';}
       if(r==24){ finNum[index] = 'O';}

       if(r < 10){
       finNum[index] = r +'0';}
       index++;
     }
     
     //inverse the array
     finNum[index] ='\0';
     char result[index];
     for (i = 0; i !=index; i++){
       result[i] = finNum[index-1-i];
     }


     
     printf("Converted to base %d: %s\n",baseto,result);
     

}


