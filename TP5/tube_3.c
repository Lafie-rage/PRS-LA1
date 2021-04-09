/* =============================================================================== */
/*                                                                                 */
/* tube_3.c                                                                       */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// Custom librairies
#define ANONYMOUS
#include "tp5_pipe.h"

#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

void getMsgFromUser(char *buffer);

int main(void) {
  /* TODO :
    - Créer pipe
    - Créer fils

    Fils :
      Tant que message pas AU REVOIR
      - Demande messages à utilisateur
      - Ecrit dans pipe
      - Attend réponse du père
    Père :
      Tant que message reçu pas AU REVOIR
      - Lit dans pipe
      - Attends 2 sec
      - Répond avec message type
  */
  int childPid, status;
  int pipeFdFromM2C[2]; // From main proc to child
  int pipeFdFromC2M[2]; // From child to main proc
  char buffer[MAX_MSG_SIZE];
  CHECK(pipe(pipeFdFromM2C), "--- Problem while creating pipe ---");
  CHECK(pipe(pipeFdFromC2M), "--- Problem while creating pipe ---");
  switch (childPid = fork()) {
    case -1:
      perror("--- Problem while creating child ---");
      exit(-1);
    case 0: // Child
      close(pipeFdFromC2M[0]);
      close(pipeFdFromM2C[1]);
      puts("-> CHILD : Unused fd close");
      do {
        getMsgFromUser(buffer);
        write(pipeFdFromC2M[1], buffer, sizeof(buffer));
        puts("-> CHILD : Message sent");
        puts("-> CHILD : Waiting for main processus to respond");
        do {
          read(pipeFdFromM2C[0], buffer, sizeof(buffer));
        } while(buffer[0] == EOF);
      } while(strcmp(buffer, CLOSE_PIPE_MSG));
      close(pipeFdFromC2M[1]);
      close(pipeFdFromC2M[1]);
      puts("-> CHILD : Used fd close");
      puts("-> CHILD : End...");
      exit(0);
    default: // Main processus
      close(pipeFdFromC2M[1]);
      close(pipeFdFromM2C[0]);
      while(1) {
        puts("MAIN : Unused fd close");
        do {
          read(pipeFdFromC2M[0], buffer, sizeof(buffer));
        } while(buffer[0] == EOF);
        printf("MAIN : Message from child : \"%s\"\n", buffer);
        sleep(2);
        write(pipeFdFromM2C[1], RESPONS_MSG, sizeof(buffer));
        if(!strcmp(buffer, CLOSE_PIPE_MSG))
          break;
      }
      close(pipeFdFromC2M[0]);
      close(pipeFdFromM2C[1]);
      puts("MAIN : Used fd close");
      puts("MAIN : End...");
  }
}

void getMsgFromUser(char *buffer) {
  printf("Entrez un message à envoyé au serveur... (Fin si vous envoyez \"%s\")\n", CLOSE_PIPE_MSG);
  if(fgets(buffer, MAX_MSG_SIZE, stdin) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    fflush(stdin);
  }
}
