#define _GNU_SOURCE

#include <arch/x86/include/generated/uapi/asm/unistd_64.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>

/**************************************/
/*
Takes a PID, and returns its prio, name, and ppid. Iterates until it reaches PID 0, upon which it cant go any higher in hierarchy.
If it recieves 0 as PID, simply says so, as there is no name or priority of relevance.
*/
/**************************************/
int main(int argc, char **argv){
	if( argc < 2){
		return 0;
	}
	int pid = atoi(argv[1]);
	int priority;
	int ppid = -1;
	int it = 0;
	if(pid == 0){
		char temp_buffer[21];
		printf("Already at PID=0.\n");
//		syscall(__NR_my_get_proc_info_by_id, pid, temp_buffer);
//		memcpy(&priority, temp_buffer + 16,  4);
//		printf("name: %s; PRIO: %d; NO PPID\n", temp_buffer, priority);
		ppid = 0;
	}
	while (ppid != 0){
		char temp_buffer[21];
		printf("Calling.  Step No.:%d\n",it);
		it++;
		syscall(__NR_my_get_proc_info_by_id, pid, temp_buffer);
		memcpy(&priority, temp_buffer+16, 4);
		memcpy(&ppid, temp_buffer +16 +4, 4);
//		pid = ppid;
		printf("name: %s; PRIO: %d; PPID : %d\n\n", temp_buffer, priority, ppid);
		pid = ppid;

	}	
/*	char sec[21];
	syscall(__NR_my_get_proc_info_by_id, ppid, sec);
	memcpy(&priority, sec+16, 4);
	memcpy(&ppid, sec + 16 + 4, 4);
	printf("name: %s; PRIO: %d; PPID: %d\n", sec, priority, ppid);
*/	

}
