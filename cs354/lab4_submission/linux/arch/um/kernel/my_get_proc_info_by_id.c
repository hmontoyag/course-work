#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/uaccess.h>


asmlinkage long sys_my_get_proc_info_by_id(pid_t pid, void __user *user_buff){
//
	struct task_struct *t;
	t = find_task_by_vpid(pid);

//
	if(t){
		char buf[TASK_COMM_LEN];
		int prio;
		int p_pid;
		long r;
		r = 0;
		prio = t->prio;

	
		get_task_comm(buf, t);
		//copy name

		r = copy_to_user(user_buff, buf, sizeof(buf));
		//copy prio
		r = r + copy_to_user(user_buff + 16, &prio , sizeof(prio));
//		//copy parent prio

		p_pid = t->parent->pid;
		r = r + copy_to_user(user_buff + 16 + 4, &p_pid, sizeof(p_pid));
		return r;
	}
	return -1;
//


}
