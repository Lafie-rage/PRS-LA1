/* =============================================================================== */
/*                                                                                 */
/* tube_cli_n1.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Custom librairies
#define NAMED
#include "tp5_pipe.h"

#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

void getMsgFromUser(char *buffer);

int main(void) {
  /* TODO :
    - Ouvre le tube nommé
    - Lit le message dedans
    - S'éteind
  */

  int fifoFd;
  char buffer[MAX_MSG_SIZE];

  // Open & write in fifo //
  CHECK(fifoFd = open(FIFO_PATHNAME, O_RDWR), "--- CLIENT : Problem while opening FIFO ---");
  puts("CLIENT : FIFO opened");
  do {
    getMsgFromUser(buffer);
    CHECK(write(fifoFd, buffer, sizeof(buffer)), "--- CLIENT : Problem while writing in FIFO ---");
  } while(strcmp(buffer, CLOSE_PIPE_MSG));
  CHECK(close(fifoFd), "--- CLIENT : Problem while closing FIFO ---");
  puts("CLIENT : FIFO closed");
  exit(0);
}

void getMsgFromUser(char *buffer) {
  printf("Entrez un message à envoyé au serveur... (Fin si vous envoyez \"%s\")\n", CLOSE_PIPE_MSG);
  if(fgets(buffer, MAX_MSG_SIZE, stdin) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    fflush(stdin);
  }
}
