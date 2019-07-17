#include <xinu.h>

did32 pipcreate() {
    // LAB2: TODO
    /*789*/
    intmask mask;
    struct dentry *devptr;
    struct pipe_t *pipeptr;
    did32 retval;
    /* just as pipetable indexes start from 0 to MAXPIPES-1, minor-number from the pipe
    devices also go from 0 to MAXPIPES-1;
    
    So if you start creating from 0, and binding that to whichever dev has a similar 
    minor-number .
    
    Do fix 25 as starting point for your iteration through devtab
    */
    mask = disable();
    for(int i = 0; i<MAXPIPES; i++){
    	pipeptr = &pipe_tables[i];
    	if(pipeptr->state==PIPE_FREE){
    	
    		//pipedevs start at pipenum 25, and go up until 34, their minor numbers match pipes
    		//in pipetables, so if i=0, match to 25, if i = 5, match to 30
    		pipeptr->bounddev = 25 + i;  //25 since its first pipedev
    		pipeptr->wsem = semcreate(PIPE_SIZE); //producer/writer
    		pipeptr->ownerpid = currpid;		  	
 			pipeptr->rsem = semcreate(0);		//consumer/reader
    		pipeptr->state = PIPE_USED;
    		pipeptr->ispipereading = 0;
    		pipeptr->killing = 0;
    		pipeptr->removingwriter = 0;
    		pipeptr->readerpid = -1;
    		pipeptr->writerpid = -1;
    		retval = pipeptr->bounddev;
    			memset(pipeptr->buffer, 0, PIPE_SIZE);
    		restore(mask);
    		return retval;
    	}
   
    }
    restore(mask);
    return SYSERR;
    /*789*/
    //return -1;
}
