/* =============================================================================== */
/*                                                                                 */
/* q3.c                                                                            */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */


/* CONSTANTS */
#define NB_PROC 10
#define SEM_NAME "mySem"

void loop();

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
  sem_t* mySem = sem_open(SEM_NAME, O_CREAT, O_RDWR, nbAccesResCrit);
  int i, pidFils;
  for(i = 0; i < NB_PROC; i++) {
      pidFils = fork();
      switch (pidFils) {
        case -1: // Error
          break;
        case 0: // Child
          loop();
          break;
        default: // Father
          waitpid(pidFils, EXIT_SUCCESS, 1);
          break;
      }
  }
  sem_destroy(mySem);
  return EXIT_SUCCESS;
}

/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void loop() {
  int i, nbLoop = rand() % 10;
  for(i = 0; i < nbLoop; i++) {
    sem_open(SEM_NAME, O_CREAT | O_EXCL); // Create or link to the semaphore if it exists
    printf("Je suis le processus %d, je suis à l'éxecution n°%d/%d de mon traitement critique\n", getpid(), i+1, nbLoop);
    sleep(rand() % 5);
    sem_unlink(SEM_NAME);
    printf("Je suis le processus %d, je viens de finir l'éxecution n°%d/%d de mon traitement critique\n", getpid(), i, nbLoop);
  }
}
