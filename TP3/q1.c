/* =============================================================================== */
/*                                                                                 */
/* q1.c                                                                            */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t mySem;

void *thread_loop(void *arg);

int main(int argc, char *argv[]) {
  if(argc != 2){
    puts("Veuillez entrer en argument le nombre de traitement critique réalisable en même temps uniquement.");
    return -1;
  }
  int nbAccesResCrit = atoi(argv[1]);
  if(nbAccesResCrit <= 0) {
    puts("L'argument doit être un entier.");
    return -2;
  }
  sem_init(&mySem, PTHREAD_PROCESS_SHARED, nbAccesResCrit);
  int i;
  pthread_t th[10];
  void *ret;
  for(i = 0; i < 10; i++) { // Create threads
      pthread_create(&th[i], NULL, thread_loop, &i);
  }

  for(i = 0; i < 10; i++) { // Join threads
      pthread_join(th[10], &ret);
  }
  sem_destroy(&mySem);
  return EXIT_SUCCESS;
}

/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *thread_loop(void *arg) {
  int numThread = *(int *)arg;
  int i, nbLoop = rand() % 10;
  for(i = 0; i < nbLoop; i++) {
    sem_wait(&mySem);
    printf("Je suis le thread n°%d, je suis à l'éxecution n°%d/%d de mon traitement critique\n", numThread, i+1, nbLoop);
    sleep(rand() % 5);
    sem_post(&mySem);
    printf("Je suis le thread n°%d, je viens de finir l'éxecution n°%d/%d de mon traitement critique\n", numThread, i, nbLoop);
  }
  pthread_exit(0);
}
