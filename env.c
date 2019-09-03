#include "headers.h"

void seten(char **args, int no_args)
{
    if(no_args !=2 &&  no_args != 3)
        printf("Incorrect number of arguments. Provide either 1 or 2 arguments.\nSyntax: `setenv var [value]`\n");

    else if(no_args == 2) 
    {
        if(setenv(args[1], "\0", 2) < 0)
            perror("Error");
    }

    else if(setenv(args[1], args[2] , 2) < 0)
        perror("Error");

    return;
}

void unseten(char **args, int no_args)
{
    if(no_args != 2)
        printf("Incorrect number of arguments. Provide only 1 argument.\nSyntax: `unsetenv var`\n");

    else if (unsetenv(args[1]) < 0)
        perror("Error");

    return;
}