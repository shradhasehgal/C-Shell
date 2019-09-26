#include "headers.h"

void job()
{
    char *status = malloc(sizeof(char) *(40));
    for(int i=0; i < back_g; i++)
    {
        sprintf(status,"/proc/%d/status", jobs[i].PID);
        FILE *f;
        if(!(f = fopen(status, "r")))
            perror("Error");
    
        else
        {
            fclose(f);
            char *status_info = read_file(status, 3);
            char *temp = status_info;
            status_info = strtok(status_info, " :\n\t\r");
            status_info = strtok(NULL, " :\n\t\r");

            if(status_info[0] == 'T')
                strcpy(status_info, "Stopped");
            
            else strcpy(status_info, "Running");
        
            printf("[%d] %s %s [%d]\n",i+1, status_info, jobs[i].job_name, jobs[i].PID);
            free(temp);
            
        }
    }
    free(status);
}