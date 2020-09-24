/*!
 * @file IMC.c
 *
 * @author Lafie-rage
 *
 *  @brief Calculate the "IMC" by asking weigth and length and returns you your medical state.
 *
 */

#include <stdio.h>

int main(void) {
  float taille; // taille en cm
  int poids; // poids en grammes
  printf("Quel est votre taille (en cm)? ");
  scanf("%f", &taille);
  printf("\nQuel est votre poids (en kg)? ");
  scanf("%d", &poids);
  taille /= 100;
  float imc = poids/(taille * taille);
  printf("\nVotre IMC est de : %.2f\n", imc);
  if (imc < 16.5) {
    puts("Vous êtes en dénutrition/anoréxie");
  }
  else if (imc < 18.5) {
    puts("Vous êtes maigre");
  }
  else if (imc < 25) {
    puts("Votre poids est idéal");
  }
  else if (imc < 30) {
    puts("Vous êtes en surpoids");
  }
  else if (imc < 35) {
    puts("Vous êtes en obésité modérée");
  }
  else if (imc < 40) {
    puts("Vous êtes en obésité sévère");
  }
  else {
    puts("Vous êtes en obésité morbide/massive");
  }
}
