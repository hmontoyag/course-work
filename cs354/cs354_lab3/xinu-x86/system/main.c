/*  main.c  - LAB 3 SAMPLE TEST CASE */

#include <xinu.h>
#include <stdio.h>

int32 receiver(void) {
	umsg32 msgbuf;
	sleep(2);
	while (TRUE) {
		msgbuf = receive();
		kprintf("Receiver Process %d, Message: %d\n", currpid, msgbuf);
	}
	return OK;
}

int32 receiver_callback(void) {
	umsg32 msgbuf;
	msgbuf = receive();
	kprintf("In callback of Process %d, Message: %d\n", currpid, msgbuf);
	return OK;
}

int32 sender(pid32 pr, umsg32 msg){
	sleepms(400);
//	kprintf("Sending \"%d\" to Process %d\n", msg, pr);
	int32 ret = sendblk(pr, msg);
	if(ret != OK)
		kprintf("FAILED Sending %d\n", msg);
	sleep(4);
	return OK;
}

int32 sender_no_blk(pid32 pr, umsg32 msg){
	sleepms(400);
//	kprintf("Sending \"%d\" to Process %d\n", msg, pr);
	int32 ret = send(pr, msg);
	if(ret != OK)
		kprintf("FAILED Sending %d\n", msg);
	sleep(4);
	return OK;
}

int32 test_reg_cb(void) {
	
	int32 ret = cbreg(&receiver_callback); 
	if(ret != OK)
		kprintf("Registering CB failed\n");

	while(1){
		; //busy doing nothing
		//sleepms(5); //The test should also work with sleep
	}
	
	return OK;
}


process	main(void)
{
	kprintf("\nHello World!\n");
	pid32 pr;
	pid32 ps[3];
	
	kprintf("\nTest 0: Send (No blocking)\n");
	pr = create(receiver, 1024, 10, "receiver", 0);
	resume(pr);
	sleepms(500);
	resume(ps[0] = create(sender_no_blk, 2048, 10, "sender1-1", 2, pr, 11));
	resume(ps[1] = create(sender_no_blk, 2048, 10, "sender1-2", 2, pr, 12));
	resume(ps[2] = create(sender_no_blk, 2048, 10, "sender1-3", 2, pr, 13));
	sleep(5);
	kill(ps[0]); kill(ps[1]); kill(ps[2]); 
	kill(pr);
	
	kprintf("\nTest 1: Send-blocking\n");
	pr = create(receiver, 1024, 10, "receiver", 0);
	resume(pr);
	sleepms(500);
	resume(ps[0] = create(sender, 2048, 10, "sender2-1", 2, pr, 21));
	resume(ps[1] = create(sender, 2048, 10, "sender2-2", 2, pr, 22));
	resume(ps[2] = create(sender, 2048, 10, "sender2-3", 2, pr, 23));
	sleep(5);
	kill(ps[0]); kill(ps[1]); kill(ps[2]); 
	kill(pr);

	kprintf("\nTest 2: Registering a callback function\n");
	pr = create(test_reg_cb,  1024, 10, "receiver_with_cb", 0);
	resume(pr);
	sleepms(500);
	resume(ps[0] = create(sender, 2048, 10, "sender3-1", 2, pr, 31));
	resume(ps[1] = create(sender, 2048, 10, "sender3-2", 2, pr, 32));
	resume(ps[2] = create(sender, 2048, 10, "sender3-3", 2, pr, 33));
	sleep(5);
	kill(ps[0]); kill(ps[1]); kill(ps[2]); 
	kill(pr);

	/* Correct sample test output:
	
	Test 0: Send (No blocking)
	FAILED Sending 12
	FAILED Sending 13
	Receiver Process 3, Message: 11

	Test 1: Send-blocking
	Receiver Process 7, Message: 21
	Receiver Process 7, Message: 22
	Receiver Process 7, Message: 23

	Test 2: Registering a callback function
	In callback of Process 11, Message: 31
	In callback of Process 11, Message: 32
	In callback of Process 11, Message: 33
	*/

	kprintf("Finished testing\n");
	return OK;
}
