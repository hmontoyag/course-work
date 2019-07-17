#include <xinu.h>

status pipdisconnect(did32 devpipe) {
    // LAB2: TODO
    /*789*/
    intmask mask;
    mask = disable();
    struct pipe_t *pipeptr;
    
    /*check valid dev and valid pipe*/
    if(isbaddev(devpipe)){
 		restore(mask);
 		return SYSERR;
 	}
 	if(devpipe < 25 || devpipe >= (25+MAXPIPES)){
 		restore(mask);
 		return SYSERR;
 	} 
 	
 	//get related pipe from pipe_tables
 	int minor = devpipe - 25; //minor-number, also pipid pf corresponding pipe
 	pipeptr = &pipe_tables[minor];
 	
 	//check that pipe is connected
 	if(pipeptr->state!=PIPE_CONNECTED){
 		restore(mask);
 		return SYSERR;
 	}
 	
 	//check that currpid is authoeized for this call (writerpid or readerpid)
	if(currpid!=pipeptr->writerpid && currpid!=pipeptr->readerpid){
		restore(mask);
		return SYSERR;
	} 	
	
 	//who (valid) called
 	if(currpid==pipeptr->writerpid){			//writer called---------------- wait for reader to finish
 		//kprintf("EO\n");
			pipeptr->removingwriter = 1;
    		pipeptr->writerpid = -1;
    		pipeptr->wpos = 0;
			struct dentry *devptr;
			devptr = &devtab[pipeptr->bounddev];
			
    		if(semcount(pipeptr->rsem)!=0){
    			//kprintf("semcount ni kill\n");
    			while(semcount(pipeptr->rsem)!=0){
    				//kprintf("w\n");
    				pipgetc(devptr);
    			}
    		}
			    
			pipeptr->readerpid = -1;
			pipeptr->state = PIPE_USED;
			pipeptr->bounddev = -1;
			semreset(pipeptr->wsem, PIPE_SIZE);
			semreset(pipeptr->rsem, 0);
				memset(pipeptr->buffer, 0, PIPE_SIZE);
			pipeptr->removingwriter = 0;
	
 		
 	} else {									//reader called---------------- no wait
 	//clean pipe and reset semaphores, writer/readerpid + state
 		//kprintf("E000\n");
	 	memset(pipeptr->buffer, 0, PIPE_SIZE);
	 	semreset(pipeptr->wsem, PIPE_SIZE);
	 	semreset(pipeptr->rsem, 0);
	 	pipeptr->readerpid = -1;
	 	pipeptr->writerpid = -1;
	 	pipeptr->state = PIPE_USED;
	 	//
	 	
 	
 	}
 	
    restore(mask);
    /*789*/
	return OK;
}
