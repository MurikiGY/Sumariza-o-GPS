#ifndef _BICICLETA_
#define _BICICLETA_

#include <stdio.h>

/* arquivo que define as operações realizadas na estrutura bicicleta */

#define PATHSIZE 30
#define BIKENAMESIZE 30
#define LOGLINESIZE 50
#define ATTRIBUTESIZE 10

/* estrutura para cada arquivo de log */
struct logData {
    int data;
    int distancia;
    int velMedia;
    int velMaxima;
    int hrMedio;
    int hrMaximo;
    int cadenMedia;
    int subAcumulada;
};
typedef struct logData logData_t;

/* Estrutura de cada bicicleta */
struct bike {
    char bikeName[BIKENAMESIZE];    /* Nome da bicicleta */
    int nLogs;                      /* tamanho do vetor de logs */
    logData_t *logVector;           /* Vetor de logs */
    int totalkm;                    /* total percorrido em km */
    int pedalmaior;                 /* pedal mais longo em km */
    int pedalmeor;                  /* pedal mais curto em km */
    int disMed;                     /* distancia media em km */
};
typedef struct bike bike_t;


/* cria estrutura de uma nova bicicleta
 * retorna 1 em sucesso
 * retorna 0 em falha*/
int criaBike(bike_t *vBike, char *name, int *vtam);

/* Destroi/Desaloca a estrutura de bicicletas */
void destroiBike(bike_t *vBike, int vtam);

/* testa se a bicicleta ja existe
 * se encontrar, retorna o indice da bicicleta
 * retorna -1 do contrario */
int existeBike(bike_t *vBike, char *name, int *vtam);

/* funcao de impressao das bicicletas */

/* Cria novo registro de bicicleta */


#endif
