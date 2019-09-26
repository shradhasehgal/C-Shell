#include "headers.h"

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
          char str[200];
          for(int i=0; i < back_g; i++)
          {
               if(jobs[i].PID == pid)
               {
                    strcpy(str, jobs[i].job_name);
                    shift(i);      
                    break;
               }
          }

          if(WEXITSTATUS(x) == 0 && WIFEXITED(x))
          fprintf(stderr,"\033[1;31m\n%s with PID %d exited normally\n\033[0m", str, pid);
     
          else fprintf(stderr,"\033[1;31m\n%s with PID %d failed to exit normally\n\033[0m",str, pid);
          prompt();
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

               signal(SIGTTOU, SIG_IGN);
               signal(SIGTTIN, SIG_IGN);
               tcsetpgrp(STDIN_FILENO, pid);
               wpid = waitpid(pid, &status, WUNTRACED);
               tcsetpgrp(STDIN_FILENO, getpgrp());
               signal(SIGTTOU, SIG_DFL);
               signal(SIGTTIN, SIG_DFL);
          }

          else
          {
               // signal(SIGCHLD, handler);
               //jobs[back_g].job_name = malloc(sizeof(char) * strlen(args[0] + 2));
               strcpy(jobs[back_g].job_name, args[0]);
               
               //printf("%d\n",no_args);
               for(int i = 1; i < no_args-1; i++)
               {
                    // printf("%s\n", args[i]);
                    strcat(jobs[back_g].job_name, " ");
                    strcat(jobs[back_g].job_name, args[i]);
               }

               //jobs[back_g].job_name[strlen(args[0])]='\0';
               jobs[back_g].PID = pid;
               back_g++;
               printf("[%d] %d\n", back_g, pid);
          }
     }

     return;
}