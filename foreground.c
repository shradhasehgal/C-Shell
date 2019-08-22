#include "headers.h"

void handler(int sig)
{
     int x;
     pid_t pid = waitpid(-1, &x, WNOHANG);

     if(pid > 0)
     {
          back_g--;
          if(WEXITSTATUS(x) == 0 && WIFEXITED(x))
          fprintf(stderr,"\033[1;31m\nProcess with PID %d exited normally\n\033[0m", pid);
     
          else fprintf(stderr,"\033[1;31m\nProcess with PID %d failed to exit normally\n\033[0m", pid);
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
               printf("Command not found\n");
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
               back_g++;
               printf("[%d] %d\n", back_g, pid);
          }
     }

     return;
}