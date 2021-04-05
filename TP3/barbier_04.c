/* =============================================================================== */
/*                                                                                 */
/* barbier_04.c                                                                    */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t waitingRoom;
sem_t barberSeat;
sem_t clientSaysHi;
sem_t clientSaysGoodBy;
sem_t safeDisplay;

typedef struct {
  int awaiting;
  int out;
} clients_t;

pthread_mutex_t mutex_clients = PTHREAD_MUTEX_INITIALIZER;
void *barber_loop(void *arg);
void *client_loop(void *arg);
void safePrintf(const char* format, int value);
void safePuts(const char *s);

int main(void) {
  pthread_t clients,
            barber;
  void *ret;
  clients_t nbClients;
  nbClients.awaiting = 0;
  nbClients.out = 0;
  sem_init(&barberSeat, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&clientSaysHi, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&clientSaysGoodBy, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&waitingRoom, PTHREAD_PROCESS_SHARED, 8);
  sem_init(&safeDisplay, PTHREAD_PROCESS_SHARED, 1);
  pthread_create(&barber, NULL, barber_loop, NULL);
  while(1) {
    int c = getchar();
    if(c == '\n') {
      safePuts("Creation d'un thread");
      pthread_create(&clients, NULL, client_loop, &nbClients);
    }
  }
  sem_destroy(&waitingRoom);
  sem_destroy(&clientSaysHi);
  sem_destroy(&barberSeat);
  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *client_loop(void *clients) {
  pthread_mutex_lock(&mutex_clients);
  (*(clients_t *)clients).out++;
  pthread_mutex_unlock(&mutex_clients);
  sem_wait(&waitingRoom);
  pthread_mutex_lock(&mutex_clients);
  (*(clients_t *)clients).out--;
  pthread_mutex_unlock(&mutex_clients);
  pthread_mutex_lock(&mutex_clients);
  (*(clients_t *)clients).awaiting++;
  pthread_mutex_unlock(&mutex_clients);
  int isBarberWorking;
  safePrintf("Un client est entré !\nIl y a %d client(s) en salle d'attente.\n", (*(clients_t *)clients).awaiting);
  safePrintf("Il y a %d clients qui attendent dehors", (*(clients_t *)clients).out);
  sem_post(&clientSaysHi);
  sem_wait(&barberSeat);
  sem_post(&waitingRoom);
  pthread_mutex_lock(&mutex_clients);
  (*(clients_t *)clients).awaiting--;
  pthread_mutex_unlock(&mutex_clients);
  safePrintf("Un client est sortie !\nIl y a %d client(s) en salle d'attente.\n", (*(clients_t *)clients).awaiting);
  safePrintf("Il y a %d clients qui attendent dehors", (*(clients_t *)clients).out);
  sem_wait(&clientSaysGoodBy);
  safePuts("\tClient : Thanks a lot, see you soon my friend ! :)");
  sem_post(&barberSeat);
  safePuts("Le client quite le salon");
  pthread_exit(0);
}

void *barber_loop(void *arg) {
  int nbClients;
  while(1) {
    sem_wait(&clientSaysHi);
    safePuts("\tBarber : Hello there, come to get your new hair cut ! :)");
    sem_post(&barberSeat);
    sleep(rand() % 5);
    safePuts("\tBarber : Look how beautiful you are ! See you soon !");
    sem_post(&clientSaysGoodBy);
  }
}

void safePrintf(const char* format, int value) {
  sem_wait(&safeDisplay);
  printf(format, value);
  sem_post(&safeDisplay);
}

void safePuts(const char* s) {
  sem_wait(&safeDisplay);
  puts(s);
  sem_post(&safeDisplay);
}
