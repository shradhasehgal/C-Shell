#include "headers.h"

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
                    int j;
                    strcpy(str, jobs[i].job_name);
                    for(j=i; j < back_g-1; j++)
                    {
                         strcpy(jobs[i].job_name, jobs[i+1].job_name);
                         jobs[i].PID = jobs[i+1].PID;
                    }

                    break;
               }
          }

          back_g--;
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
               do 
               {
                    wpid = waitpid(pid, &status, WUNTRACED);
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));
          }

          else
          {
               signal(SIGCHLD, handler);
               //jobs[back_g].job_name = malloc(sizeof(char) * strlen(args[0] + 2));
               strcpy(jobs[back_g].job_name, args[0]);
               jobs[back_g].job_name[strlen(args[0])]='\0';
               jobs[back_g].PID = pid;
               back_g++;
               printf("[%d] %d\n", back_g, pid);
          }
     }

     return;
}