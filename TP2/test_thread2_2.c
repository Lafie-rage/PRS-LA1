/* =============================================================================== */
/*                                                                                 */
/* test_thread2_2.c                                                                */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>


void *thread_treatement(void *arg);

int main(int argc, char *argv[]) {
  void *retVal;
  int i,
      nbThread = 0;

  if(argc != 2) {
    puts("Nombre d'arguments incorrects !");
    return 1;
  }


  // On ne prendra pas plus de 99 threads
  if(strlen(argv[1]) == 2)
    nbThread = (argv[1][0] - 48) * 10 + argv[1][1] - 48;
  else
    nbThread = argv[1][0] - 48;

  pthread_t th[nbThread];

  for (i = 0; i < nbThread; i++)
    pthread_create(&th[i], NULL, thread_treatement, &i);

  for (i = 0; i < nbThread; i++)
    pthread_join(th[i], &retVal);


  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *thread_treatement(void *arg) {
  int i = 0;
  int numThread = *(int *)arg;
  struct timespec tim, timrem;
  tim.tv_sec = 0;
  tim.tv_nsec = 100 * 1000000;

  while (1) {
    nanosleep(&tim, &timrem);
    printf("Numero de thread %d.\nValeur actuelle : %d.\n", numThread, i++);
  }

  pthread_exit(EXIT_SUCCESS);
}
