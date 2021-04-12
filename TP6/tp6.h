/* =============================================================================== */
/*                                                                                 */
/* tp6.h                                                                           */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#ifndef TP6_H
  #define TP6_H

  #define MAX_MSG_SIZE 256
  #define SHM_SIZE 256
  #define SEM_SHM_NAME "shm_sem"
  #define SEM_PIPE_NAME "pipe_sem"
  #define PIPE_PATH "./server_pipe"
  #define SHM_PATH "./server_shm"

  #include <sys/ipc.h>
  #include <sys/shm.h>

  #define CHECK(sts,msg) if ((sts)== -1) {perror(msg); exit(-1);}

  //typedef struct shmid_ds t_shmid_ds;

  typedef struct communication_info {
    int fifoFd;
    int shmId;
    char *shmPtr;
    struct shmid_ds shmBuffer;
  } t_communication_info;

  void initComInfo(t_communication_info *comInfo);

#endif
