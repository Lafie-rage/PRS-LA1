#include <stdio.h>

int main(void) {
  FILE* f_readme = fopen("./ressources/README.TXT", "r");
  FILE* f_monreadme = fopen("./ressources/MONREADME.TXT", "w+");
  long taille;
  char contentReadMe[101];
  char phraseSup[101];

  puts("Contenu du fichier README.TXT :");
  fscanf(f_readme, "%[^\n]s\n", contentReadMe);
  printf("%s\n", contentReadMe);
  puts("Création du nouveau fichier :");
  fprintf(f_monreadme, "%s\n", contentReadMe);
  fseek(f_readme, EOF, SEEK_SET);
  taille = ftell(f_readme);
  printf("Taille du fichier README.TXT : %ld\n", taille);
  fprintf(f_monreadme, "%sLe fichier README.TXT contient %ld caractere(s).\n", contentReadMe, taille);
  puts("Ajout de la taille du fichier README.TXT dans le fichier MONREADME.TXT");
  fscanf(f_monreadme, "%[^\n]s\n%[^\n]s", contentReadMe, phraseSup);
  printf("Contenue du fichier MONREADME.TXT :\n%s\n%s", contentReadMe, phraseSup); // marche pas entièrement mais flemme pour l'instant
}
