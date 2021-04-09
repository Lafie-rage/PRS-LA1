#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

#define MSG_KEY 1
#define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

void printMsgInfo(int msgId);

int main(void) {
  /* TODO :
  Créer une boite aux lettres
  Appel fonction affichage
  Suppression boite aux lettres
  */

  int msgId;
  key_t key = ftok("/tmp", MSG_KEY);
  // Cration mail box //
  CHECK(msgId = msgget(key, 0666 | IPC_CREAT | IPC_EXCL), "--- Problem while creating mailbox ---");
  printMsgInfo(msgId);
  CHECK(msgctl(msgId, IPC_RMID, NULL), "--- Problem while deleting mailbox ---");
}

void printMsgInfo(int msgId) {
  /* TODO :
  Affiche ses informations
  */
  struct msqid_ds buffer;
  CHECK(msgctl(msgId, IPC_STAT, &buffer), "--- Problem while retrieving mailbox informations ---");
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
