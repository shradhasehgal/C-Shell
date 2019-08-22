#include "headers.h"

void history(char *command)
{
    char *token = command;
    token = strtok(NULL, " \"\n\t\r"); 

    int n = 10;
    if(token != NULL)
        n = atoi(token);

    int count = 0;
    for(int i = hist_i-1; i >=0 && count < n; i--)
    {
        printf("%s", hist[i % 21]);
        count++;
    }
    
}