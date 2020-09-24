#include <stdio.h>
#include <unistd.h>

int main (void) {
  printf("Mon PID est : %d\n", getpid());
  //while(1); // Question 2.1.2
  alarm(20);
  pause();
}
