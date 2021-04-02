/* =============================================================================== */
/*                                                                                 */
/* shm_srv.c                                                                       */
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


int main(int argc, char *argv[]) {
  /*
   * TODO : Le premier s’appelle shm_srv.c;
   * Il réalise les mêmes fonctionnalités que le programme shm_e1.c,
   * mais écrit un message dans le segment de mémoire partagée et
   * attend 30 secondes avant de se terminer.
   */
   struct shmid_ds shmBuffer;
   int shmId;
   char *shmPtr; // pointer vers mémoire partagée
   puts("SERVER : Création de la mémoire partagée");
   CHECK(shmId = shmget(ftok(argv[0], 1), SHM_SIZE * sizeof(char), 0666| IPC_CREAT | IPC_EXCL), " --- Problème création mémoire partagée --- ");
   CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "SERVER : -- Problème linkage mémoire partagée au processus --- ");
   puts("SERVER : ---> On a linké la mémoire partagée");
   printf("SERVER : \t\t\tSHMD ID : %d\n", shmId);
   CHECK(shmctl(shmId, IPC_STAT, &shmBuffer), "SERVER : --- Problème récupération shmid_ds --- ");
   puts("SERVER : ---> On a récupéré les info de la mémoire partagée");
   // Ecriture valeur //
   sem_open(SEM_NAME, O_CREAT | O_EXCL); // Create or link to the semaphore if it exists
   strcpy(shmPtr, "Une très longue chaine qui ne fait surement pas 100 caractère mais on essaye de s'en approcher");
   sem_unlink(SEM_NAME);
   // Détachement de la mémoire partagée //
   CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
   sleep(30);
   puts("SERVER : FIN");
}
