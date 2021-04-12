/* =============================================================================== */
/*                                                                                 */
/* server.c                                                                        */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/***************************************************************************************/
/*                                  CUSTOM LIBRAIRIES                                  */
/***************************************************************************************/
#include "tp6.h"

#define MAX_CLIENTS 5

// Init clients list by setting each pid to -1
void initClients(int *clients);

// Create and connect to the shm & pipe.
void setUpConnection(t_communication_info *comInfo, int dailyKey);

// Close shm & pipe
void closeCommunication(int argc, void *argv);

int main(int argc, char *argv[]) {
  if(argc != 2) {
    perror("ERROR : Cannot open without the server's daily key. Please run the program as follow : ./[build/]server <serverDailyKey>");
    exit(-1);
  }
  t_communication_info comInfo;
  int clients[MAX_CLIENTS];
  int dailyKey = atoi(argv[1]);
  initClients(clients);

  initComInfo(&comInfo);

  on_exit(closeCommunication, &comInfo);

  setUpConnection(&comInfo, dailyKey);

  sleep(10);

  return 0;
}

void initClients(int *clients) {
  int i;
  for(i = 0; i < MAX_CLIENTS; i++) {
    clients[i] = -1;
  }
}

void setUpConnection(t_communication_info *comInfo, int dailyKey) {
  CHECK(mkfifo(PIPE_PATH, 0666), "--- ERROR : Cannot create fifo");
  puts("Pipe created");
  // Open pipe as write only
  CHECK(comInfo->fifoFd = open(PIPE_PATH, O_RDWR), "--- ERROR : Cannot open FIFO");
  puts("Connected to pipe");
  // Create the shared memory
  CHECK(comInfo->shmId = shmget(ftok(SHM_PATH, dailyKey), SHM_SIZE * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL), "--- ERROR : Cannot open shared memory");
  puts("Shm created");
  // Connect to shm
  CHECK(*(comInfo->shmPtr = shmat(comInfo->shmId, NULL, 0)), " --- Error : Cannot link to shm");
  // retieve info
  CHECK(shmctl(comInfo->shmId, IPC_STAT, &(comInfo->shmBuffer)), "--- ERROR : Cannot retrieve informations from shm");
}

void closeCommunication(int argc, void *argv) {
  t_communication_info *comInfo = (t_communication_info *)argv;
  if(comInfo->fifoFd != -1) {
    CHECK(close(comInfo->fifoFd), "ERROR : Cannot close FIFO");
    puts("Pipe closed");
  }
  if(comInfo->shmId != -1) {
    CHECK(shmctl(comInfo->shmId, IPC_RMID, &(comInfo->shmBuffer)) ,"--- ERROR : Cannot delete shm");
    puts("Shm closed");
  }
}
