
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filedump(char * p , int len) {

    FILE * fin = fopen(p,"r" );
    fseek(fin,0L,SEEK_END);
    int size = ftell(fin);
    fseek(fin, 0L, SEEK_SET);
    char * pe = (char*) malloc(sizeof(size));
    /**/  fread(pe,sizeof(char),len,fin);
    
    int i;
    int d=0;
    int f=0;
    int count = 1;
    long a = 0;
    if (len > size) { len = size;}
   // printf("a");
    printf("0x%016lX: ", (unsigned long) a);
    for(i=0; i <len; i++) {
      int c = pe[i]&0xFF;
      printf("%02X ",c);
      if(count==16||i+1==len){
        if(count != 16){
	  for(f = count; f < 16; f++) { printf("   ");}
	}  
         printf(" ");
	 for(d = i - count+1; d< i+1; d++){
	   int cd = pe[d]&0xFF;
	   printf("%c",(cd>=32&&cd<127)?cd:'.');
	 }
	 printf("\n");
	 if(i+1!=len){
	   printf("0x%016lX: ",(unsigned long) a+(i+1));
	 }
	 count =0;
	 f = i;
       }
       count++;
     }
     
}

int
main(int argc, char **argv) {
  if (argc < 1) { printf("Usage: myfiledump file [maxbytes]\n");}
  char * fileName = argv[1];
  FILE * fd = fopen(fileName,"r");
  if(fd == NULL) { 
    printf("Error opening file \"%s\"\n",fileName);
    exit(1);
  }
  fseek(fd,0L,SEEK_END);
  int size = ftell(fd);
  fseek(fd,0L,SEEK_SET);
  fclose(fd);
  if(argc < 3) {
    filedump(fileName, size);
  } else {
    int len = atoi(argv[2]);
    filedump(fileName,len);
    }
}



