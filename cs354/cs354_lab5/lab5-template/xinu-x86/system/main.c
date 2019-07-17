/*  main.c  - main */

#include <xinu.h>
/*	pid32 prA, prB;
process pra(did32 n){
	sleepms(1000);
	struct dentry *devptr;
	devptr = &devtab[n];
	pipwrite(devptr, "ABC", 3);
	sleepms(1000);
	pipwrite(devptr, "DEF", 3);
	sleepms(1000);
	//pipdisconnect(devptr->dvnum);
}
process prb(did32 n){
	sleepms(1000);
	struct dentry *devptr;
	devptr = &devtab[n];
	kill(prA);
	char buf[6];
	//pipread(devptr, buf, 3);
	//buf[3] = '\0';
//	kprintf("TEST1 = %s#\n", buf);
	sleepms(3000);
	//char buf2[3];
	pipread(devptr, buf, 3);
*/


/*	kprintf("TESTA = %c\n", pipgetc(devptr));
	kprintf("TESTB = %c\n", pipgetc(devptr));
	kprintf("TESTC = %c\n", pipgetc(devptr));
	sleepms(1000);
	kprintf("TESTD = %c\n", pipgetc(devptr));
	kprintf("TESTE = %c\n", pipgetc(devptr));
	kprintf("TESTF = %c\n", pipgetc(devptr));*/
	//sleepms(1000);
//}
process	main(void)
{

	/* Run the Xinu shell */
	recvclr();
	/*=======================================================================*/
	resume(create(shell, 8192, 50, "shell", 1, WCONSOLE));
	/*=======================================================================*/
	/*789*/
	/*did32 test;
	test = pipcreate();
	kprintf("main: %d\n", currpid);
	prA = create(pra, 2048, 10, "pra", 1, test);
	prB = create(prb, 2048, 10, "prb", 1, test);
	
	kprintf("prA = %d, prB = %d\n", prA, prB);
	pipconnect(test, prA, prB);
	
	sleepms(1000);
	resume(prA);
	sleepms(5000);
	resume(prB);
	sleepms(100000);*/

	/*789*/
	/* Wait for shell to exit and recreate it */
	/*=======================================================================*/
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, WCONSOLE));
	}
	/*=======================================================================*/
	return OK;
    
}
