#include "headers.h"

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
          if(bg == 1)
               setpgid(0, 0);

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
               back_g++;
               printf("[%d] %d\n", back_g, pid);
          }
     }

     return;
}