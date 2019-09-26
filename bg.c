#include "headers.h"

void bg(char **args, int no_args)
{
    if(no_args != 2)
        printf("Incorrect number of arguments.\nFormat is `bg <jobNumber>`.");

    else
    {
        int job_no = atoi(args[1]);
        if (job_no > back_g)
            printf("Enter valid job number\n");
        
        else kill(jobs[job_no-1].PID, SIGCONT);   
    }
    
}