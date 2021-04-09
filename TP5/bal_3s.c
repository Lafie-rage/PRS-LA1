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

void printMsgInfo(int msgId);

int main(void) {
  /* TODO :
  Créer une boite aux lettres
  Appel fonction affichage informations
  Boucle reception msg type 1
  Si message => affichage celui-ci et appel fonction affichage informations
  Suppression boite aux lettres
  */
  int msgId;
  key_t key = ftok("/tmp", MSG_KEY);
  t_request request;
  // Cration mail box //
  CHECK(msgId = msgget(key, 0666 | IPC_CREAT | IPC_EXCL), "SERVER : --- Problem while creating mailbox ---");
  printMsgInfo(msgId);
  while (1) {
    CHECK(msgrcv(msgId, &request, sizeof(t_body), 1, 0), "SERVER : --- Problem while trying to read message from mailbox ---");
    printf("Message send : %s\n", request.body.msg);
    printMsgInfo(msgId);
  }
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
