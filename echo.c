#include "headers.h"

void echo(char *command)
{
    char *token = command;
    token = strtok(NULL, " \"\n\t\r"); 
    while (token != NULL)
    {
        printf("%s ",token);
        token = strtok(NULL, " \"\n\t\r");
    }
    printf("\n");
    return;
}