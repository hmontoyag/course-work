/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int pn;

process pra(){
  int32 nc, ns, st;
  sleepms(1000);
  pipesend(pn, 6, "Hello ");
  pipesend(pn, 6, "World");
  st = pipestate(pn, &nc, &ns);
  kprintf("pipestate: %d %d %d\n", st, nc, ns);
}

process prb(){
  pn = pipeopen();
  char msg[12];
  piperecv(pn, 12, msg);
  kprintf("message: %s\n", msg);
  int32 nc, ns, st;
  st = pipestate(pn, &nc, &ns);
  kprintf("pipestate: %d %d %d\n", st, nc, ns);
  pipeclose(pn);
  st = pipestate(pn, &nc, &ns);
  kprintf("pipestate after closing: %d\n", st);
}

process	main(void)
{
  pn = -1;
  resume(create(pra, 2000, 20, "prA", 0));
  resume(create(prb, 2000, 20, "prB", 0));
  return OK;
}
