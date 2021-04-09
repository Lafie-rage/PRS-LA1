/* =============================================================================== */
/*                                                                                 */
/* tube_1.c                                                                       */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define MSG_TO_SEND "Ceci est un message"
#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

int main(void) {
  /* TODO :
    - Créer pipe
    - Créer fils

    Fils :
      - Ecrit dans pipe

    Père :
      - Attend fin fils
      - Lit dans pipe
  */
  int childPid, status;
  int pipeFd[2];
  char buffer[strlen(MSG_TO_SEND)];
  CHECK(pipe(pipeFd), "--- Problem while creating pipe ---");
  switch (childPid = fork()) {
    case -1:
      perror("--- Problem while creating child ---");
      exit(-1);
    case 0: // Child
      close(pipeFd[0]);
      puts("-> CHILD : Reading fd close");
      write(pipeFd[1], MSG_TO_SEND, sizeof(buffer));
      puts("-> CHILD : Message sent");
      close(pipeFd[1]);
      puts("-> CHILD : Writing fd close");
      puts("-> CHILD : End...");
      exit(0);
    default: // Main processus
      waitpid(childPid, &status, 0);
      close(pipeFd[1]);
      puts("MAIN : Writing fd close");
      read(pipeFd[0], buffer, sizeof(buffer));
      printf("MAIN : Message from child : \"%s\"\n", buffer);
      close(pipeFd[0]);
      puts("MAIN : Writing fd close");
      puts("MAIN : End...");
  }
}
