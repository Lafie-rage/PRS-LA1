#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void main(){
  printf("Mon PID est : %d\n", getpid());
	signal(SIGINT, SIG_IGN);
	while(1);
}
