#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

/* funcao para desalocar estrutura de linha */
void desalocaLinha(linha_t *l){

    free(l->atributo);
    free(l->valor);
    free(l);

    return;
}


/* le uma linha, retorna o atributo e valor na estrutura */
linha_t *leAtributoValor (FILE *f){
    linha_t     *l;               /* Estrutura de retorno   */
    char        linha[TAMLINHA];  /* String de toda a linha */

    /* Aloca a estrutura de retorno */
    if (!(l = malloc(sizeof(linha_t)))){
        fprintf(stderr, "Falha de alocacao da linha\n");
        return NULL;
    }

    /* Aloca as strings de dentro da estrutura */
    if (!(l->atributo = malloc(sizeof(char)*TAMLINHA))){
        fprintf(stderr, "Falha de alocacao do atributo da linha\n");
        return NULL;
    }
    if (!(l->valor = malloc(sizeof(char)*TAMLINHA))){
        fprintf(stderr, "Falha de alocacao do valor da linha\n");
        return NULL;
    }

    /* le a linha inteira e testa se leu a ultima linha do arquivo */
    if (!fgets(linha, TAMLINHA, f)){
        desalocaLinha(l);
        return NULL;
    }

//    fprintf(stdout, "%s", linha);

    /* Testa linha vazia */
//    if (strlen(linha) <= 1){
//        desalocaLinha(l);
//        return NULL;
//    }

    /* Guarda o atributo */
    strcpy(l->atributo, strtok(linha, " "));
    l->atributo[strcspn(l->atributo, "\n")] = '\0';

    /* Guarda o valor */
    strcpy(l->valor, strtok(NULL, "\0"));
    l->valor[strcspn(l->valor, "\n")] = '\0';

    return l;
}


/* Recebe string por parametro, retorna por parametro atributo e valor */
void le_linha(FILE *f, char *linha, char *atributo, char *valor){


    /* Guarda o atributo */
    strcpy(atributo, strtok(linha, " "));
    atributo[strcspn(atributo, "\n")] = '\0';

    /* Guarda o valor */
    strcpy(valor, strtok(linha, " "));
    valor[strcspn(valor, "\n")] = '\0';

}













/* Zera valores da estrutura */
void zeraEstrutura(log_t *log){
    
    log->distancia = 0;
    log->velMedia = 0;
    log->velMax = 0;
    log->hrMedio = 0;
    log->hrMax = 0;
    log->cadMedia = 0;
    log->subAcumulada = 0;
}


/* le o nome da bicicleta do arquivo */
int bikeName (FILE *f, log_t *log){
    char linha[TAMLINHA];       /* Estrutura com atributo e valor */
    char atributo[TAMLINHA];    /* String de atributo */
    char valor[TAMLINHA];       /* String de valor */

    fgets(linha, TAMLINHA, f);

    /* Retorna o atributo e o valor lido */
    AtributoValor(linha, atributo, valor);

    /* Guarda no vetor o nome da bicicleta */
    /* Testa se atributo eh Gear */
    if (strcmp(atributo, "Gear:")){
        fprintf(stderr, "Atributo %s lido diferente de Gear\n", atributo);
        return 1;
    } else {
        /* Testa a alocacao da string do nome */
        if (!(log->Nome = malloc(sizeof(char)*(strlen(valor) + 1)))){
            fprintf(stderr, "Erro de alocacao do nome do log\n");
            return 1;
        }
        strncpy(log->Nome, valor, strlen(valor) + 1);
    }

    desalocaLinha(linha);
    return 0;
}

/* Le linha de data do arquivo */
int bikeDate (FILE *f, log_t *log){
    linha_t *linha;     /* Estrutura com atributo e valor   */
//    char aux[TAMLINHA]; /* string auxiliar                  */

    /* Le a data */
    linha = leAtributoValor(f);
    if (!linha)
        return 1;

    /* Guarda no vetor a data do log */
    /* Testa se o atributo eh uma Data */
    if (strcmp(linha->atributo, "Date:")){
        fprintf(stderr, "Atributo lido diferente de Date\n");
        return 1;
    } else {
        /* Testa alocacao da string de data */
        if (!(log->Data = malloc(sizeof(char)*(strlen(linha->valor) + 1)))){
            fprintf(stderr, "Erro de alocacao da data do log\n");
            return 1;
        }
        /* formata a data */
        /* LEMBRAR DE FORMATAR A DATA */

        strncpy(log->Data, linha->valor, strlen(linha->valor) + 1);
    }

    desalocaLinha(linha);
    return 0;
}

