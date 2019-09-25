#include <stdio.h>
#include <sys/time.h>
#include <event.h>

void say_hello(int fd, short event, void *arg)
{
  printf("Hello\n");
}

int main(int argc, const char* argv[])
{
  struct event ev;
  struct timeval tv;

  tv.tv_sec = 3;
  tv.tv_usec = 0;

  event_init();
  evtimer_set(&ev, say_hello, NULL);
  evtimer_add(&ev, &tv);
  event_dispatch();

  return 0;
}