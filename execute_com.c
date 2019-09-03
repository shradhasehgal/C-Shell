#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "ls.c"
#include "run.c"
#include "pinfo.c"
#include "history.c"
#include "nightswatch.c"

void execute_com(char *command)
{
    strcpy(hist[hist_i % 20], command);
    hist_i++;
    
    char *com = (char *)malloc(sizeof(char) *2000);
    strcpy(com, command);
    //printf("%s\n", com);
    com = strtok(com, " \n\t\r");
    
    if(com == NULL)
        return;

    char **args = (char**)malloc(sizeof(char*) * 100);
    int no_args = 0;
    
    while (com != NULL)
    {
        args[no_args]  = (char *)malloc(sizeof(char) *strlen(com)+10);
        strcpy(args[no_args], com);
        com = strtok(NULL, " \n\t\r");
        no_args++;
    }

    command = strtok(command, " \n\t\r");

    if(strcmp(args[0], "nightswatch") == 0)
        nightswatch(args, no_args);
    
    else if(!strcmp(args[no_args-1], "&"))
    {
        args[no_args-1] = NULL;
        run(args, no_args, 1);
    }

    else if(args[no_args-1][strlen(args[no_args-1]) -1] == '&')
    {
        args[no_args-1][strlen(args[no_args-1]) -1] = '\0';
        run(args, no_args, 1);
    }
    
    else if(strcmp(command, "quit") == 0)
    {
        write_history();
        printf("\033[1;35m\n*** Goodbye, %s ***\n\033[0m", USER);
        printf("\n*** Nash Out ~(˘▾˘~) ***\n\n");
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

    else run(args, no_args, 0);
    
    for(int j=0; j < no_args; j++)
        free(args[j]);

    free(args), free(com);
    
}