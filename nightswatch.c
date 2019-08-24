#include "headers.h"
#include <sys/time.h>
#include <sys/types.h>


void dirty();
void interrupt();

void nightswatch(char **args, int no_args)
{
    int f = 0;
    if(no_args !=4 )
    {
        printf("Kindly give input as `nightswatch -n [seconds] [dirty/interrupt]\n");
        return;
    }

    
    else if(!strcmp(args[3], "dirty"))
        f = 1;
    
    else if(!strcmp(args[3], "interrupt"))
        f = 0;

    else 
    {
        printf("Kindly give input as `nightswatch -n [seconds] [dirty/interrupt]\n");
        return;
    } 

    int n = atoi(args[2]);
    
    if(f==0)
    {
        FILE *foo = fopen("/proc/interrupts", "r");
        if(foo == NULL)
            printf("Can't open /proc/interrupts file\n");

        else
        {
            char *line = read_file("/proc/interrupts", 1);
            printf("%s\n",line);
            free(line);  
            fclose(foo);
        }

    }
    
    while(1)
    {
        fd_set rfds;
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        int retval; FD_ZERO(&rfds); FD_SET(0, &rfds);

        retval = select(1, &rfds, NULL, NULL, &tv);

        if (retval == -1)
            perror("select()");
        
        else if (retval)
        {
            retval = select(1, &rfds, NULL, NULL, &tv);
            //char buffer[2];
            //read(STDIN_FILENO, buffer, 1);
            char c = fgetc(stdin);
            char d = fgetc(stdin);

            if(c == 'q')
                return;
        }
            
        if(f == 0)
            interrupt();
        else dirty();
        sleep(n);   
    }
}

void dirty()
{
    FILE *f = fopen("/proc/meminfo", "r");
    if(f == NULL)
        printf("Can't open /proc/meminfo file\n");

    else
    {
        char *line = read_file("/proc/meminfo", 17);
        printf("%s\n",line);
        free(line);  
    }

    fclose(f);
    return;
}

void interrupt()
{
    FILE *f = fopen("/proc/interrupts", "r");
    if(f == NULL)
        printf("Can't open /proc/interrupts file\n");

    else
    {
        char *line = read_file("/proc/interrupts", 3);
        for(int i=0; i < strlen(line); i++)
        {
            if(line[i]=='I')
            {
                line[i] = '\0';
                break;
            }
        }
        printf("%s\n",line);
        free(line);  
    }

    fclose(f);
    return;
}