/* =============================================================================== */
/*                                                                                 */
/* test_caractere.c                                                                */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITER_LOOP 1000

char flag = 0;


void *printA(void *arg);

void *printB(void *arg);


int main(void) {
  pthread_t th1,
            th2;
  void *retVal_th1,
       *retVal_th2;

  pthread_create(&th1, NULL, printA, NULL);
  pthread_create(&th2, NULL, printB, NULL);

  pthread_join(th1, &retVal_th1);
  pthread_join(th2, &retVal_th2);

  return EXIT_SUCCESS;
}


/* =============================================================================== */
/*                                FUNCTIONS' CORPSES                               */
/* =============================================================================== */

void *printA(void *arg) {
  char chaine[] = "AAAAAAAAAAAAAAAAAAAA";
  int i = 0,
      cmp_loop_1 = 0,
      cmp_loop_2;

  while(flag);
  flag++;
  for(; i<21; i++) {
    printf("%c", chaine[i]);
    for (; cmp_loop_1 < ITER_LOOP; cmp_loop_1++)
      for (cmp_loop_2 = 0; cmp_loop_2 < ITER_LOOP; cmp_loop_2++); // wait
  }
  puts("");
  flag = 0;

  pthread_exit(EXIT_SUCCESS);
}


void *printB(void *arg) {
  char chaine[] = "BBBBBBBBBBBBBBBBBBBB";
  int i = 0,
      cmp_loop_1 = 0,
      cmp_loop_2;

  while(flag);
  flag++;
  for(; i<21; i++) {
    printf("%c", chaine[i]);
    for (;cmp_loop_1 < ITER_LOOP; cmp_loop_1++)
      for (cmp_loop_2 = 0; cmp_loop_2 < ITER_LOOP; cmp_loop_2++); // wait
  }
  puts("");
  flag = 0;

  pthread_exit(EXIT_SUCCESS);
}
