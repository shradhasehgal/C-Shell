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
            switch(status_info[0])
            {
                case 'R': strcpy(status_info, "Running"); break;
                case 'D': strcpy(status_info, "Sleeping (uninterruptible)"); break;
                case 'S': strcpy(status_info, "Sleeping (interruptible)"); break;
                case 'T': strcpy(status_info, "Stopped"); break;
                case 'Z': strcpy(status_info, "Defunct (Zombie)"); break;
            }
            printf("[%d] %s %s [%d]\n",i+1, status_info, jobs[i].job_name, jobs[i].PID);
            free(temp);
            
        }
    }
    free(status);
}