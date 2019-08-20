#include "headers.h"

void cd(char *command)
{
    char *token = strtok(NULL, " \n\t\r");
    if(token == NULL) 
    {
        if(chdir(HOME) != 0) 
            perror("Error");
    }

    else if(token[0] == '~')
    {   
        int n = strlen(token);
        char *temp = (char *)malloc(sizeof(char) *n);
        strcpy(temp, "");
        if(n > 1)
        {
            for(int i=1; i < n; i++)
            temp[i-1] = token[i];
        }
        
        char *final_path = (char *)malloc(sizeof(char) *(n + strlen(HOME)));
        strcpy(final_path, HOME);
        strcat(final_path, temp);
        free(temp);
        printf("%s\n", final_path);
        if(chdir(final_path) != 0) 
            perror("Error");

        free(final_path);
    }
    
    else if(chdir(token) != 0) 
        perror("Error");

    return;
}