#include <xinu.h>

devcall pipputc(struct dentry *devptr, char ch) {
    // LAB2: TODO
    
    struct pipe_t *pipeptr;
    pipeptr = &pipe_tables[devptr->dvminor];

    if(pipeptr->state != PIPE_CONNECTED){
    	return SYSERR;
    }
    
    if(pipeptr->writerpid != currpid){
    	return SYSERR;
    }


    wait(pipeptr->wsem);
    
    pipeptr->buffer[pipeptr->wpos] = ch;
kprintf("put: %c\n",ch);
    pipeptr->wpos++;
    if(pipeptr->wpos >= PIPE_SIZE){
    	pipeptr->wpos = 0;
    }
    
    signal(pipeptr->rsem);

    return 1;
}

