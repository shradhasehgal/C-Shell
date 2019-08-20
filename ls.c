#include "headers.h"

void ls_blank(char *dirname)
{

    
}

void ls_l(char *dir)
{

}

void ls_a(char *dir)
{

}

void ls_al(char *dir)
{

}


void ls(char *command)
{
    int f1 = 0, f2 = 0, f3 = 0;
    char *token = command;

    while (token != NULL)
    {
        if(!strcmp(token,"-l"))
            f1 = 1;
    
        else if(!strcmp(token,"-a"))
            f2 = 1;

        else if(!strcmp(token,"-al"))
            f3 = 1;
        
        else if(!strcmp(token,"-la"))
            f3 = 1;

        else
        {
            char *final_path;
            if(token[0] == '~')
            {
                int n = strlen(token);
                char *temp = (char *)malloc(sizeof(char) *n);
                
                if(n > 1)
                {
                    for(int i=1; i < n; i++)
                        temp[i-1] = token[i];
                }
                
                final_path = (char *)malloc(sizeof(char) *(n + strlen(HOME)));
                strcpy(final_path, HOME);
                strcat(final_path, temp);
                free(temp);
            }

            else final_path = token;
            
            if(f1 && f2 || f3)
                ls_al(final_path);
            else if(f1)
                ls_l(final_path);

            else if(f2)
                ls_a(final_path);

            else ls_blank(final_path);
        }

        token = strtok(NULL, " \n\t\r");
        
    }
}