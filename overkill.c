#include "headers.h"

void overkill()
{
    for(int i=0; i < back_g; i++)
        kill(jobs[i].PID, 9);

    return;
}