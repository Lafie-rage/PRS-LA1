#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(void) {
  int childPid = fork();
  if(childPid == 0) {
    printf("Je suis le processus fils, mon pid est %d, celui de mon père est %d\n", getpid(), getppid());
    int *ptr_ppid;
    *ptr_ppid = getppid();
    wait(ptr_ppid);
  }
  else
    printf("Je suis le processus père, mon pid est %d, celui de mon fils est %d\n", getpid(), childPid);
  while(1);
}
