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
	//kprintf("R\n");
	mask = disable();
	prptr = &proctab[currpid];
	
	
	if (prptr->prhasmsg == FALSE) {
	//kprintf("ERR\n");
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	
	
	msg = prptr->prmsg;		/* Retrieve message		*/
	if(prptr->rcpblkflag==0 && isempty(prptr->sendqueue)){
		prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	}
	if(nonempty(prptr->sendqueue)&&prptr->rcpblkflag!=0){

		pid32 dqpr = dequeue(prptr->sendqueue);
		struct procent *dqprptr = &proctab[dqpr];
		//dqprptr proc that has been dequeued that was trying to send a mess
		//kprintf("HERE with dqprptr = %d, and msg = %d\n", dqpr,dqprptr->sendblkmsg);

		prptr->prmsg = dqprptr->sendblkmsg;
		
		dqprptr->sendblkflag = 0;

		if(isempty(prptr->sendqueue)){

			prptr->rcpblkflag = 0;
		}
		ready(dqpr);

	
	
	}
	
	restore(mask);
	return msg;
}
