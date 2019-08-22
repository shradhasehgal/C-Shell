#include "headers.h"

void cd(char *command)
{
    char *token = command;
    token = strtok(NULL, " \n\t\r");
    if(token == NULL) 
    {
        if(chdir(HOME) != 0) 
            perror("Error");
    }

    else if(token[0] == '~')
    {   
        int n = strlen(token);
        char *temp = (char *)malloc(sizeof(char) *n);
        strcpy(temp,"\0");
        int i=0;
        if(n > 1)
        {
            for(i=1; i < n; i++)
                temp[i-1] = token[i];
        }
        temp[i] ='\0';
        
        char *final_path = (char *)malloc(sizeof(char) *(n + strlen(HOME)+12));
        strcpy(final_path, HOME);
        strcat(final_path, temp);
        final_path[n +strlen(HOME)-1] ='\0';
        free(temp);
        if(chdir(final_path) != 0) 
            perror("Error");

        free(final_path);
    }
    
    else if(chdir(token) != 0) 
        perror("Error");

    return;
}