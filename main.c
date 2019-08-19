#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define EXIT_FAILURE 1
// Global variables
char HOST[256], USER[256], CWD[2048], HOME[2048];


char *get_input()
{
    ssize_t input_size = 0;
    char *input_line = NULL;
    getline(&input_line, &input_size, stdin);
    return input_line;
}

void prompt()
{
    gethostname(HOST, sizeof(HOST));
    getlogin_r(USER, sizeof(USER));
    char *DIR;
    
    if (getcwd(CWD, sizeof(CWD)) == NULL)
    {
       perror("getcwd() error");
       exit(EXIT_FAILURE);
    }

    else
    {
        char * p;
        p = strstr(CWD, HOME);
        if(p) DIR = p + strlen(HOME);
        else DIR = CWD;
    }
    
    printf("\x1B[1;32m<%s@%s\x1B[0m:\x1B[1;34m~%s>\x1B[0m",USER, HOST, DIR);
}

void shell()
{
    char *input;
    do
    {
        prompt();
        input = get_input();

    } while(1);
}

int main()
{
    if (getcwd(HOME, sizeof(HOME)) == NULL)
    {
       perror("getcwd() error");
       return 1;
    }
    else shell();
    return 0;
}