#include <stdio.h>
#include <string.h>

void pwd()
{
    char *PWD = (char *)malloc(2048 * sizeof(char));
    if (getcwd(PWD, 2048) == NULL)
    {
       perror("getcwd() error");
       exit(1);
    }

    else printf("%s\n", PWD);
    free(PWD);
    return;
}