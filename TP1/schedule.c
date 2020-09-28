/* =============================================================================== */
/*                                                                                 */
/* schedule.c                                                                     */
/* Auteur : I Le Glaz    																													 */
/* Commentateur : Corentin Destrez                                                 */
/* =============================================================================== */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <errno.h>

#define CHECK(sts, msg)				\
	if (-1 == (sts) && errno != 0) 	\
	{								\
		perror(msg);				\
		exit(EXIT_FAILURE);			\
	} else         					\
		printf("%s : %d\n", msg, sts)

int main (void)
{
    struct sched_param param;
    int my_pid = 0;
    int old_policy, old_priority;
    int status;
    int low_priority, high_priority;

    system ("clear;ps -l"); // On clear la console puis on execute ps -l afin de voir les priorites de tous les processus en cours dans la console
    status = nice (+10); // On change la priorite du processus en lui ajoutant 10.
    CHECK(status, "nice(+10)");
    system ("ps -l"); // On reaffiche la priorité des processus executes dans la console

    high_priority = sched_get_priority_max(SCHED_FIFO); // On recupere la valeur de la priorite haute pour SCHED_FIFO
    CHECK(high_priority,"sched_get_priority_max FIFO");

    low_priority = sched_get_priority_min(SCHED_FIFO); // On recupere la valeur de la priorite basse pour SCHED_FIFO
    CHECK(low_priority,"sched_get_priority_min FIFO");

    old_policy = sched_getscheduler(my_pid); // On recupere la politique d'ordonnancement actuelle du processus
    CHECK(old_policy,"sched_getscheduler");

    status = sched_getparam(my_pid, &param); // On recupere les parametres d'ordonnancement actuels
    CHECK(status,"sched_getparam");

    old_priority = param.sched_priority; // On recupere la priorite actuelle du processus

    param.sched_priority = high_priority; // on defini ensuite la priorite du processus sur une priorite haute
    status = sched_setscheduler(my_pid, SCHED_FIFO, &param); // On passe l'ordonnanceur en politique FIFO et met à jour la priorite definie precedemment
    CHECK(status,"sched_setscheduler");

    param.sched_priority = low_priority; // on defini ensuite la priorite du processus sur une priorite haute
    status = sched_setparam(my_pid, &param); // Met a jour la priorite definie precedemment
    CHECK(status,"sched_setparam");

    param.sched_priority = old_priority; // retablie la valeur de base de la priorite
    status = sched_setscheduler(my_pid, old_policy, &param); // met a jour la priorite definie precedemment et retablie la politique d'ordonnancement de base
    CHECK(status,"sched_setscheduler 2");

    status = nice (-11); // renice le processus en lui retirant 11 de priorite
    CHECK(status, "nice(-11)");
    system ("ps -l"); // reaffiche la priorite des processus courrant dans la console

    exit(EXIT_SUCCESS);
}
