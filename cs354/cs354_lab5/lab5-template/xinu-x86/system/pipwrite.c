#include <xinu.h>

uint32 pipwrite(struct dentry *devptr, char* buf, uint32 len) {
    // LAB2: TODO
    
    if (len < 0){
    	return SYSERR;
    } else if (len == 0){
    	return 0;
    }
    int32 ret = len;
    
    for(; len > 0; len--){
    	if( 1 != pipputc(devptr,*buf++)){
    		return SYSERR;
    	}
    }
    
    return ret;
}
