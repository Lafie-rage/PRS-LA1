/* =============================================================================== */
/*                                                                                 */
/* tp6.c                                                                           */
/* Auteur : Corentin DESTREZ                                                       */
/* =============================================================================== */


#include "tp6.h"

void initComInfo(t_communication_info *comInfo) {
  comInfo->fifoFd = -1;
  comInfo->shmId = -1;
}
