#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tp5.h"

#define MSG_KEY 1
#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

int main(void) {
  /* TODO :
  Ouvre la boite aux lettres serveur
  10 fois =>
    - lit message utilisateur
    - envoit message au serveur (type 1)
  */
  int msgId, i;
  key_t key = ftok("/tmp", MSG_KEY);
  char msg[MAX_BODY_MSG_SIZE] = "";
  t_request request;
  request.type = 1;
  request.body.pid = getpid();
  // Cration mail box //
  CHECK(msgId = msgget(key, 0), "--- Problem while retrieving mailbox ---");
  for(i = 0; i < 10; i++) {
    printf("Entrez un message à envoyé au serveur...");
    fgets(msg, MAX_BODY_MSG_SIZE, stdin);
    strcpy(request.body.msg, msg);
    CHECK(msgsnd(msgId, &request, sizeof(t_body), 0), "--- Problem while sending message ---");
  }
}
