#ifndef _LOG_
#define _LOG_

/* Header de operacoes nos arquivos de log */

#include <stdio.h>

#define TAMLINHA 60

/* Estrutura do vetor de logs */
struct log {
    char   *Nome;
    char   *Data;
    float  distancia;
    float  velMedia;
    float  velMax;
    float  hrMedio;
    float  hrMax;
    float  cadMedia;
    float  subAcumulada;
};
typedef struct log log_t;

/* Estrutura da linha dos logs */
struct linha {
    char *atributo;
    char *valor;
};
typedef struct linha linha_t;


/* Le a linha do arquivo e retorna o atributo e o valor */
linha_t *leAtributoValor(FILE *f);

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
