#include <xinu.h>
struct pipeent pipetab[NPIPE];

/*---------------------------------------------------------------------

======================================================================*/
int32 pipeopen(
	)
{

 int32 i;
 int32 id;
 struct  pipeent *pipeptr;
 
 for(i=0; i < NPIPE; i++){
 	pipeptr = &pipetab[i];
 	if(pipeptr->inUse==0){
 		pipeptr->inUse=1;
 		id = i;
 		pipeptr->wRecord = PIPE_BS;
		pipeptr->rRecord = 0;
 		pipeptr->wsem = semcreate(PIPE_BS);
 		pipeptr->rsem = semcreate(0);

 		return id;
 	}
 }
 return SYSERR;

}

/*---------------------------------------------------------------------

======================================================================*/
syscall pipeclose(
		int32 pipe	/* id of pipe to be close if in use */
	)
{
	//disable interrupts and make ptr
	intmask mask;
	struct pipeent *pipeptr;
	
	mask = disable();
	//check that ID is valid at least
	if(pipe >= NPIPE || pipe <0){
		restore(mask);
		return SYSERR;
	}
	
	pipeptr = &pipetab[pipe];
	//check that pipe is in use
	if (pipeptr->inUse == 0){
		restore(mask);
		return SYSERR;
	}
	struct	procent *prptr;	
	prptr = &proctab[currpid];
	//++++++++++++++++++++++
	if(prptr->prstate == PR_WAIT){
	
		restore(mask);
		return SYSERR;
	}
		//++++++++++++++++++++++
	pipeptr->inUse = 0;
	memset(pipeptr->buffer, 0, PIPE_BS);
	pipeptr->writePos = 0;
	pipeptr->readPos = 0;
	pipeptr->freeSpace = PIPE_BS;
	pipeptr->wRecord = semcount(pipeptr->wsem);
	pipeptr->rRecord = semcount(pipeptr->rsem);
	semdelete(pipeptr->wsem);
	semdelete(pipeptr->rsem);

	
	
	return OK;
}
/*---------------------------------------------------------------------

======================================================================*/
syscall pipesend(
		int32 pipe, 	/*id of pipe*/
		int32 len,  	/*length of message*/
		char *c	/* char pointer to start of message*/
	)
{

//disable interrupts and make ptr
	intmask mask;
	struct pipeent *pipeptr;
	
	mask = disable();
//check that ID is valid at least
	if(pipe >= NPIPE || pipe <0){
		restore(mask);
		return SYSERR;
	}
	
	pipeptr = &pipetab[pipe];
//check that pipe is in use
	if (pipeptr->inUse != 1){
		restore(mask);
		return SYSERR;
	}
//iterating int
	
	int i = 0;
	//probs do a while until i=? or while i<= to len, and
	//there do the sends, and if there is no more space then 
	/* wait (assume we need to restore interrupts before?) 
	/remember to move the writePos in case resume or next write has to loop around
	*/
	int32 id = pipe;
	//kprintf("??\n");
	while(i < len){
		if(semtab[pipeptr->wsem].scount <=0){
			//kprintf("BOOOOO\n");
			wait(pipeptr->wsem);
		}
//	kprintf("%c\n",c[i]);
	//increment wsem/psem = available space PIPE_BS - (calls to wait)//
	//---------------------------------------------------------
		int32 missing = len - i;
		int32 ava = semtab[pipeptr->wsem].scount;
		int32 fit;
		int32 toSignal;
		if(ava - missing >=0){
			fit = missing;
		} else {
			fit = ava;
		}
		
			semtab[pipeptr->wsem].scount= semtab[pipeptr->wsem].scount- fit;
			//kprintf("a:%d, m:%d, f:%d s:%d\n", ava, missing,fit, semtab[pipeptr->wsem].scount);
		//wait(pipeptr->wsem);-------------------------
	//check that pipe wasnt closed while waiting	
	//++++++++++++++++++++++
		if(pipeptr->inUse!=1){
			restore(mask);
			return SYSERR;
		}
		//++++++++++++++++++++++
int32 j = 0;
		for(j = 0; j < fit; j++){
			
		//put char into buffer
			pipeptr->buffer[pipeptr->writePos] = c[i];
			//kprintf("%c\n",c[i]);
		//increment writing position for next time
			pipeptr->writePos++;

		//make sure writing pos loops around 'circular buffer'
			if(pipeptr->writePos >= PIPE_BS){
				pipeptr->writePos = 0;
			}
			i++;
		}
	//increment looping through *c for len
		
	//signal rsem/csem/ = elements in buffer
		signaln(pipeptr->rsem, fit);
		//kprintf("no\n");
		//signal(pipeptr->rsem);

	}
	//kprintf("wp = %d\n", pipeptr->writePos);
	//kprintf("rp = %d\n", pipeptr->readPos);
	restore(mask);
	return OK;	
}
/*---------------------------------------------------------------------

======================================================================*/
syscall piperecv(
		int32 pipe, 	/*id of pipe*/
		int32 len,  	/*length of message*/
		char *c	/* char pointer to start of message*/
	)
{

//disable interrupts and make ptr
	intmask mask;
	struct pipeent *pipeptr;
	
	mask = disable();
//check that ID is valid at least
	if(pipe >= NPIPE || pipe <0){
		restore(mask);
		return SYSERR;
	}
	
	pipeptr = &pipetab[pipe];

//check that pipe is in use
	if (pipeptr->inUse != 1){
		restore(mask);
		return SYSERR;
	}
	
//iterating int
	int i = 0;
	//kprintf("rwp = %d\n", pipeptr->writePos);
	//kprintf("rrp = %d\n", pipeptr->readPos);
	while(i < len){
	//calculate how much is going to go into the buffer in this iteration of the while loop
	//-------------------------------------------------------
	struct	procent *prptr;	
	prptr = &proctab[currpid];
	//++++++++++++++++++++++
	if(prptr->prstate == PR_WAIT){
	
		restore(mask);
		return SYSERR;
	}
	if(semtab[pipeptr->rsem].scount <= 0){		
			wait(pipeptr->rsem);

	}
		 
		int32 missing = len - i;
		int32 toRead = PIPE_BS - semtab[pipeptr->wsem].scount;
		int32 fit;
		if(toRead - missing >=0){
			fit = missing;
		} else {
			fit = toRead;
		}
		
		
		semtab[pipeptr->rsem].scount= semtab[pipeptr->rsem].scount- fit;
		
		//-------------------------------------------
		//check that pipe wasnt closed while waiting
		//++++++++++++++++++++++
		if(pipeptr->inUse!=1){
			restore(mask);
			return SYSERR;
		}
		
		//++++++++++++++++++++++
	int32 j;
	for(j = 0; j < fit; j++){
	//put char from buffer into *c
		c[i] = pipeptr->buffer[pipeptr->readPos];
		//kprintf("%c\n",pipeptr->buffer[pipeptr->readPos]);
	//increment read position for next time
		pipeptr->readPos++;

	//make sure read pos loops around 'circular buffer'
		if(pipeptr->readPos >=PIPE_BS){
			pipeptr->readPos = 0;
		}
		
		i++;
		}
		signaln(pipeptr->wsem, fit);
		//signal(pipeptr->wsem);
		//kprintf("SCRAA\n");

	}
    //kprintf("erwp = %d\n", pipeptr->writePos);
	//kprintf("errp = %d\n", pipeptr->readPos);
	restore(mask);
	return OK;
}

