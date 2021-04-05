/* =============================================================================== */
/*                                                                                 */
/* barbier_01.c                                                                    */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void *thread_loop(void *arg);

int main(void) {
  pthread_t th;
  void *ret;
  int thread_index = 0;
  while(1) {
    int c = getchar();
    if(c == '\n') {
      puts("Creation d'un thread");
      pthread_create(&th, NULL, thread_loop, &thread_index);
      thread_index++;
    }
  }
  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *thread_loop(void *arg) {
  int index = *(int *)arg;
  int duration = rand() % 5;
  sleep(duration);
  printf("Thread %d terminé\n", index);
  pthread_exit(0);
}
