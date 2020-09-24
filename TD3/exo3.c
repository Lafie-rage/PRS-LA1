#include <stdio.h>
#include <string.h>

int main(void) {
  int i;
  char c;
  char chaine[13];
  int monTableau[12];
  char monTableauDeChaines[2][10];
  i=10;
  c = 'A';
  strcpy(chaine, "Bonjour");
  printf("\nPremière affectation = %s", chaine);
  sprintf(chaine, "Bonjour");
  printf("\nPremière affectation, chaine = %s", chaine);

  printf("\nBonjour, merci de saisir la valeur de la chaine : ");
  scanf("%12s", chaine);
  printf("\nVoici le 6ème caractère de chaine %c\n", chaine[5]);
  monTableau[0] = 1;
  monTableau[1] = 5;
  monTableau[2] = 5;
  monTableau[3] = 7;
  monTableau[4] = 11;
  sprintf(monTableauDeChaines[0], "123456789");
  sprintf(monTableauDeChaines[1], "ABCDEFHGI");

  printf("\n Premier élément de monTableauDeChaines : %s", monTableauDeChaines[0]);
  printf("\n Deuxième élément de monTableauDeChaines : %s", monTableauDeChaines[1]);

  strncpy(monTableauDeChaines[0], "1234567890123456789", 9);
  strncpy(monTableauDeChaines[1], "ABCDEFHGIJKLMNOPQRSTUVWXYZ", 9);
  printf("\n Premier élément de monTableauDeChaines : %s", monTableauDeChaines[0]);
  printf("\n Deuxième élément de monTableauDeChaines : %s", monTableauDeChaines[1]);
  return 0;
}
