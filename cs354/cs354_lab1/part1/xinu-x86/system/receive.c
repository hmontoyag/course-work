/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE && prptr->rcpblkflag==0) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	if(prptr->rcpblkflag!=0){
	
		pid32 deqprid = dequeue(prptr->sendqueue);
		struct procent *deqpr = &proctab[deqprid];
		prptr->prmsg = deqpr->sendblkmsg;
		/**********/
		
		/*flags, check if queue is empty for rcpblkflag, */
		
		
		/**********/
	
	
	
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	restore(mask);
	return msg;
}
