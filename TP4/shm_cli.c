/* =============================================================================== */
/*                                                                                 */
/* shm_cli.c                                                                       */
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
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <fcntl.h>           /* For O_* constants */

#define SHM_SIZE 101
#define SEM_NAME "shm_sem"
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}


int main(void) {
  /*
   * TODO : Le second s’appelle shm_cli.c;
   * il a pour mission d’aller lire le message laissé par shm_srv
   * et de l’afficher.
   */
   struct shmid_ds shmBuffer;
   int shmId, i;
   char *shmPtr; // pointer vers mémoire partagée
   puts("CLIENT : Création de la mémoire partagée");
   CHECK(shmId = shmget(ftok("build/shm_srv", 1), SHM_SIZE * sizeof(char), 0666), " --- Problème création mémoire partagée --- ");
   CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "CLIENT : -- Problème linkage mémoire partagée au processus --- ");
   puts("CLIENT : ---> On a linké la mémoire partagée");
   printf("CLIENT : \t\t\tSHMD ID : %d\n", shmId);
   CHECK(shmctl(shmId, IPC_STAT, &shmBuffer), "CLIENT : --- Problème récupération shmid_ds --- ");
   puts("CLIENT : ---> On a récupéré les info de la mémoire partagée");
   // Ecriture valeur //
   sem_open(SEM_NAME, O_CREAT | O_EXCL); // Create or link to the semaphore if it exists
   printf("%s\n", shmPtr);
   for(i = 0; i < SHM_SIZE; i++) {
    *(shmPtr+i) = '\0';
   }
   printf("Client : Contenu de la mémoire partagée après vidage : \n\t\"%s\"\n", shmPtr);
   sem_unlink(SEM_NAME);
   CHECK(shmctl(shmId, IPC_RMID, &shmBuffer) ,"PERE : --- Problème suppression de la mémoire partagée --- ");
   puts("Client : ---> On a supprimé le segment de la mémoire partagée");
}