/* Recebe uma string e retorna o float formatado */
//float strtofloat (char *s){
//    int i, strtam;
//
//    strtam = strlen(s) + 1;
//
//    for(i=0; i<strtam ;i++){
//        if (s[i] > 0)
//    }
//
//}


/* retorna a diferença em segundos dos dois timestamps */
//int diferencaTimestamp(char *t1, char *t2){


//}


/* Le bloco de dados e insere no vetor */
int leBlocoDados(FILE *f, log_t *log){
    linha_t *linha;             /* Estrutura com o atributo e valor     */
//    float   altitude = 0;       /* Salva a altitude                     */
//    float   speed1 = 0;         /* Salva a primeira velocidade lida     */  
//    float   speed2 = 0;         /* Salva a ultima velocidade lida       */
//    float   hrMed1 = 0;         /* Salva o primeiro heart_rate lido     */
//    float   hrmed2 = 0;         /* Salva o ultimo heart_rate lido       */
//    float   cadMed1 = 0;        /* Salva a primeira cadencia lida       */
//    float   cadMed2 = 0;        /* Salva a ultima cadencia lida         */
//    char    *timestamp;         /* String que guarda o timestamp        */
//    int     contVel, contHr, contCad;/* Contador de blocos              */

//    if (!(timestamp = malloc(sizeof(char)*TAMLINHA))){
//        fprintf(stderr, "Erro de alocacao do timestamp\n");
//        return 0;
//    }

    linha = leAtributoValor(f);

    /* Enquanto não for fim do arquivo */
    while (!feof(f)){

        /* Le linhas enquanto linha for diferente de NULL */
        while (linha){

            /* Testa se leu distancia */
            if (!strcmp(linha->atributo, "distance:")){
                log->distancia = atof(linha->valor);
            } //else
//
//            /* Testa se leu altitude */
//            if (!strcmp(linha->atributo, "altitude:"))
//                /* Testa se leu pela primeira vez */
//                if (altitude == 0)
//                    altitude = strtof(linha->valor);
//                else
//                    if (linha->valor > altitude)
//                        log->subAcumulada = log->subAcumulada + (linha->valor - altitude);
//
//            /* Testa se leu cadence */
//            if (!(strcmp(linha->valor, "cadence:"))){
//                cadMed1 = cadMed2;    
//                cadMed2 = strtof(linha->valor);
//            }
//
//            /* Testa se leu heart_rate */
//            if (!(strcmp(linha->valor, "heart_rate:"))){
//                /* Testa heart_rate maximo */
//                if (linha->valor > log->hrMax)
//                    log->hrMax = strtof(linha->valor);
//                hrMed1 = hrMed2;
//                hrMed2 = strtof(linha->valor);
//            }
//
//            /* Testa se leu speed */
//            if (!strcmp(linha->atributo, "speed:")){
//                /* Testa velocidade maxima */
//                if (linha->valor > log->velMax)
//                    log->velMax = strtof(linha->valor);
//                speed1 = speed2;
//                speed2 = strtof(linha->valor);
//            }
//
//            /* Testa se leu timestamp */
//            if (!(strcmp(linha->vetor, "timestamp:"))){
//                /* Testa se leu o primeiro timestamp */
//                if
//            }

            desalocaLinha(linha);
            linha = leAtributoValor(f);
        }

        linha = leAtributoValor(f);
    }
//    free(timestamp);
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
        fprintf(stderr, "Distancia percorrida: %f\n", vetLog[i].distancia);
        fprintf(stderr, "Velocidade Media: %f\n", vetLog[i].velMedia);
        fprintf(stderr, "Velocidade Maxima: %f\n", vetLog[i].velMax);
        fprintf(stderr, "Heart_rate Medio: %f\n", vetLog[i].hrMedio);
        fprintf(stderr, "Heart_rate Maximo: %f\n", vetLog[i].hrMax);
        fprintf(stderr, "Cadencia media: %f\n", vetLog[i].cadMedia);
        fprintf(stderr, "Subida acumulada: %f\n", vetLog[i].subAcumulada);
        fprintf(stdout, "\n");
    }

    return;
}


