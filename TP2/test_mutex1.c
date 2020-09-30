/* =============================================================================== */
/*                                                                                 */
/* test_mutex1.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS 10

void *thread_treatement (void * arg);

int main(void) {
  pthread_t threads[NB_THREADS];
  int i = 0;
  void *retVal_threads[NB_THREADS];

  for (; i < NB_THREADS; i++) {
    pthread_create(threads[i], NULL, thread_treatement, (void *)i);
  }

  for (i = 0; i < NB_THREADS; i++) {
    pthread_join(threads[i], retVal_threads[i]);
  }

  return EXIT_SUCCESS;
}

void *thread_treatement (void *arg) {
  int threadNb = (int)arg;
  
  pthread_exit(EXIT_SUCCESS);
}
