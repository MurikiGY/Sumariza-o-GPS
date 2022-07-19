#include "bicicleta.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>


/* Calcula quantidade de arquivos em um diretorio */
int calcNumArquivos(DIR *dir){
    struct dirent   *entry;     /* Estrutura dirent     */
    int             tam = 0;    /* Contador de tamanho  */

    /* Loop de leiura do diretorio */
    while ((entry = readdir(dir)) != NULL)
        if (entry->d_type == DT_REG)
            tam++;

    /* Retorna o ponteiro para o inicio do diretorio */
    rewinddir(dir);

    return tam;
}


/* Concatena caminho <directory>/<file> */
char *makePath(char *dir, char *fileName){
    char *p;    /* Ponteiro de retorno */

    /* aloca string de retorno, soma + 2 por conta do "/" e do "/0" */
    if (!(p = malloc(sizeof(char)*(strlen(dir) + strlen(fileName) + 2)))){
        fprintf(stderr, "Falha de alocacao da string de caminho\n");
        exit(2);
    }

    strncpy(p, dir, strlen(dir) + 1);           /* caminho do diretorio */
    strncat(p, "/", 2);                        
    strncat(p, fileName, strlen(fileName) + 1); /* nome do arquivo */

    return p;
}


/* le arquivos de dados e insere no vetor de estruturas
 * dir      = variavel de acesso do diretorio
 * dirName  = Nome do diretorio
 * vetLog   = Vetor de logs
 * */
int leVetorLogs(DIR *dir, char *dirName, log_t *vetLog){
    FILE            *file;      /* Stream de arquivo        */
    struct dirent   *entry;     /* Estrutura dirent         */
    int             i = 0;      /* Indice do vetor de logs  */
    char            *path;      /* String <pasta>/<arquivo> */
    linha_t         *linha;     /* Estrutura da linha       */
    int             funcOut;    /* Retorno da funcao        */

    /* Loop de leitura do diretorio */
    while((entry = readdir(dir)) != NULL)
        if (entry->d_type == DT_REG){
            
            /* Monta string do caminho */
            path = makePath(dirName, entry->d_name);

            /* Abre o arquivo */
            if (!(file = fopen(path, "r")))
                fprintf(stderr, "Erro em abrir o arquivo: %s\n", entry->d_name);
            else {
                zeraEstrutura(&vetLog[i]);

                /* Le o nome da bicicleta e guarda no vetor */
                funcOut = bikeName(file, &vetLog[i]);
                if (funcOut)
                    return 0;

                /* Le a data da atividade e guarda no vetor */
                funcOut = bikeDate(file, &vetLog[i]);
                if (funcOut)
                    return 0;

                /* Le o restante do arquivo e atribui no vetor */
                funcOut = leBlocoDados(file, &vetLog[i]);
                if (funcOut)
                    return 0;

                /* Fecha o arquivo */
                fclose(file);
                i++;
            }
            free(path);
        }

    return 1;
}


int main (int argc, char **argv){
    DIR     *directory;     /* Stream do diretorio           */
    log_t   *vLog;          /* Vetor de estruturas do log    */
    bike_t  *vBike;         /* Vetor de bikes                */
    int     logTam;         /* Tamanho do vetor de logs      */
    int     bikeTam;        /* Tamanho do vetor de bicicleas */
    int     funcOut;        /* Valor de retorno da funcao    */

    /* Testa parametro */
    if (getopt(argc, argv, "d:") == -1){
        fprintf(stderr, "%s:Parametro errado\n", argv[2]);
        exit(1);
    }

    /* Abre diretorio */
    if (!(directory = opendir(argv[2]))){
        perror("Não foi possivel acesssar o diretorio\n");
        exit(2);
    }

    /* Calcula numero de logs */
    logTam = calcNumArquivos(directory);

    printf("Quantidade de arquivos encontrados: %d\n", logTam);

    /* Testa se existem logs */
    if (logTam == 0){
        printf("Diretorio de logs vazio\n");
        return 1;
    }

    /* Aloca vetor de logs */
    if (!(vLog = malloc(sizeof(log_t)*logTam))){
        fprintf(stderr, "Falha de alocacao do vetor de logs\n");
        exit(1);
    }

    /* Insere dados no vetor de logs */
    funcOut = leVetorLogs(directory, argv[2], vLog);
    if (!funcOut){
        fprintf(stdout, "%d\n", funcOut);
        destroiVetorLog(vLog, logTam);
        return funcOut;
    }

    imprimeVetorLog(vLog, logTam);

    /* Ordena vetor em blocos do nome */

    /* Calcula o numero de bicicletas no vetor */

    /* Aloca estrutura de bicicletas */

    /* Arruma os ponteiros de inicio e fim das bicicletas */

    /* imprime bicicletas */


    destroiVetorLog(vLog, logTam);

    closedir(directory);
    return 0;
}

/* Valores para guardar:
 * do log:
 * {
 *  -Distancia
 *  -velocidade media
 *  -velociade maxima
 *  -HR medio
 *  -HR maximo
 *  -Cadencia media
 *  -Subida acumulada
 *  }
 * da bicicleta
 * {
 */
