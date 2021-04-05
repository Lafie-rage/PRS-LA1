/* =============================================================================== */
/*                                                                                 */
/* barbier_02.c                                                                    */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t waitingRoom;

void *thread_loop(void *arg);

int main(void) {
  pthread_t th;
  void *ret;
  int nbClients = 0;
  sem_init(&waitingRoom, PTHREAD_PROCESS_SHARED, 8);
  while(1) {
    int c = getchar();
    if(c == '\n') {
      puts("Creation d'un thread");
      pthread_create(&th, NULL, thread_loop, &nbClients);
    }
  }
  sem_destroy(&waitingRoom);
  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *thread_loop(void *nbClients) {
  sem_wait(&waitingRoom);
  (*(int *)nbClients)++;
  printf("Un client est entré !\nIl y a %d client(s) en salle d'attente.\n", *(int *)nbClients);
  int duration = rand() % 5;
  sleep(duration);
  sem_post(&waitingRoom);
  (*(int *)nbClients)--;
  printf("Un client est sortie !\nIl y a %d client(s) en salle d'attente.\n", *(int *)nbClients);
  pthread_exit(0);
}
