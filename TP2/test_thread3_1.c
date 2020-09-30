/* =============================================================================== */
/*                                                                                 */
/* test_thread3_1.c                                                                   */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#define MESSAGE "Salut a tous"

void *thread1_treatement(void *arg) {
  char* chaine = (char *)arg;
  int i = 0;

  for (; i < strlen(chaine); i++) {
    printf("%c\n", toupper(chaine[i]));
  }

  pthread_exit(EXIT_SUCCESS);
}

void *thread2_treatement(void *arg) {
  char* chaine = (char *)arg;
  int i = 0;

  for (; i < strlen(chaine); i++) {
    printf("%c\n", tolower(chaine[i]));
  }

  pthread_exit(EXIT_SUCCESS);
}

int main(void) {
  pthread_t th1,
            th2;
  void *retVal_th1,
       *retVal_th2;

  pthread_create(&th1, NULL, thread1_treatement, MESSAGE);
  pthread_create(&th2, NULL, thread2_treatement, MESSAGE);

  pthread_join(th1, &retVal_th1);
  pthread_join(th2, &retVal_th2);

  return EXIT_SUCCESS;
}
