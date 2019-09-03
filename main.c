#include "headers.h"
#include "execute_com.c"

char *get_input()
{
    ssize_t input_size = 0;
    char *input_line = NULL;
    getline(&input_line, &input_size, stdin);
    return input_line;
}

void prompt()
{
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
        //printf("%s %s \n", CWD, HOME);
        if(p)
        {
            DIR = p + strlen(HOME);
            printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~%s\x1B[0m>", USER, HOST, DIR);
        }
        else
        {
            DIR = CWD;
            printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m%s\x1B[0m>", USER, HOST, DIR);
        }

    }

    
}

char **tokenize(char *input)
{
    char *p = strtok (input, ";");
    char **array = malloc(256 * sizeof(char *));

    no = 0;

    while (p != NULL)
    {
        array[no++] = p;
        p = strtok (NULL, ";");
    }

    return array;
}

void shell()
{
    char *input;
    do
    {
        prompt();
        signal (SIGINT, SIG_IGN);
        input = get_input();
        char **commands;
        commands = tokenize(input);
        for(int i = 0; i < no; i++)
            execute_com(commands[i]);
            

    } while(1);
}

// void ctrl_c(int signum)
// {

//     signal(SIGINT, ctrl_c); 
// } 

int main()
{
    printf("\033[1;35m\n *** Welcome to Shell Nash ***\n\033[0m");
    printf("\n She sells C-Shells on the C-Shore :)\n\n");

    gethostname(HOST, sizeof(HOST));
    getlogin_r(USER, sizeof(USER));
    char *DIR;
    
    pid_t p_id;
    p_id = getpid();
    char *exe = malloc(sizeof(char) *(40));
    sprintf(exe,"/proc/%d/exe", p_id);
    int ret = readlink(exe, HOME, 1000);
    HOME[ret] = '\0';

    for(int i = strlen(HOME)-1; i>=0; i--)
    {
        if(HOME[i] == '/')
        {
            HOME[i] = '\0';
            break;
        }
    }

    load_history();
    //signal(SIGINT, ctrl_c);
    shell();
    return 0;
}