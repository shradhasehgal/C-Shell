#include "headers.h"

char **pipe_elements(char *input)
{
    char *p = strtok (input, "|");
    char **pipe_args = malloc(256 * sizeof(char *));

    no = 0;

    while (p != NULL)
    {
        pipe_args[no++] = p;
        p = strtok (NULL, "|");
    }

    return pipe_args;
}

void piping(char *command)
{
    char **pipe_args = pipe_elements(command);
    int type=0, parr[2], fd=0; pid_t newproc;

    for(int j=0; pipe_args[j]!=NULL; j++)
    {
        pipe(parr);
        newproc=fork();
        if(newproc==0)
        {
            dup2(fd , 0);
            if(pipe_args[j+1]!=NULL) dup2(parr[1],1);
            close(parr[0]);
            execute_com(pipe_args[j]);
            exit(2);
        }
        else
        {

            wait(NULL);
            close(parr[1]);
            fd = parr[0];
        }
    }
}
