/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		/*if (ptold->prprio > firstkey(readylist)) {   //"even if current pro has higher prio comp to head of readylist"
			return;
		}*/
		
		if(isempty(readylist)||(firstid(readylist)==0 && lastid(readylist)==0)){
			preempt = QUANTUM + ptold->prprio;			
			return;
		}
		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		//insert(currpid, readylist, ptold->prprio);
		enqueue(currpid, readylist);
	}


	
	if(isempty(readylist)||(firstid(readylist)==0 && lastid(readylist)==0)){
		currpid = 0;
		ptnew = &proctab[0];
	} else {
		currpid = dequeue(readylist);
		ptnew = &proctab[currpid];
	}	
		ptnew->prstate = PR_CURR;
		preempt = QUANTUM + ptnew->prprio;
		ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
		
	

	/* Force context switch to highest priority ready process */

	/*currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM + ptnew->prprio;	*/	/* Reset time slice for process	*/
	/*ctxsw(&ptold->prstkptr, &ptnew->prstkptr);*/

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
