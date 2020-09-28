/* =============================================================================== */
/*                                                                                 */
/* fork_3.1.3.c                                                                     */
/* Auteur : Corentin Destrez                                                       */
/* =============================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
  int childPid = fork();
  if(childPid == 0) {
    printf("Je suis le processus fils, mon pid est %d, celui de mon père est %d\n", getpid(), getppid());
    _exit(0);
  }
  else
    printf("Je suis le processus père, mon pid est %d, celui de mon fils est %d\n", getpid(), childPid);
  while(1);
}
