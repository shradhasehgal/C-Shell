#include "headers.h"

int is_hidden(char *filename)
{
    if(filename[0] == '.') return 1;
    else return 0;
}

void long_listing(char *directory, char *filename)
{
    char *filepath = (char *)malloc(sizeof(char) * (strlen(directory) + strlen(filename)+1);
    strcpy(filepath, directory);
    strcpy(filepath, "/");
    strcpy(filepath, filename);

    struct stat name;
    if(stat(filepath, &name) != 0)
        perror("Error");     

    else
    {
        struct group *gr = getgrgid(file_stat.st_gid);
        struct passwd *pwd =  getpwuid(file_stat.st_uid);
        mode_t p = name.st_mode;
        char *mode = malloc(sizeof(char) * 9 + 1);
        mode[0] = (p & S_IRUSR) ? 'r' : '-';
        mode[1] = (p & S_IWUSR) ? 'w' : '-';
        mode[2] = (p & S_IXUSR) ? 'x' : '-';
        mode[3] = (p & S_IRGRP) ? 'r' : '-';
        mode[4] = (p & S_IWGRP) ? 'w' : '-';
        mode[5] = (p & S_IXGRP) ? 'x' : '-';
        mode[6] = (p & S_IROTH) ? 'r' : '-';
        mode[7] = (p & S_IWOTH) ? 'w' : '-';
        mode[8] = (p & S_IXOTH) ? 'x' : '-';
        mode[9] = '\0';
        return mode;
    }
    free(filepath);

}

void ls_out(char *dir_name, int flag, int hidden)
{
    struct dirent **file;
    int n = scandir(dir_name, &file, NULL, alphasort);
    if(n < 0)
    {
        perror("Error");
        return;
    }

    switch(flag)
    {
        case 0:
            for(int i=0; i<n; i++) 
            { 
                if(hidden == 0 && !is_hidden(file[i]->d_name) || hidden == 1)
                    printf("%s\t",file[i]->d_name); 
                free(file[i]); 
            }
            printf("\n");
            free(file);
            break;
    
        case 1:
            for(int i=0; i<n; i++)
            {
                if(hidden == 0 && !is_hidden(file[i]->d_name) || hidden == 1)
                    long_listing(dir_name, file[i]);
                free(file[i]);
            }
            break;
    }
    
}



void ls(char *command)
{
    int f1 = 0;
    char *token = command;

    token = strtok(NULL, " \n\t\r");

    int hidden = 0;
    while (token != NULL)
    {
        if(!strcmp(token,"-l"))
            f1 = 1;
    
        else if(!strcmp(token,"-a"))
            hidden = 1;

        else if(!strcmp(token,"-al") || !strcmp(token,"-la"))
        {   
            f1 = 1, hidden = 1;
        }
        

        else
        {
            char *final_path;
            if(token[0] == '~')
            {
                int n = strlen(token);
                char *temp = (char *)malloc(sizeof(char) *n);
                
                if(n > 1)
                {
                    for(int i=1; i < n; i++)
                        temp[i-1] = token[i];
                }
                
                final_path = (char *)malloc(sizeof(char) *(n + strlen(HOME)));
                strcpy(final_path, HOME);
                strcat(final_path, temp);
                free(temp);
            }

            else final_path = token;
        
            ls_out(final_path, f1, hidden);
        }

        token = strtok(NULL, " \n\t\r");
        
    }
}