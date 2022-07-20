#ifndef _LOG_
#define _LOG_

/* Header de operacoes nos arquivos de log */

#include <stdio.h>

#define TAMLINHA 60

/* Estrutura do vetor de logs */
struct log {
    char   *Nome;
    char   *Data;
    int  distancia;
    int  velMedia;
    int  velMax;
    int  hrMedio;
    int  hrMax;
    int  cadMedia;
    int  subAcumulada;
};
typedef struct log log_t;

/* Estrutura da linha dos logs */
struct linha {
    char *atributo;
    char *valor;
};
typedef struct linha linha_t;


/* Zera valroes da estrutura */
void zeraEstrutura(log_t *log);

/* Le o nome e insere no vetor */
int bikeName(FILE *f, log_t *log);

/* Le a data e insere no vetor */
int bikeDate(FILE *f, log_t *log);

/* Le bloco de dados */
int leBlocoDados(FILE *f, log_t *log);

/* Desaloca vetor */
void destroiVetorLog(log_t *vetLog, int vetTam);

/* Imprime vetor */
void imprimeVetorLog(log_t *vetLog, int vetTam);


#endif
