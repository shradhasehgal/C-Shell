#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>

#define EXIT_FAILURE 1
char HOST[256], USER[256], CWD[2048], HOME[2048];
int no;