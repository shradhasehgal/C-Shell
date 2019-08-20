#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "pwd.c"

#define EXIT_SUCCESS 0

void execute_com(char *command)
{
    command = strtok(command, " \n\t\r");
    if(strcmp(command, "quit") == 0)
        exit(EXIT_SUCCESS);

    else if(strcmp(command, "pwd") == 0)
        pwd();

    else if(strcmp(command, "ls")==0)
        ls();
    
    
}