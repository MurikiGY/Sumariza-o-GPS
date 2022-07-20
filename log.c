#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"


/* Zera valores da estrutura */
void zeraEstrutura(log_t *log){
    
    log->distancia      = 0;
    log->velMedia       = 0;
    log->velMax         = 0;
    log->hrMedio        = 0;
    log->hrMax          = 0;
    log->cadMedia       = 0;
    log->subAcumulada   = 0;
}


/* Retorna atributo e valor por parametro */
void atributoValor(char *l, char **a, char **v){

    printf("Copiando a string: %s\n", l);

    *a = strtok(l, " ");
    *v = strtok(NULL, "\n");

    printf("Atributo: %s\n", *a);
    printf("Valor: %s\n", *v);

}


/* le o nome da bicicleta do arquivo
 * f    = Variavel de acesso ao arquivo
 * log  = Struct do indice do vetor
 * */
int bikeName (FILE *f, log_t *log){
    char linha[TAMLINHA];       /* Estrutura com atributo e valor   */
    char *atributo;             /* String de atributo               */
    char *valor;                /* String de valor                  */

    /* Guarda a string da linha em "linha" */
    fgets(linha, TAMLINHA, f);

    /* Retorna o atributo "Gear" e o valor "nome" */
    atributoValor(linha, &atributo, &valor);

    /* Testa se atributo eh Gear */
    if (strcmp(atributo, "Gear:")){

        fprintf(stderr, "Atributo %s lido diferente de Gear\n", atributo);
        return 1;

    } else {

        /* Alocacao da string do nome */
        if (!(log->Nome = malloc(sizeof(char)*(strlen(valor) + 1)))){
            fprintf(stderr, "Erro de alocacao do nome do log\n");
            return 1;
        }

        /* Copia conteudo de "valor" para o nome na estrutura */
        strncpy(log->Nome, valor, strlen(valor) + 1);

    }

    return 0;
}

/* Le linha de data do arquivo */
int bikeDate (FILE *f, log_t *log){
    char linha[TAMLINHA];       /* Estrutura com atributo e valor   */
    char *atributo;             /* String de atributo               */
    char *valor;                /* String de valor                  */

    /* Guarda a string da linha em "linha" */
    fgets(linha, TAMLINHA, f);

    /* Retorna o atributo "Data" e o valor */
    atributoValor(linha, &atributo, &valor);

    /* Testa se o atributo eh uma Data */
    if (strcmp(atributo, "Date:")){

        fprintf(stderr, "Atributo lido diferente de Date\n");
        return 1;

    } else {

        /* alocacao da estrutura */
        if (!(log->Data = malloc(sizeof(char)*(strlen(valor) + 1)))){
            fprintf(stderr, "Erro de alocacao da data do log\n");
            return 1;

        }

        strncpy(log->Data, valor, strlen(valor) + 1);
    }

    return 0;
}

/* Retorna um inteiro de uma string */
int strInteger (char *s){

    return atoi(strtok(s, " "));

}


/* Le bloco de dados e insere no vetor
 * f    = Arquivo a ser acessado 
 * log  = Estrutura de dados */
int leBlocoDados(FILE *f, log_t *log){
    char linha[TAMLINHA];       /* Estrutura com atributo e valor   */
    char *atributo;             /* String de atributo               */
    char *valor;                /* String de valor                  */

    /* Guarda a string da linha em "linha" */
    fgets(linha, TAMLINHA, f);

    /* Retorna o atributo "Data" e o valor */
    atributoValor(linha, &atributo, &valor);

    /* testa se leu altitude */
    if (!strcmp(atributo, "altitude:")){

        /* Atualiza altura */
        log->subAcumulada = strInteger(valor);

    } else if (!strcmp(atributo, "cadence:")){

        /* Atualiza cadencia */
        log->cadMedia = strInteger(valor);

    } else if (!strcmp(atributo, "distance:")){

        /* Atualiza distancia */
        log->distancia = log->distancia + strInteger(valor);

    } else if (!strcmp(atributo, "heart_rate:")){

        /* Atualiza heart_rate */
        log->hrMedio = log->hrMedio + strInteger(valor);

    } else if (!strcmp(atributo, "speed:")){

        /* Atualiza speed */
        log->velMedia = log->velMedia + strInteger(valor);

//    } else if (!strcmp(atributo, "timestamp:")){



    }

    return 1;
}


/* Desaloca vetor */
void destroiVetorLog(log_t *vetLog, int vetTam){
    int i;

    /* desaloca Nome, Data */
    for(i=0; i<vetTam ;i++){
        free(vetLog[i].Nome);
        free(vetLog[i].Data);
    }

    free(vetLog);
}


/* Imprime vetor */
void imprimeVetorLog(log_t *vetLog, int vetTam){
    int i;

    for(i=0; i<vetTam ;i++){
        fprintf(stdout, "imprimindo log da posição %d:\n", i);
        fprintf(stdout, "Nome: %s\n", vetLog[i].Nome);
        fprintf(stdout, "Data: %s\n", vetLog[i].Data);
        fprintf(stderr, "Distancia percorrida: %d\n", vetLog[i].distancia);
        fprintf(stderr, "Velocidade Media: %d\n", vetLog[i].velMedia);
        fprintf(stderr, "Velocidade Maxima: %d\n", vetLog[i].velMax);
        fprintf(stderr, "Heart_rate Medio: %d\n", vetLog[i].hrMedio);
        fprintf(stderr, "Heart_rate Maximo: %d\n", vetLog[i].hrMax);
        fprintf(stderr, "Cadencia media: %d\n", vetLog[i].cadMedia);
        fprintf(stderr, "Subida acumulada: %d\n", vetLog[i].subAcumulada);
        fprintf(stdout, "\n");
    }

    return;
}


