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
	shift(job_no-1);
	signal(SIGTTIN, SIG_IGN); signal(SIGTTOU, SIG_IGN); tcsetpgrp(STDIN_FILENO, CHILD_ID); 
	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpgrp()); signal(SIGTTIN, SIG_DFL); signal(SIGTTOU, SIG_DFL); 
	//signal(SIGTSTP, ctrl_z);

	if(WIFSTOPPED(status))
	{
		printf("%s with PID %d suspended\n", CURR_JOB, CHILD_ID);
		strcpy(jobs[back_g].job_name, CURR_JOB);
        jobs[back_g].PID = CHILD_ID;
        back_g++;
	}

	return;
}