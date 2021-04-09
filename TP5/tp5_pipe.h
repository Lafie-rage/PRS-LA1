#ifndef TP5_PIPE_H
  #define TP5_PIPE_H

  #ifndef NAMED // Anonymous pipes

    #define CLOSE_PIPE_MSG "AU REVOIR"
    #define RESPONS_MSG "OK"

  #endif

  #ifndef ANONYMOUS

    // Named pipes
    #define FIFO_PATHNAME "./myFifo"
    #define MSG_TO_SEND "Ceci est un message envoyé par un pipe nomé"
    #define CLOSE_PIPE_MSG "PAUSE"

  #endif

  // Both
  #define MAX_MSG_SIZE 256

#endif
