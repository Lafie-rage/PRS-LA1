#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;

void signalCallback(int signal){
  if(signal == SIGINT) {
    puts("Le signal d'interruption envoye par la combinaison de touche ctrl+c est ignoré.");
  }
}

int main(void) { // Inspiré du code vu en TD diapo Processus et signaux p58
  printf("Mon PID est : %d\n", getpid());
  newact.sa_handler = signalCallback;
  newact.sa_flags = 0; // Remise du flag à 0
  sigaction(SIGINT, &newact, NULL);

  while(1);

  return 0;
}
