#include <stdio.h>

int main(void) {
  int i;
  i = 12;
  i++;
  printf("Bonjour donnez la valeur de i :");
  scanf("%d", &i);
  printf("\nVous avez saisi la valeur %d\n", i);
  return i;
}
