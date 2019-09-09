#include "headers.h"

int isfile(char* path) 
{
    struct stat f;
    if(stat(path, &f) == 0 && !S_ISDIR(f.st_mode))
        return 1;
    else return 0;
}

void redirection(char *command)
{
    int status;
    char *output[2], *input[2];
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    char * out = strstr(command, ">");
    char * in = strstr(command, "<");

    output[0] = &command[0];
    
    if(out != NULL)
    { 
        output[0] = strtok(command, ">");
        output[1] = strtok(NULL, ">");
        output[1] = strtok(output[1], " \r\t\n");
    }

    input[0] = output[0];
    if(in != NULL)
    { 
        input[0] = strtok(input[0], "<");
        input[1] = strtok(NULL, "<");
    }

    char **args = (char**)malloc(sizeof(char*) * 100);
    int no_args = 0;
    
    if(in != NULL)
    {
        if(input[1] == NULL)
        {
            printf("Specify file name for input\n");
            return;
        }
        
        input[1] = strtok(input[1], " \n\r\t");
        if(!isfile(input[1]))
        {
            printf("File does not exist\n");
            return;
        }
        // int fd_in = open(input[1], O_RDONLY);
        // close(fd_in);
    }

    input[0] = strtok(input[0], " \n\r\t");

    while (input[0] != NULL)
    {
        args[no_args]  = (char *)malloc(sizeof(char) *strlen(input[0])+10);
        strcpy(args[no_args], input[0]);
        input[0] = strtok(NULL, " \n\t\r");
        no_args++;
    }

    int out_type = 0;
    if(out != NULL)
    {
        out = strstr(command, ">>");
        if(out != NULL)
            out_type = 2;
        else out_type = 1;

        if(output[1] == NULL)
        {
            printf("Enter output file\n");
            return;
        }
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("Error in forking");
        return;
    }
    
    if(pid == 0)
    {
        if(in != NULL)
        {
            int fd_in = open(input[1], O_RDONLY);
            if(fd_in < 0) 
                perror("Input redirection");   
            
            if(dup2(fd_in, 0) != 0) 
                perror("Input redirection - dup2 fail");
            
            close(fd_in);
        }

        if(out_type)
        {
            int fd_out;
            if(out_type == 1)
                fd_out = open(output[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

            else if(out_type == 2)
                fd_out = open(output[1], O_WRONLY | O_CREAT | O_APPEND, 0644);

            if(fd_out < 0)
                perror("Output Redirection");
            
            if(dup2(fd_out, 1) != 1) 
                perror("Output Redirection - dup2 fail");
        
            close(fd_out);
            
        }

        execvp(args[0], args);
        dup2(saved_stdin, 0);
        close(saved_stdin);
        
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }        
    
    else while (wait(&status) != pid);
    
    for(int j=0; j < no_args; j++)
        free(args[j]);
    free(args);
}
