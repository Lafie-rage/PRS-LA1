/* =============================================================================== */
/*                                                                                 */
/* test_thread2_1.c                                                                */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PARAM 5

void *thread_treatement(void *arg) {

  printf("La valeur passee dans le thread est %d\n", *(int *)arg);
  pthread_exit(EXIT_SUCCESS);
}

int main(void) {
  pthread_t th;
  void *retVal;
  int val = PARAM;

  pthread_create(&th, NULL, thread_treatement, &val);
  pthread_join(th, &retVal);

  return EXIT_SUCCESS;
}
