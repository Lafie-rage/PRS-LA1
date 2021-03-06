/* =============================================================================== */
/*                                                                                 */
/* tube_srv_n1.c                                                                   */
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
    - Crée le tube nommé
    - Ecrit un message dedans
    - Attend quelques secondes
    - S'éteind
  */

  int fifoFd;

  // Create fifo //
  CHECK(mkfifo(FIFO_PATHNAME, 0666), "--- SERVER : Problem while creating FIFO ---");

  // Open & write in fifo //
  CHECK(fifoFd = open(FIFO_PATHNAME, O_RDWR), "--- SERVER : Problem while opening FIFO ---");
  puts("SERVER : FIFO opened");
  CHECK(write(fifoFd, MSG_TO_SEND, sizeof(MSG_TO_SEND)), "--- SERVER : Problem while writing in FIFO ---");
  puts("SERVER : Message send");
  sleep(5);
  CHECK(close(fifoFd), "--- SERVER : Problem while closing FIFO ---");
  puts("SERVER : FIFO closed");
  exit(0);
}
