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

// Custom librairies
#define NAMED
#include "tp5_pipe.h"

#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

int main(void) {
  /* TODO :
    - Ouvre le tube nommé
    - Lit le message dedans
    - S'éteind
  */

  int fifoFd;
  char buffer[MAX_MSG_SIZE];

  // Open & write in fifo //
  CHECK(fifoFd = open(FIFO_PATHNAME, O_WRONLY), "--- CLIENT : Problem while opening FIFO ---");
  puts("CLIENT : FIFO opened");
  CHECK(read(fifoFd, buffer, sizeof(buffer)), "--- CLIENT : Problem while reading in FIFO ---");
  printf("Message from server : \"%s\"\n", buffer);
  CHECK(close(fifoFd), "--- CLIENT : Problem while closing FIFO ---");
  puts("CLIENT : FIFO closed");
  exit(0);
}
