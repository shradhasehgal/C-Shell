#include "headers.h"


// void handler2(int sig)
// {
//   int x;
//   pid_t pid = waitpid(-1, &x, WNOHANG);

//   if(pid > 0)
//   {

//       if(WEXITSTATUS(x) == 0 && WIFEXITED(x))
//       fprintf(stderr,"\033[1;31m\nCRONJOB completed\n\033[0m");
  
//       else fprintf(stderr,"\033[1;31m\nCould not complete CRONJOB\n\033[0m");
//       prompt();
//       fflush(stdout);
//   }
  
//   return;
// }

void cron(char **args, int no_args)
{
  int time, total, note;
  if(no_args < 7)
    printf("Enter command in the form `cronjob -c ls -t 3 -p 6`");
  
  else 
  {
      for(int i=0; i < no_args; i++)
      {
        if(!(strcmp(args[i],"-c"))
          note = i+1;
          
        else if(!(strcmp(args[i],"-t"))
          time = args[i+1];

        else if(!(strcmp(args[i],"-p"))
          total = args[i+1];
      }
 
      no_args -= 6;

      for(int i=0; i<no_args; i++)
        args[i] = args[i+note];

      args[no_args] = NULL;
  } 

  int status;
  pid_t pid = fork(), wpid;
  args[no_args] = NULL;

  int number_exec = total / time, iter = 0;
  if (pid < 0) 
  {    
      perror("Error");
      exit(EXIT_FAILURE);
  }

  else if (pid == 0) 
  {
    while(iter < number_exec)
    {
      sleep(time);
      if (execvp(args[0], args) < 0) 
      {     
            perror("Command not found");
            exit(EXIT_FAILURE);
      }

      iter++;
    }

    return;   
  }

}