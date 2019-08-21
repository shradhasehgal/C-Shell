#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "ls.c"
#include "foreground.c"
#include "background.c"

void execute_com(char *command)
{
    //int n = strlen(command);
    //char *command_copy = (char *)malloc(sizeof(char) * n +10);
    //strcpy(command_copy, command);
    //command_copy[n-1] ='\0';
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

    else
    {
        char **args = (char**)malloc(sizeof(char*) * 100);
        int no_args = 0;
        while (command != NULL)
        {
            args[no_args]  = (char *)malloc(sizeof(char) *strlen(command)+10);
            strcpy(args[no_args], command);
            command = strtok(NULL, " \n\t\r");
            no_args++;
        }
        
        if(args[no_args-1] == '&')
            background(args, no_args);

        else foreground(args, no_args);
    
        for(int j=0; j < no_args; j++)
            free(args[j]);

        free(args);
        //printf("%s", command_copy);
        //if(command_copy[n-1])
    }

    //free(command_copy);
}