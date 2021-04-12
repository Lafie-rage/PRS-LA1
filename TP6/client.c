/* =============================================================================== */
/*                                                                                 */
/* client.c                                                                        */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

/***************************************************************************************/
/*                                  CUSTOM LIBRAIRIES                                  */
/***************************************************************************************/
#include "tp6.h"

// Open shm & pipe
void initConnection(t_communication_info *comInfo, int dailyKey);

// Send connection message to serveur
void connectToServer(t_communication_info *comInfo);

// Close shm & pipe
void endCommunication(int argc, void *argv);

int main(int argc, char *argv[]) {
  if(argc != 2) {
    perror("ERROR : Cannot open without the server's daily key. Please run the program as follow : ./[build/]client <serverDailyKey>");
    exit(-1);
  }
  t_communication_info comInfo;
  int dailyKey = atoi(argv[1]);

  on_exit(endCommunication, &comInfo);

  initConnection(&comInfo, dailyKey);

  connectToServer(&comInfo);

  return 0;
}

void initConnection(t_communication_info *comInfo, int dailyKey) {
  // Open pipe as write only
  CHECK(comInfo->fifoFd = open(PIPE_PATH, O_WRONLY), "--- ERROR : Cannot open FIFO");
  puts("Connected to pipe");
  // Open the shared memory
  CHECK(comInfo->shmId = shmget(ftok(SHM_PATH, dailyKey), SHM_SIZE * sizeof(char), 0666), "--- ERROR : Cannot open shared memory");
  CHECK(*(comInfo->shmPtr = shmat(comInfo->shmId, NULL, 0)), "ERROR : Cannot link to shm");
  puts("Connected to shm");
  // retieve info
  CHECK(shmctl(comInfo->shmId, IPC_STAT, &(comInfo->shmBuffer)), "--- ERROR : Cannot retrieve informations from shm");
}

void endCommunication(int argc, void *argv) {
  t_communication_info *comInfo = (t_communication_info *)argv;
  if(comInfo->fifoFd != -1) {
    CHECK(close(comInfo->fifoFd), "ERROR : Cannot close FIFO");
  }
  if(comInfo->shmId != -1) {
    CHECK(shmdt(comInfo->shmPtr), " --- ERROR : Cannot unlink to shm");
  }
}

void connectToServer(t_communication_info *comInfo) {

}
