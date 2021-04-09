#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "tp5.h"

#define MSG_KEY 1
#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

// Threads behavior
void *waitReceipt(void *arg);
void *sendRequest(void *arg);

int getMsgFromUser(char *buffer);

int main(void) {
  /* TODO :
  Ouvre la boite aux lettres serveur
  Tant que message différent de CLOSE_CONNECTION_MSG =>
    - lit message utilisateur
    - envoit message au serveur (type 1)
    - lance thread
  */
  int msgId, i;
  key_t key = ftok("/tmp", MSG_KEY);
  char msg[MAX_BODY_MSG_SIZE];
  t_request request;
  pthread_t receiptWaiter;
  pthread_t messageSender;
  request.type = 1;
  request.body.pid = getpid();
  // Cration mail box //
  CHECK(msgId = msgget(key, 0), "--- Problem while retrieving mailbox ---");
  pthread_create(&receiptWaiter, NULL, waitReceipt, &msgId);
  pthread_create(&messageSender, NULL, sendRequest, &msgId);
  pthread_join(receiptWaiter, NULL);
  pthread_join(messageSender, NULL);
}

void *waitReceipt(void *arg) {
  /* TODO :
    Attend accusé de réception du serveur
    Message type pid client
  */
  int msgId = *((int *)arg);
  t_request request;
  while(strcmp(request.body.msg, CLOSE_CONNECTION_MSG)) {
    CHECK(msgrcv(msgId, &request, sizeof(t_body), getpid(), 0), "SERVER : --- Problem while trying to read message from mailbox ---");
    puts("Receipt recieved.\nEnd thread...");
  }
  pthread_exit(0);
}

void *sendRequest(void *arg) {
  int msgId = *((int *)arg);
  t_request request;
  request.type = 1;
  request.body.pid = getpid();
  while(strcmp(request.body.msg, CLOSE_CONNECTION_MSG)) {
    getMsgFromUser(request.body.msg);
    CHECK(msgsnd(msgId, &request, sizeof(t_body), 0), "--- Problem while sending message ---");
  }
  pthread_exit(0);
}

int getMsgFromUser(char *buffer) {
  printf("Entrez un message à envoyé au serveur... (Fin si voous envoyez \"%s\")\n", CLOSE_CONNECTION_MSG);
  if(fgets(buffer, MAX_BODY_MSG_SIZE, stdin) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    fflush(stdin);
  }
}
