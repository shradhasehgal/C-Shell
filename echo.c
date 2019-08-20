#include "headers.h"

void echo(char *command)
{

    char *token = command;
    if (token == NULL) 
        printf("\n");

    while (token != NULL)
    {
        printf("%s\n",token);
        token = strtok(NULL, " \n\t\r");
    }

    return;
}