#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define PASSWORD "bonjour"
#define NB_TRY_PASS 5

int fork_result;

void signalCallback_parent(int signal);
void signalCallback_child(int signal);

int main (void) {
  printf("Je suis le processus pere, mon PID est : %d\n", getpid());
  fork_result = fork();
  if(!fork_result) { // fils
    char strInp[200] = "";
    char ch;
    int cmpNbTry = 0,
        cmpPassLength;
    struct sigaction newact_child;
    int ppid = getppid();
    printf("Je suis le fils est mon PID est : %d\n", getpid());
    newact_child.sa_handler = signalCallback_child;
    newact_child.sa_flags = 0; // Remise du flag à 0
    sigaction(SIGINT, &newact_child, NULL);
    printf("Entrez votre mdp. Vous avez %d tentatives\n", NB_TRY_PASS);
    while(cmpNbTry < NB_TRY_PASS) {
      fgets(strInp, 199, stdin);
      if(strInp[0] != '\0') { // If the user input ctrl+c, we ignore it
        // Avoid \n recorded by scanf, whatever the string send's length
        cmpPassLength = -1;
        while(strInp[++cmpPassLength] != '\n' && cmpPassLength < 200);
        strInp[cmpPassLength] = '\0';
        if(strcmp(strInp, PASSWORD) == 0) break; // Password is correct
        puts("Le mot de passe entre est invalide. Veuillez reessayer...");
        cmpNbTry++;
      }
    }
    if(cmpNbTry < NB_TRY_PASS) kill(ppid, SIGUSR1); // Define as signal for an valide pass
    else kill(ppid, SIGUSR2); // Define as signal for an invalide pass
    wait(&ppid);
  }
  else { // pere
    struct sigaction newact_parent;
    newact_parent.sa_handler = signalCallback_parent;
    newact_parent.sa_flags = 0; // Remise du flag à 0
    sigaction(SIGUSR1, &newact_parent, NULL);
    sigaction(SIGUSR2, &newact_parent, NULL);
    sigaction(SIGALRM, &newact_parent, NULL);
    signal(SIGINT, SIG_IGN); // ignore ctrl+c
  	alarm(20);
    wait(&fork_result);
  }
}

void signalCallback_child(int signal) {
  if(signal == SIGINT)// pas besoin de switch pluisqu'un seul signal est deroute
    puts("\nLe signal d'interruption envoye par la combinaison de touche ctrl+c est ignore.");
}
void signalCallback_parent(int signal) {
  switch (signal) {
    case SIGUSR1: // valide password
      puts("Le mot de passe entre est valide.");
      break;
    case SIGUSR2: // invalide password
      puts("Vous avez depasse votre nombre de tentatives pour entrer votre mot de passe. Veuillez réessayer plus tard. :)");
      break;
    case SIGALRM:
      kill(fork_result, SIGKILL);
      puts("Le temps pour entrer le mot de passe est depasse");
      break;
    default:
      break;
  }
}
