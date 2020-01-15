/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>


/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
extern long ctr1000;

SYSCALL chprio(int pid, int newprio)
{
	update_syscall_count(currpid,1);
        unsigned long syscall_exec_start = ctr1000;
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		update_syscall_time(currpid,1,ctr1000 - syscall_exec_start);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	update_syscall_time(currpid,1,ctr1000 - syscall_exec_start);
	return(newprio);
}
