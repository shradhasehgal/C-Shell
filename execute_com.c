#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "ls.c"
#include "run.c"
#include "pinfo.c"
#include "history.c"
#include "nightswatch.c"
#include "env.c"
#include "jobs.c"
#include "kjob.c"
#include "overkill.c"
#include "bg.c"

void removeSpaces(char *str) 
{ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ' && str[i]!='\t' && str[i]!='\n') 
            str[count++] = str[i]; 

    str[count] = '\0'; 
} 


void execute_com(char *command)
{
    
    char *com = (char *)malloc(sizeof(char) *2000);
    char *com2 = (char *)malloc(sizeof(char) *2000);
    strcpy(com, command);
    strcpy(com2, command);
    removeSpaces(com2);
    int up = 0;
    com = strtok(com, " \n\t\r");
    
    if(com == NULL)
        return;

    if(com2[0]=='\033')
    {
        int i = 0;
        if(strlen(com2)%3 == 0)
        {
            while(com2[3*i]!= '\0')
            {
                if(com2[3*i] == '\033' && com2[3*i+1] =='[' && com2[3*i+2] == 'A')  //checking for up key
                    up++, i++;

                else 
                {
                    up = 0;
                    break;
                }
            }

            if(up > 0)
            {
                prompt();
                printf("%s",hist[(hist_i - up) % 20]);
                strcpy(command, hist[(hist_i - up) % 20]);
                strcpy(com, command);
                com = strtok(com, " \n\t\r");
            }
        }
    }
    
    strcpy(hist[hist_i % 20], command);
    hist_i++;

    char **args = (char**)malloc(sizeof(char*) * 100);
    int no_args = 0;
    
    while (com != NULL)
    {
        //printf("%s\n",com);
        args[no_args]  = (char *)malloc(sizeof(char) *strlen(com)+10);
        strcpy(args[no_args], com);
        com = strtok(NULL, " \n\t\r");
        no_args++;
    }

    command = strtok(command, " \n\t\r");

    if(!strcmp(args[0], "nightswatch"))
        nightswatch(args, no_args);
    
    else if(!strcmp(args[0], "kjob"))
        kjob(args, no_args);
    
    else if(!strcmp(args[0], "bg"))
        bg(args, no_args);
    
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

    else if(!strcmp(args[0], "setenv"))
        seten(args, no_args);

    else if(!strcmp(args[0], "unsetenv"))
        unseten(args, no_args);
    
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

    else if(strcmp(command, "jobs") == 0)
        job();
    
    else if(strcmp(command, "overkill") == 0)
        overkill();

    else run(args, no_args, 0);
    
    for(int j=0; j < no_args; j++)
        free(args[j]);

        free(com2);
        free(com);
        free(args);  
    
}