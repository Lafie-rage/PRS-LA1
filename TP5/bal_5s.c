/* =============================================================================== */
/*                                                                                 */
/* bal_5s.c                                                                       */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tp5_msg.h"

#define MSG_KEY 1
#define CLIENT_LIST_SIZE 5
#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

void printMsgInfo(int msgId);

void sendReceipt(int msgId, int clientPid, const char *msg);
void updatingList(int *clients, int *nbKnownClients, pid_t clientPid);
void removeFromList(int *clients, int *nbKnownClients, pid_t clientPid);
void printClientsList(const int *clients, int nbKnownClients);

int main(void) {
  /* TODO :
  Créer une boite aux lettres
  Appel fonction affichage informations
  Boucle reception msg type 1
  Si message différent de CLOSE_CONNECTION_MSG =>
    - affichage celui-ci
    - appel fonction affichage informations
    - Si message CLOSE_CONNECTION_MSG => suppression client de la liste
    - Sinon si client pas dans la liste, on l'ajoute
    - envoit accusé de récéption
  Suppression boite aux lettres
  */
  int msgId, nbKnownClients;
  key_t key = ftok("/tmp", MSG_KEY);
  t_request request;
  int clients[CLIENT_LIST_SIZE];
  strcpy(request.body.msg, "");
  // Cration mail box //
  CHECK(msgId = msgget(key, 0666 | IPC_CREAT | IPC_EXCL), "SERVER : --- Problem while creating mailbox ---");
  printMsgInfo(msgId);

  do {
    CHECK(msgrcv(msgId, &request, sizeof(t_body), 1, 0), "SERVER : --- Problem while trying to read message from mailbox ---");
    printf("Message send : %s\n", request.body.msg);
    if(!strcmp(request.body.msg, CLOSE_CONNECTION_MSG)){
      removeFromList(clients, &nbKnownClients, request.body.pid);
      sendReceipt(msgId, request.body.pid, CLOSE_CONNECTION_MSG);
    }
    else {
      updatingList(clients, &nbKnownClients, request.body.pid);
      sendReceipt(msgId, request.body.pid, MSG_RECEIVED);
    }
    printClientsList(clients, nbKnownClients);
    printMsgInfo(msgId);
  } while (nbKnownClients != 0);
  CHECK(msgctl(msgId, IPC_RMID, NULL), "SERVER : --- Problem while deleting mailbox ---");
}

void printMsgInfo(int msgId) {
  /* TODO :
  Affiche ses informations
  */
  struct msqid_ds buffer;
  CHECK(msgctl(msgId, IPC_STAT, &buffer), "SERVER : --- Problem while retrieving mailbox informations ---");
  puts("msqid_ds {");
  printf("\tmsg_stime : %s,\n", ctime(&(buffer.msg_stime)));
  printf("\tmsg_rtime : %s,\n", ctime(&(buffer.msg_rtime)));
  printf("\tmsg_ctime : %s,\n", ctime(&(buffer.msg_ctime)));
  printf("\t__msg_cbytes : %ld,\n", buffer.__msg_cbytes);
  printf("\tmsg_qnum : %ld,\n", buffer.msg_qnum);
  printf("\tmsg_qbytes : %ld,\n", buffer.msg_qbytes);
  printf("\tmsg_lspid : %d,\n", buffer.msg_lspid);
  printf("\tmsg_lrpid : %d,\n", buffer.msg_lrpid);
  puts("\tipc_perm : {");
  printf("\t\t__key : %d,\n", buffer.msg_perm.__key);
  printf("\t\tuid : %d,\n", buffer.msg_perm.uid);
  printf("\t\tgid : %d,\n", buffer.msg_perm.gid);
  printf("\t\tcuid : %d,\n", buffer.msg_perm.cuid);
  printf("\t\tcgid : %d,\n", buffer.msg_perm.cgid);
  printf("\t\tmode : %d,\n", buffer.msg_perm.mode);
  printf("\t\t__seq : %d\n", buffer.msg_perm.__seq);
  puts("\t}\n}");

}


void sendReceipt(int msgId, int clientPid, const char* msg) {
  /* TODO :
    Envoit MSG_RECEIVED au client
    Message de type pid client
    */
  t_request receipt;
  receipt.type = clientPid;
  receipt.body.pid = getpid();
  strcpy(receipt.body.msg, msg);
  CHECK(msgsnd(msgId, &receipt, sizeof(t_body), 0), "SERVER : --- Problem while sending receipt to client ---");
}

void updatingList(int *clients, int *nbKnownClients, pid_t clientPid) {
  int i;
  for(i = 0; i < *nbKnownClients; i++) {
    if(clients[i] == clientPid)
      break;
  }
  printf("i = %d\n", i);
  if( i == *nbKnownClients) // clients inconnu
    clients[(*nbKnownClients)++] = clientPid;
}

void removeFromList(int *clients, int *nbKnownClients, pid_t clientPid) {
  int i, indexToRemove = -1;
  int tmp;
  for(i = 0; i < *nbKnownClients; i++) {
    if(clients[i] == clientPid)
      indexToRemove = i;
      break;
  }
  if(indexToRemove != -1) {
    (*nbKnownClients)--;
    if(indexToRemove != 0) {
      for(i = indexToRemove; i < *nbKnownClients; i++) {
        clients[i] = clients[i+1];
      }
    }
  }
}

void printClientsList(const int *clients, int nbKnownClients) {
  int i = 0;
  puts("Known clients : {");
  for(i = 0; i < nbKnownClients; i++) {
    if(i == nbKnownClients)
      printf("Clients %d pid : %d\n", i+1, clients[i]);
    else
      printf("Clients %d pid : %d,\n", i+1, clients[i]);
  }
  puts("}");
}
