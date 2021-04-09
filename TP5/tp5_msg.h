#ifndef TP5_MSG_H
#define TP5_MSG_H

// Request type...
#define MAX_BODY_MSG_SIZE 256
#define CLOSE_CONNECTION_MSG "SALUT"
#define MSG_RECEIVED "RECEIVED"
typedef struct body {
  pid_t pid;
  char msg[MAX_BODY_MSG_SIZE];
} t_body;
typedef struct request {
  long type;
  t_body body;
} t_request;

#endif
