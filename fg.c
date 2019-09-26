#include "headers.h"

void fg(char **args, int no_args)
{
    if(no_args!=2)
    {
        printf("Incorrect number of arguments.\nFormat is `fg <jobNumber>`.\n");
        return;
    }
    int pid, job_no = atoi(args[1]), status;
	if (job_no > back_g)
	{
		printf("Enter valid job number.");
		return;
	}
	pid = jobs[job_no-1].PID;
	strcpy(CURR_JOB, jobs[job_no-1].job_name);
	CHILD_ID = pid;
	shift(job_no);
	signal(SIGTTOU, SIG_IGN); signal(SIGTTIN, SIG_IGN); tcsetpgrp(STDIN_FILENO, CHILD_ID); 
	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpgrp()); signal(SIGTTOU, SIG_DFL); signal(SIGTTIN, SIG_DFL);  
	return;
}