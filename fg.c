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
	shift(job_no);
	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	return;
}