/*---------------------------------------------------------------------

======================================================================*/

syscall pipestate(
		int32 pipe, 	/*id of pipe*/
		int32 *nc,  	/*elements in buffer*/
		int32 *ns	/* available space*/
	)
{

//disable interrupts and make ptr
	intmask mask;
	struct pipeent *pipeptr;
	
	mask = disable();
//check that ID is valid at least
	if(pipe >= NPIPE || pipe <0){
		restore(mask);
		return SYSERR;
	}
	pipeptr = &pipetab[pipe];
	*nc = semcount(pipeptr->rsem);
	*ns = semcount(pipeptr->wsem);
	
	if(pipeptr->inUse == 0){
		if(pipeptr->rRecord < 0){
			*nc = 0;
		} else {
			*nc = pipeptr->rRecord;
		}
		if(pipeptr->wRecord > PIPE_BS){
			*ns= PIPE_BS;
		} else {
			*ns = pipeptr->wRecord;
		}
	
		return PIPE_AVAL;
		
	} else {
		if(semcount(pipeptr->rsem) < 0){
			*nc = 0;
		} else {
			*nc = semcount(pipeptr->rsem);
		}
		if(semcount(pipeptr->wsem) > PIPE_BS){
			*ns = PIPE_BS;
		} else {
			*ns = semcount(pipeptr->wsem);
		}
		
	
		return PIPE_USED;
	}
}
/*---------------------------------------------------------------------

======================================================================*/
/*int32 calculateAttempt(int32 pipe, int32 len, int32 c_i){

	int32 missing = len - c_i;
	struct pipeent *pipeptr;
	pipeptr = &pipetab[pipe];
	
	int32 available = PIPE_BS - pipeptr->writePos;
	*/
	



