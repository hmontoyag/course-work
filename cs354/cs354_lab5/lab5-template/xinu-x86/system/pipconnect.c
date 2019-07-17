#include <xinu.h>

status pipconnect(did32 devpipe , pid32 writer, pid32 reader) {
    // LAB2: TODO
    /*789*/
    intmask mask;
    mask = disable();
    
    /*check pids and devpipe are valid*/
    if(isbaddev(devpipe)||isbadpid(writer)||isbadpid(reader)||(devpipe < 25 || devpipe >= 25 + MAXPIPES)){
    	restore(mask);
    	return SYSERR;
    }
    
    struct pipe_t *pipeptr;
    pipeptr = &pipe_tables[devpipe - 25]; //devpipe - 25 should at least be 25, first pipe, at most be 34 -25 = 9 last pipe

    /*check pipe not already connected to processes*/
    if(pipeptr->readerpid!=-1 || pipeptr->writerpid!=-1){
    	restore(mask);
    	return SYSERR;
    }
 
    /*check state is USED, */
    if(pipeptr->state!=PIPE_USED){
    	restore(mask);
    	return SYSERR;
    }
    /*connect*/
   // kprintf("connecting: %d/%d \n", writer, reader);
    pipeptr->readerpid = reader;
    pipeptr->writerpid = writer;
    pipeptr->wpos = 0;
    pipeptr->rpos =0;
    pipeptr->wsem = semcreate(PIPE_SIZE);
    pipeptr->rsem = semcreate(0);	
    pipeptr->removingwriter = 0;
    pipeptr->killing = 0;
    	memset(pipeptr->buffer, 0, PIPE_SIZE);
    pipeptr->state = PIPE_CONNECTED;
    restore(mask);
    /*789*/
	return OK;
}
