#include "headers.h"


// void ctrl_z(int signum)
// {
//      //printf("yeeett0");
//     pid_t p = getpid();
    
//     if(p < 0)
//         perror("Error");
    
//     else if (p != SHELL_ID)
//         return;

//     if (CHILD_ID != -1)
//     {
//         printf("yeet");
//         fflush(stdout);
//         // kill(CHILD_ID, SIGTTIN);	
//         kill(CHILD_ID, SIGTSTP);
//         strcpy(jobs[back_g].job_name, CURR_JOB);
//         jobs[back_g].PID = CHILD_ID;
//         back_g++;
//     }

//     signal(SIGTSTP, ctrl_z);
// }

void shift(int i)
{
     for(int j=i; j < back_g-1; j++)
     {
          strcpy(jobs[i].job_name, jobs[i+1].job_name);
          jobs[i].PID = jobs[i+1].PID;
     }
     
     back_g--;
}
void handler(int sig)
{
     int x;
     pid_t pid = waitpid(-1, &x, WNOHANG);

     if(pid > 0)
     {
          char str[200]; int f =0;
          for(int i=0; i < back_g; i++)
          {
               if(jobs[i].PID == pid)
               {

                    strcpy(str, jobs[i].job_name);
                    shift(i);
                    f = 1;      
                    break;
               }
          }

          if(WEXITSTATUS(x) == 0 && WIFEXITED(x) && f)
          fprintf(stderr,"\033[1;31m\n%s with PID %d exited normally\n\033[0m", str, pid);
     
          else if(f) fprintf(stderr,"\033[1;31m\n%s with PID %d failed to exit normally\n\033[0m",str, pid);
          
          if(f) prompt();
          fflush(stdout);
     }
     
     return;
}

void run(char **args, int no_args, int bg)
{
     int status;
     pid_t pid = fork(), wpid;
     args[no_args] = NULL;

     if (pid < 0) 
     {    
          perror("Error");
          exit(EXIT_FAILURE);
     }

     else if (pid == 0) 
     {   
          setpgid(0, 0);
          if (execvp(args[0], args) < 0) 
          {     
               perror("Command not found");
               exit(EXIT_FAILURE);
          }
     }
     else 
     {
          if(bg == 0)
          {
               CHILD_ID = pid;
               strcpy(CURR_JOB, args[0]);
               
               for(int i = 1; i < no_args-1; i++)
               {
                    strcat(CURR_JOB, " ");
                    strcat(CURR_JOB, args[i]);
               }

               signal(SIGTTIN, SIG_IGN);

               signal(SIGTTOU, SIG_IGN);
               tcsetpgrp(STDIN_FILENO, pid);
               //signal(SIGTSTP, ctrl_z);
               wpid = waitpid(pid, &status, WUNTRACED);
               tcsetpgrp(STDIN_FILENO, getpgrp());
               signal(SIGTTIN, SIG_DFL);
               signal(SIGTTOU, SIG_DFL);

               if(WIFSTOPPED(status))
               {
                    printf("%s with PID %d suspended\n", CURR_JOB, pid);
                    strcpy(jobs[back_g].job_name, CURR_JOB);
                    jobs[back_g].PID = CHILD_ID;
                    back_g++;
               }
          }

          else
          {
               strcpy(jobs[back_g].job_name, args[0]);
               
               for(int i = 1; i < no_args-1; i++)
               {
                    strcat(jobs[back_g].job_name, " ");
                    strcat(jobs[back_g].job_name, args[i]);
               }

               jobs[back_g].PID = pid;
               back_g++;
               printf("[%d] %d\n", back_g, pid);
          }
     }

     return;
}