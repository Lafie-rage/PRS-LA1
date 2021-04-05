/* =============================================================================== */
/*                                                                                 */
/* barbier_03.c                                                                    */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t waitingRoom;
sem_t barber_seat;
sem_t client_says_hi;
sem_t client_says_good_by;

void *barber_loop(void *arg);
void *client_loop(void *arg);

int main(void) {
  pthread_t clients,
            barber;
  void *ret;
  int nbClients = 0;
  sem_init(&barber_seat, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&client_says_hi, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&client_says_good_by, PTHREAD_PROCESS_SHARED, 0);
  sem_init(&waitingRoom, PTHREAD_PROCESS_SHARED, 8);
  pthread_create(&barber, NULL, barber_loop, NULL);
  while(1) {
    int c = getchar();
    if(c == '\n') {
      puts("Creation d'un thread");
      pthread_create(&clients, NULL, client_loop, &nbClients);
    }
  }
  sem_destroy(&waitingRoom);
  sem_destroy(&client_says_hi);
  sem_destroy(&barber_seat);
  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *client_loop(void *nbClients) {
  sem_wait(&waitingRoom);
  (*(int *)nbClients)++;
  int isBarberWorking;
  printf("Un client est entré !\nIl y a %d client(s) en salle d'attente.\n", *(int *)nbClients);
  sem_post(&client_says_hi);
  sem_wait(&barber_seat);
  sem_post(&waitingRoom);
  (*(int *)nbClients)--;
  printf("Un client est sortie !\nIl y a %d client(s) en salle d'attente.\n", *(int *)nbClients);
  sem_wait(&client_says_good_by);
  puts("\tClient : Thanks a lot, see you soon my friend ! :)");
  sem_post(&barber_seat);
  puts("Le client quite le salon");
  pthread_exit(0);
}

void *barber_loop(void *arg) {
  int nbClients;
  while(1) {
    sem_wait(&client_says_hi);
    puts("\tBarber : Hello there, come to get your new hair cut ! :)");
    sem_post(&barber_seat);
    sleep(rand() % 5);
    puts("\tBarber : Look how beautiful you are ! See you soon !");
    sem_post(&client_says_good_by);
  }
}
