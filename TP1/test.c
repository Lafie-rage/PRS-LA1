#include <stdio.h>
#include <sched.h>

int main (void) {
  printf("SCHED_FIFO : %d\n", SCHED_FIFO);
  printf("SCHED_RR : %d\n", SCHED_RR);
  printf("SCHED_OTHER : %d\n", SCHED_OTHER);
}
