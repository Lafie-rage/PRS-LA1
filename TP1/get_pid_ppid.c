#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf("Le PID du processus courant est : %d.\nLe PID de son père (PPID) est : %d.\n",getpid(), getppid());
	return 0;
}
