#include "headers.h"

char * read_file(char *filename, int n)
{   
    FILE* file = fopen(filename, "r");
    char line[256];
    char *info = malloc(sizeof(char) *256);
    int i = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        i++;
        if(i == n)
            strcpy(info, line);
    }

    fclose(file);
    return info;
}
void pinfo(char *command)
{
    char *token = command;
    token = strtok(NULL, " \"\n\t\r");
    pid_t p_id;
    
    if(token == NULL)
        p_id = getpid();

    else
        p_id = atoi(token);
    
    char *exe = malloc(sizeof(char) *(40));
    char *status = malloc(sizeof(char) *(40));
    sprintf(status,"/proc/%d/status", p_id);
    sprintf(exe,"/proc/%d/exe", p_id);

    FILE *f;

    if(!(f = fopen(status, "r")))
        printf("Process with ID %d does not exist\n", p_id);
    
    else
    {
        fclose(f);
        char *status_info = read_file(status, 3);
        char *memory_info = read_file(status, 18);
        char *token1 = strtok(status_info, ":\t"); token1 = strtok(NULL, ":\t");
        char *token2 = strtok(memory_info, ":\t\r "); token2 = strtok(NULL, ":\t\r");
        
        char exe_path[2048];
        char *p; 
        //char * p = malloc(sizeof(char) * 2048);
        printf("pid -- %d\nProcess Status -- %sVirtual Memory -- %sExecutable path -- ", p_id, token1, token2); 
        int ret = readlink(exe, exe_path, 1000);
        if(ret == -1)
            printf("No path for executable\n");
        else 
        {
            exe_path[ret] = '\0'; 
            p = strstr(exe_path, HOME);
            if(p)
            {
                //p[strlen(HOME)-1] ='~';
                p += strlen(HOME);
                printf("~%s\n", p);

            }
            else printf("~%s\n", exe_path);
        }

        free(status_info);
        free(memory_info);
    } 


    free(status);
    free(exe);
}