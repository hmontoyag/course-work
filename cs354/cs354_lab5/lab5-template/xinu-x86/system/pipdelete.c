#include <xinu.h>

status pipdelete(did32 devpipe) {
    // LAB2: TODO
    /*789*/
 /*	devpipe must be between 25 <= devpipe < 25+MAXPIPES (35), 
 	if its bound/in-use, then pipe_tables[devpipe-25]*/
 	intmask mask;
 	mask = disable();
 	//kprintf("del\n");
 	struct pipe_t *pipeptr;
 	
 	if(isbaddev(devpipe) || devpipe < 25 || devpipe >= (25+MAXPIPES)){
 		restore(mask);
 		return SYSERR;
 	}

 	int minor = devpipe - 25; //minor-number, also pipid pf corresponding pipe
 	pipeptr = &pipe_tables[minor];
 	
 	//dont check for the following is pipe is dying

	 	if(pipeptr->state == PIPE_FREE){
	 		restore(mask);
	 		return SYSERR;
	 	}
	 	/*check if currproc can delete*/
	 	if(pipeptr->ownerpid != currpid){
	 		restore(mask);
	 		return SYSERR;
	 	}
	 	
 	/*now do delete*/
 	
 	memset(pipeptr->buffer, 0, PIPE_SIZE);

 	pipeptr->ownerpid = -1;
 	pipeptr->bounddev = -1;
 	pipeptr->readerpid = -1;
 	pipeptr->writerpid = -1;
 	semdelete(pipeptr->wsem);
 	semdelete(pipeptr->rsem);
 	pipeptr->state = PIPE_FREE;
 	/*might be missing some hard stop for reader and writer processes?     ????*/
 	restore(mask);
 	
 
 /*789*/   
	return OK;
}
