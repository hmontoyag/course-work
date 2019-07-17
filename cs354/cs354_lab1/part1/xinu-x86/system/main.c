/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int convoysem;

prch(c)
char c;
{
  int i;
	int j = 0;
  while(j<100) {
    for (i=0; i< 2; i++);

    kprintf("%c", c);
	j++;
	if(j==100){
	kprintf("\nlul\n");
	}
  }
}

main ()
{
   kprintf("\n\nHello world, Xinu lives\n\n");

   pid32 prA, prB, prC, prD;
   prA = create(prch,10,5,"proc A",1,'A');
   prB = create(prch,10,4,"proc B",1,'B');
   prC = create(prch,10,6,"proc C",1,'C');
   
   sleepms(3000);
   resume(prA);
   resume(prB);
kprintf("wadup");
   sleepms(10000);
   kprintf("WASAAAAP\n");
   //tends to have no runnable process here?.
   sleepms(5000);
   //at this point there;s briefly no runnable pr??
   prD = create(prch,10,3,"proc D",1,'D');
     resume(prC);
   resume(prD);
}
