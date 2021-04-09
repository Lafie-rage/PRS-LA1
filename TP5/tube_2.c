/* =============================================================================== */
/*                                                                                 */
/* tube_2.c                                                                       */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

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

    Père :
      Tant que message reçu pas AU REVOIR
      - Lit dans pipe
  */
  int childPid, status;
  int pipeFd[2];
  char buffer[MAX_MSG_SIZE];
  CHECK(pipe(pipeFd), "--- Problem while creating pipe ---");
  switch (childPid = fork()) {
    case -1:
      perror("--- Problem while creating child ---");
      exit(-1);
    case 0: // Child
      close(pipeFd[0]);
      puts("-> CHILD : Reading fd close");
      do {
        getMsgFromUser(buffer);
        write(pipeFd[1], buffer, sizeof(buffer));
        puts("-> CHILD : Message sent");
      } while(strcmp(buffer, CLOSE_PIPE_MSG));
      close(pipeFd[1]);
      puts("-> CHILD : Writing fd close");
      puts("-> CHILD : End...");
      exit(0);
    default: // Main processus
      close(pipeFd[1]);
      while(1) {
        puts("MAIN : Writing fd close");
        do {
          read(pipeFd[0], buffer, sizeof(buffer));
        } while(buffer[0] == EOF);
        printf("MAIN : Message from child : \"%s\"\n", buffer);
        if(!strcmp(buffer, CLOSE_PIPE_MSG))
          break;
      }
      close(pipeFd[0]);
      puts("MAIN : Writing fd close");
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
