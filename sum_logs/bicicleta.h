#ifndef _BICICLETA_
#define _BICICLETA_

#include "log.h"

#include <stdio.h>


/* Estrutura da bicicleta */
struct bike {
    char    *nome;          /* Nome da bicicleta */
    log_t   *iniVet;        /* Ponteiro de inicio do vetor */
    log_t   *fimVet;        /* ponteiro do fim do vetor */
    int     nAtividades;    /* Quantidade de atividades realizada */
    int     distTotal;      /* Distancia total percorrida */
    int     distMedia;      /* Distancia media percorrida */
    int     pMaisLongo;     /* Pedal mais longo */
    int     pMaisCurto;     /* Pedal mais curto */
};
typedef struct bike bike_t;





#endif
