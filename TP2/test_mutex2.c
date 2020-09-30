/* =============================================================================== */
/*                                                                                 */
/* test_mutex2.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cmp = 0;
pthread_mutex_t mutexCmp = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cmpMustBePrinted = PTHREAD_COND_INITIALIZER;

void *increment(void *arg);
void *print(void *arg);

int main (void) {
  pthread_t th1,
            th2;
  void *retVal;


  pthread_create(&th1, NULL, increment, NULL);
  pthread_create(&th2, NULL, print, NULL);

  pthread_join(th1, &retVal);

  return(EXIT_SUCCESS);
}

void *increment(void *arg) {
  while(cmp < 20) {
    cmp += rand()%10;
    printf("Compteur a %d\n", cmp);
  }
  pthread_cond_signal(&cmpMustBePrinted);
  pthread_exit(EXIT_SUCCESS);
}

void *print(void *arg) {
  pthread_cond_wait(&cmpMustBePrinted, &mutexCmp);
  puts("Le compteur a depasse 20");
  pthread_exit(EXIT_SUCCESS);
}
