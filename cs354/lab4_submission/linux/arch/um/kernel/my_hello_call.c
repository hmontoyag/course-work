#include <linux/kernel.h>

asmlinkage long sys_my_hello_call(void){
	printk(KERN_ALERT "Hello World !!!\n"); //KERN_ALERT is loglevel, making sure that the msg will display on console
	return 0;

}
