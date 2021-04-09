/* =============================================================================== */
/*                                                                                 */
/* shm_e1.c                                                                        */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 101
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}

int main(int argc, char *argv[]) {
  /* TODO :
   * Ecrire un programme shm_e1.c qui crée un
   * segment de mémoire partagée, dans lequel
   * il stocke une chaîne de caractères de 100
   * caractères maximum, et affiche toutes les
   * informations connues sur ce segment de
   * mémoire partagée, puis détruit le segment
   * de mémoire partagée.
  */
  struct shmid_ds shmBuffer;
  int shmId, i;
  char *shmPtr; // pointer vers mémoire partagée
  // Création du segement //
  // 101 pour \0 en 101ème position
  CHECK(shmId = shmget(ftok(argv[0], 1), SHM_SIZE * sizeof(char), 0666| IPC_CREAT | IPC_EXCL), " --- Problème création mémoire partagée --- ");
  puts("---> On a créé la mémoire partagée");
  // Link avec le processus courrant //
  // On veut lire & écrire donc 0 en mode d'ouverture
  CHECK(*(shmPtr = shmat(shmId, NULL, 0)), " -- Problème linkage mémoire partagée au processus --- ");
  puts("---> On a linké la mémoire partagée");
  CHECK(shmctl(shmId, IPC_STAT, &shmBuffer), " --- Problème récupération shmid_ds --- ");
  puts("---> On a récupéré les info de la mémoire partagée");
  // Lecture/écriture valeur //
  strcpy(shmPtr, "Une très longue chaine qui ne fait surement pas 100 caractère mais on essaye de s'en approcher");
  puts("---> On a écrit dans la mémoire partagée");
  printf("Contenu de la mémoire partagée après écriture: \n\t\"%s\"\n", shmPtr);
  puts("Info sur le ségment :");
  puts("\tPermissions :");
  printf("\t\t__key : %d\n", shmBuffer.shm_perm.__key);
  printf("\t\tuid : %d\n", shmBuffer.shm_perm.uid);
  printf("\t\tgid : %d\n", shmBuffer.shm_perm.gid);
  printf("\t\tcuid : %d\n", shmBuffer.shm_perm.cuid);
  printf("\t\tcgid : %d\n", shmBuffer.shm_perm.cgid);
  printf("\t\tmode : %d\n", shmBuffer.shm_perm.mode);
  printf("\t\t__seq : %d\n", shmBuffer.shm_perm.__seq);
  printf("\tshm_segsz : %ld\n", shmBuffer.shm_segsz);
  printf("\tshm_atime : %ld\n", shmBuffer.shm_atime);
  printf("\tshm_dtime : %ld\n", shmBuffer.shm_dtime);
  printf("\tshm_ctime : %ld\n", shmBuffer.shm_ctime);
  printf("\tshm_cpid : %d\n", shmBuffer.shm_cpid);
  printf("\tshm_lpid : %d\n", shmBuffer.shm_lpid);
  printf("\tshm_nattch : %ld\n", shmBuffer.shm_nattch);

  // Suppression //
  // On vide le contenu
  for(i = 0; i < SHM_SIZE; i++) {
    *(shmPtr+i) = '\0';
  }
  printf("Contenu de la mémoire partagée après vidage : \n\t\"%s\"\n", shmPtr);
  CHECK(shmctl(shmId, IPC_RMID, &shmBuffer) ," --- Problème suppression de la mémoire partagée --- ");
  puts("---> On a supprimé le segment de la mémoire partagée");
  // Détachement de la mémoire partagée
  CHECK(shmdt(shmPtr), " --- Problème delinkage de la mémoire partagée --- ");
  puts("---> On a unlinké la mémoire partagée");
}
