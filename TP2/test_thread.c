/* =============================================================================== */
/*                                                                                 */
/* test_thread.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "time.h"

#define NB_FORKS 50000

void *do_nothing(void *arg) {
  int i;
  i=0;
  pthread_exit(EXIT_SUCCESS);
}

int main(void) {
  time_t t1,t2;
  time(&t1);
  pthread_t th;
  void *ret;
  int j;

  printf("Debut du programme test_thread %ld \n",t1);
  for (j=0;j < NB_FORKS; j++)
    pthread_create(&th, NULL, do_nothing, ret);

  for (j=0;j < NB_FORKS; j++)
    pthread_join(th, &ret);

  time(&t2);
  printf("Fin du programme test_thread %ld \n",t2);
  printf("Durée du programme %ld \n",(t2-t1));

  return EXIT_SUCCESS;
}
