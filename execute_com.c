#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "ls.c"

void execute_com(char *command)
{
    command = strtok(command, " \n\t\r");
    if(strcmp(command, "quit") == 0)
        exit(EXIT_SUCCESS);

    else if(strcmp(command, "pwd") == 0)
        pwd();

    else if(strcmp(command, "cd")==0)
        cd(command);

    else if(strcmp(command, "echo")==0)
        echo(command);

    else if(strcmp(command, "ls") == 0)
        ls(command);
}