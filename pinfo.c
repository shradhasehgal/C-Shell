#include "headers.h"

void pinfo(char *command)
{
    char *token = command;
    token = strtok(NULL, " \"\n\t\r");
    
    if(token == NULL)
    {
        pid_t shell_pid = getpid();
        printf("pid -- %d\n", shell_pid);
    }

}