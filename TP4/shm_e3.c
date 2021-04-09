/* =============================================================================== */
/*                                                                                 */
/* shm_e3.c                                                                        */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define SHM_SIZE 101
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}

void filsBehavior(int id, int shmId);

int main(int argc, char *argv[]) {
  /*
   * TODO : Ecrire un programme shm_e4.c qui vous
   * garantit que le dernier processus écrivant dans le segment de mémoire partagé a le dernier mot
   * ( mais on ne choisit pas qui aura le dernier mot )!
   */
  struct shmid_ds shmBuffer;
  int shmId, i, pidFils, pidFils2, status;
  char *shmPtr; // pointer vers mémoire partagée
  // Création du segement //
  // 101 pour \0 en 101ème position
  CHECK(shmId = shmget(ftok(argv[0], 1), SHM_SIZE * sizeof(char), 0666| IPC_CREAT | IPC_EXCL), " --- Problème création mémoire partagée --- ");
  puts("---> On a créé la mémoire partagée");
  switch (pidFils = fork()) {
    case -1: // error
      perror(" --- Erreur création processus fils --- ");
      exit(-1);
      break;
    case 0: // Fils 1
      filsBehavior(1, shmId);
      break;
    default:
      switch (pidFils2 = fork()) {
        case -1: // error
          perror(" --- Erreur création processus fils --- ");
          exit(-1);
          break;
        case 0: // Fils 2
          filsBehavior(2, shmId);
          break;
        default: // Père
           waitpid(pidFils, &status, 0);
           waitpid(pidFils2, &status, 0);
           // Link avec le processus courrant //
           // On veut juste lire don on devrait être en mode readonly
           // Or avant de supprimer le segment on veut le vider, donc on ouvre en mode lecture/écriture
           CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "PERE : -- Problème linkage mémoire partagée au processus --- ");
           puts("PERE : ---> On a linké la mémoire partagée");
           printf("PERE : \t\t\tSHMD ID : %d\n", shmId);
           CHECK(shmctl(shmId, IPC_STAT, &shmBuffer), "PERE : --- Problème récupération shmid_ds --- ");
           puts("PERE : ---> On a récupéré les info de la mémoire partagée");
           // Lecture valeur //
           printf("PERE : Contenu de la mémoire partagée après écriture des fils : \n\t\"%s\"\n", shmPtr);
           // Suppression //
           // On vide le contenu
           for(i = 0; i < SHM_SIZE; i++) {
             *(shmPtr+i) = '\0';
           }
           printf("PERE : Contenu de la mémoire partagée après vidage : \n\t\"%s\"\n", shmPtr);
           CHECK(shmctl(shmId, IPC_RMID, &shmBuffer) ,"PERE : --- Problème suppression de la mémoire partagée --- ");
           puts("PERE : ---> On a supprimé le segment de la mémoire partagée");
           // Détachement de la mémoire partagée //
           CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
           puts("---> On a unlinké la mémoire partagée");
           break;
      }
      break;
  }
}

void filsBehavior(int id, int shmId) {
  int i;
  char *shmPtr;
  struct timespec tim, timrem;
  tim.tv_sec = 0;
  // Link avec le processus courrant //
  // On veut juste écrire mais on doit forcément lire au minimum donc 0 en mode d'ouverture
  printf("FILS %d :\t\t\tSHMD ID : %d\n", id, shmId);
  CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "FILS 2 : -- Problème linkage mémoire partagée au processus --- ");
  printf("FILS %d : ---> On a linké la mémoire partagée", id);
  // écriture de la valeur //
  for(i = 0; i < 20; i++) {
    *(shmPtr + i) = 'A';
    tim.tv_nsec = (rand() % 100) * 1000000;
    nanosleep(&tim, &timrem);
  }
  printf("FILS %d : ---> On a écrit dans la mémoire partagée", id);
  // Détachement de la mémoire partagée //
  CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
  printf("FILS %d : ---> On a unlinké la mémoire partagée", id);
  printf("FILS %d : ---> FIN", id);
}
