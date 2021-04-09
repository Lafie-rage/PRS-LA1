/* =============================================================================== */
/*                                                                                 */
/* shm_e2.c                                                                        */
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

#define SHM_SIZE 101
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}

int main(int argc, char *argv[]) {
  /* TODO :
   * Ecrire un programme shm_e2.c qui complète le programme
   * shm_e1.c en réalisant les opérations suivantes :
   * Le programme crée un fils,le fils écrit dans la mémoire partagée et meurt.
   * Le père attend la mort de son fils, lit dans la mémoire partagée et affiche le message du fils.
  */
  struct shmid_ds shmBuffer;
  int shmId, i, pidFils, status;
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
    case 0: // Fils
        // Link avec le processus courrant //
        // On veut juste écrire mais on doit forcément lire au minimum donc 0 en mode d'ouverture
        CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "FILS : -- Problème linkage mémoire partagée au processus --- ");
        puts("FILS : ---> On a linké la mémoire partagée");
        // écriture de la valeur //
        strcpy(shmPtr, "Une très longue chaine qui ne fait surement pas 100 caractère mais on essaye de s'en approcher");
        puts("FILS : ---> On a écrit dans la mémoire partagée");
        // Détachement de la mémoire partagée //
        CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
        puts("FILS : ---> On a unlinké la mémoire partagée");
        puts("FILS : ---> FIN");
      break;
    default:
      waitpid(pidFils, &status, 0);
      // Link avec le processus courrant //
      // On veut juste lire don on devrait être en mode readonly
      // Or avant de supprimer le segment on veut le vider, donc on ouvre en mode lecture/écriture
      CHECK(*(shmPtr = shmat(shmId, NULL, 0)), "PERE : -- Problème linkage mémoire partagée au processus --- ");
      puts("PERE : ---> On a linké la mémoire partagée");
      CHECK(shmctl(shmId, IPC_STAT, &shmBuffer), "PERE : --- Problème récupération shmid_ds --- ");
      puts("PERE : ---> On a récupéré les info de la mémoire partagée");
      // Lecture valeur //
      printf("PERE : Contenu de la mémoire partagée après écriture du fils : \n\t\"%s\"\n", shmPtr);
      // Suppression //
      // On vide le contenu
      for(i = 0; i < SHM_SIZE; i++) {
        *(shmPtr+i) = '\0';
      }
      printf("PERE : Contenu de la mémoire partagée après vidage : \n\t\"%s\"\n", shmPtr);
      CHECK(shmctl(shmId, IPC_RMID, &shmBuffer) ,"PERE : --- Problème suppression de la mémoire partagée --- ");
      puts("PERE : ---> On a supprimé le segment de la mémoire partagée");
      break;
      // Détachement de la mémoire partagée //
      CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
      puts("---> On a unlinké la mémoire partagée");
  }
}
