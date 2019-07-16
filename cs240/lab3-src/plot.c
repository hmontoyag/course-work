
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
  double xx[MAXCOLS];

  clearPlot();

  // Evaluate function and store in vector yy
   int i = 0;
   int j = 0;
   
   for(i = 0; i < MAXCOLS-1; i++){
     double x = minX + (maxX - minX)*i/MAXCOLS;
     double y = rpn_eval(funcFile, x);
  //   stack_clear();
     xx[i] = x;
     yy[i] = y;
   }
  //Compute maximum and minimum y in vector yy
  double  maxY = yy[0];
  double  minY = yy[0];
  for(j = 0; j < MAXCOLS -1; j++){
     if (yy[j] < minY){
        minY = yy[j];
     }
  }
  for(j=0; j <MAXCOLS - 1; j++){
     if(yy[j] > maxX){
        maxX = yy[j];
     }
  }
    if ( minY < 0) {

      for (i = 0; i <MAXCOLS - 1; i++){
        plotXY(i,19,'_');
      }
    } else if (minY >= 0) {
      for (i =0; i < MAXCOLS -1; i++) {
	
        plotXY(i,39,'_');
	}
      }
   
  //Plot y axis
    for (i = 0; i < MAXROWS - 1; i++){
       plotXY(40,i,'|');
    }
  // Plot function. Use scaling.
   for (i = 0; i < MAXCOLS-1; i++){
      int x =i;
      int y = (int)((yy[i] - minY) * MAXROWS / (maxY-minY));
      plotXY(x,39-y,'*');
   }
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  // Get arguments
  //below 
   double xmin = atof(argv[2]);
   double xmax = atof(argv[3]);
   char * funcName = argv[1];
  //createPlot(funcName, xmin, xmax);
  createPlot(funcName, xmin, xmax);
}
