/* sendblk.c - sendblk */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendblk(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
//kprintf("S\n");
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prstate == PR_FREE){
		restore(mask);
		return SYSERR;
	}
	//kprintf("prmsg = %d\n",msg);
		struct procent *curpr;
		curpr = &proctab[currpid];
		//kprintf("takingpr = %d, with msg = %d------------------------------------------\n", currpid, msg);
		
	if(prptr->prhasmsg || prptr->sendblkflag!=0){

		//change state, vars, and flag
		curpr->prstate = PR_SNDBLK;

		curpr->sendblkflag = 1;

		//kprintf("queuepr = %d, with msg = %d------------------------------------------\n", currpid, msg);
		enqueue(currpid, prptr->sendqueue);
		curpr->sendblkmsg = msg;
		curpr->sendblkrcp = pid;
		
		prptr->rcpblkflag = 1;
		prptr->prhasmsg = TRUE;

		resched();  //block until it can send it through?

	
	} else { //regular send---------------------------------------
		dequeue(prptr->sendqueue);
		//enqueue(currpid, prptr->sendqueue);
		//kprintf("queuingpr = %d, with msg = %d\n", currpid, msg);

		prptr->prmsg = msg;		/* Deliver message		*/
		prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/
		prptr->rcpblkflag = 1;

	}
	
	/*---*/
	
	/*---*/
	
	

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}

	restore(mask);		/* Restore interrupts */
	return OK;
}
