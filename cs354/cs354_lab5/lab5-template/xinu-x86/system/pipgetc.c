#include <xinu.h>

devcall pipgetc(struct dentry *devptr) {
    // LAB2: TODO
    struct pipe_t *pipeptr;
    pipeptr = &pipe_tables[devptr->dvminor];
    
if(pipeptr->removingwriter != 1){

	if(pipeptr->state != PIPE_CONNECTED){
		 //	kprintf("><\n");
			return SYSERR;
	}
	if(pipeptr->readerpid != currpid){
			return SYSERR;
	}
	
}    
    wait(pipeptr->rsem);
    
    char ch;
    ch =  pipeptr->buffer[pipeptr->rpos];
kprintf("got: %c\n", ch);
    pipeptr->rpos++;
    if(pipeptr->rpos >= PIPE_SIZE){
    	pipeptr->rpos = 0;
    }
    
    signal(pipeptr->wsem);

    
    return (devcall)ch;
}

