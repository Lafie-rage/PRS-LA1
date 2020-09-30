/* =============================================================================== */
/*                                                                                 */
/* test_mutex1.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS 10

pthread_mutex_t mutex1;

void *thread_treatement (void * arg);

int main(void) {
  pthread_t threads[NB_THREADS];
  char i = 0;
  void *retVal_threads[NB_THREADS];

  for (i = 0; i < NB_THREADS; i++) {
    pthread_create(&(threads[i]), NULL, thread_treatement, (void *)i);
  }

  for (i = 0; i < NB_THREADS; i++) {
    pthread_join(threads[i], &retVal_threads[i]);
  }

  return EXIT_SUCCESS;
}

void *thread_treatement (void *arg) {
  int i = 0;
  int j;
  int result = 0;
  int nb_iter = rand()%10;
  int threadNb = (int)(arg);

  printf("Thread %d fera %d tour de boucle\n", threadNb, nb_iter);

  for (; i < nb_iter; i++) {
    pthread_mutex_lock(&mutex1);
    printf("Debut calcul thread %d\n", threadNb);
    for (j = 0; j < 10; j++) {
      result += 30 * rand()%100;
    }
    printf("Fin calcul thread %d\n", threadNb);
    pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(EXIT_SUCCESS);
}
