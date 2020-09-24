#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CHECK(sts, msg) if ((sts) == -1) {perror(msg);exit(-1);}

int main(void) {
  CHECK(fork(), "Ne peut pas créer un nouveau processus");
  CHECK(fork(), "Ne peut pas créer un nouveau processus");
  printf("Je suis le processus %d, mon père est le %d\n", getpid(), getppid());
  return 0;
}
