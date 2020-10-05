/* =============================================================================== */
/*                                                                                 */
/* test_mutex3.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexCondition = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t oneThreadHasFinish = PTHREAD_COND_INITIALIZER;


void *thread_calcul_treatement (void * arg);
void *thread_awaiting_treatement (void *arg);

int main(void) {
  pthread_t threads_calcul[NB_THREADS],
            thread_awaiting;
  char i = 0;
  void *retVal_threads_calcul[NB_THREADS],
       *retVal_thread_awaiting;

  // On lance le thread en attente avant, afin d'être sûr que tous les threads n'aient pas encore finit leur exécution avant le wait...
  pthread_create(&thread_awaiting, NULL, thread_awaiting_treatement, NULL);
  for (i = 0; i < NB_THREADS; i++) {
    pthread_create(&(threads_calcul[i]), NULL, thread_calcul_treatement, (void *)i);
  }


  pthread_join(thread_awaiting, &retVal_thread_awaiting);
  for (i = 0; i < NB_THREADS; i++) {
    pthread_join(threads_calcul[i], &retVal_threads_calcul[i]);
  }

  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *thread_calcul_treatement (void *arg) {
  int i = 0;
  int j;
  int result = 0;
  int nb_iter = rand()%10;
  int threadNb = (int)(arg);

  printf("Thread %d fera %d tour de boucle\n", threadNb, nb_iter);

  for (; i < nb_iter; i++) {
    pthread_mutex_lock(&mutex1);
    // Pour améliorer la lisibilité, on retire les printfs...
    //printf("Debut calcul thread %d\n", threadNb);
    for (j = 0; j < 10; j++) {
      result += 30 * rand()%100;
    }
    //printf("Fin calcul thread %d\n", threadNb);
    pthread_mutex_unlock(&mutex1);
  }

  pthread_cond_signal(&oneThreadHasFinish);

  pthread_exit(EXIT_SUCCESS);
}


void *thread_awaiting_treatement (void *arg) {
  pthread_cond_wait(&oneThreadHasFinish, &mutexCondition);

  puts("Un thread a termine son execution");

  return EXIT_SUCCESS;

}
