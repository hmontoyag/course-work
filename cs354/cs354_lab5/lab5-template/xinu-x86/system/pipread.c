#include <xinu.h>

uint32 pipread(struct dentry *devptr, char* buf, uint32 len) {
    // LAB2: TODO
 
    struct pipe_t *pipeptr;
    pipeptr = &pipe_tables[devptr->dvminor];

 	
    if (len < 0){
    	pipeptr->ispipereading = 0;
    	return SYSERR;
    } else if (len == 0){
    	pipeptr->ispipereading = 0;
    	return 0;
    }
    
    int32 ret = len;
    int i = 0;
    int got = 0;
    
    for(; len > 0; len--){
    	
    	if(SYSERR == (buf[i] = pipgetc(devptr)) || pipeptr->state==PIPE_FREE){
    		return i;
    		
    	}
    	i++;
    	
    }
    
    pipeptr->ispipereading = 0;
	return i;
}
