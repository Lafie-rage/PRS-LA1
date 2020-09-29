/* =============================================================================== */
/*                                                                                 */
/* test_fork.c                                                                     */
/* Auteur : I Le Glaz                                                              */
/* =============================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "time.h"
#define NB_FORKS 50000
void do_nothing() {
  int i;
  i=0;
  exit(EXIT_SUCCESS);
}
/* =============================================================================== */
int main(int argc, char *argv[]) {
  time_t t1,t2;
  time(&t1);
  printf("Debut du programme test_fork %ld \n",t1);
  int pid,j,status;
  for (j=0;j < NB_FORKS; j++) {
	switch (pid = fork()) {
             case -1 :
		perror("fork()");
                exit(EXIT_FAILURE);
             case 0 : /* Code du processus fils */
                do_nothing();
		break;
             default: /* Code du processus pere */
                waitpid(pid,&status,0);
                break;
         }
  }
  time(&t2);
  printf("Fin du programme test_fork %ld \n",t2);
  printf("Durée du programme %ld \n",(t2-t1));

  return EXIT_SUCCESS;
}
