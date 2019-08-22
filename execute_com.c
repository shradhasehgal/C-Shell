#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "ls.c"
#include "run.c"
#include "pinfo.c"
#include "history.c"

void execute_com(char *command)
{
    strcpy(hist[hist_i], command);
    hist_i++;
    
    command = strtok(command, " \n\t\r");
    if(strcmp(command, "quit") == 0)
    {
        printf("\033[1;35m\n*** Exiting shell ***\n\033[0m");
        exit(EXIT_SUCCESS);
    }

    else if(strcmp(command, "pwd") == 0)
        pwd();

    else if(strcmp(command, "cd")==0)
        cd(command);

    else if(strcmp(command, "echo")==0)
        echo(command);

    else if(strcmp(command, "ls") == 0)
        ls(command);

    else if(strcmp(command, "pinfo") == 0)
        pinfo(command);

    else if(strcmp(command, "history") == 0)
        history(command);

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
        
        if(!strcmp(args[no_args-1], "&"))
        {
            args[no_args-1] = NULL;
            run(args, no_args, 1);
        }

        else if(args[no_args-1][strlen(args[no_args-1]) -1] == '&')
        {
            args[no_args-1][strlen(args[no_args-1]) -1] = '\0';
            run(args, no_args, 1);
        }

        else run(args, no_args, 0);
    
        for(int j=0; j < no_args; j++)
            free(args[j]);

        free(args);
        //printf("%s", command_copy);
        //if(command_copy[n-1])
    }

    //free(command_copy);
}