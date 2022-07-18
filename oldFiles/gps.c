#include "bicicleta.h"
#include "liblista.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

void makePath(char *p, char *dir, char *fileName){

    strncpy(p, dir, strlen(dir)+1);  /* caminho do diretorio */
    strcat(p, "/");
    strcat(p, fileName); /* nome do arquivo */

    return;
}

bike_t *leAtribuiEstrutura(DIR *dir, char *logDir, int *nBike){
    FILE *file;             /* Abre stram do arquivo */
    struct dirent *entry;   /* estrutura dirent */
    lista_t *bLista;        /* lista ligada */
    bike_t *b;              /* estrutura de retorno */
    int nlogs;              /* numero de logs para ser alocado */
    char *path;
    char bNome[LOGLINESIZE]; /* String do nome da bicicleta */
    char gear[LOGLINESIZE]; /* string que guarda palavra gear */
    int i;

    /* Cria a lista */
    bLista = lista_cria();

    /* looIR *dip de leitura dos logs */
    while ((entry = readdir(dir)) != NULL)
        /* testa se eh um arquivo */
        if (entry->d_type == DT_REG){

            if (!(path = malloc(sizeof(char)*(strlen(logDir) + strlen(entry->d_name) + 3)))){
                fprintf(stderr, "Erro de alocacao no caminho");
                exit(5);
            }

            /* abre o arquivo de log, avisa se der erro */
            makePath(path, logDir, entry->d_name);
            if (!(file = fopen(path, "r")))
                fprintf(stderr, "Falha em abrir o log\n");

            /* le a primeira linha do log
             * retorna o nome por parametro */
            leAtributoValor(gear, bNome, file);
            if (strcmp(gear, "Gear"))
                printf("Nome de bicicleta invalido\n");

            /* procura nome na lista, incrementa log se encontrar
             * insere novo no do contrario */
            if (!lista_pertence_incrementa(bLista, bNome))
                    lista_insere_fim(bLista, bNome);

            free(path);
            fclose(file);
        }

    /* imprime a lista para debug */
//    lista_imprime(bLista);

    /* numero de bicicletas eh o tamanho da lista */
    *nBike = lista_tamanho(bLista);
//    printf("%d\n", *nBike);

            /* até aqui funciona */

    /* aloca vetor de IR *dibicicletas */
    if(!(b = malloc(sizeof(bike_t)*(*nBike)))){
        fprintf(stderr, "Erro de alocacao da estrutura\n");
        exit(3);
    }

    /* guarda o nome e aloca vetor de logs para cada bicicleta */
    for (i=0; i<(*nBike) ;i++){
        nlogs = lista_retira_inicio(bLista, bNome);
        if (nlogs == -1)
            fprintf(stderr, "Lista vazia\n");

        printf("%s\n", bNome);
        printf("%d\n", nlogs);


        strcpy(b[i].bikeName, bNome);
        b[i].nLogs = nlogs;
        if (!(b[i].logVector = malloc(sizeof(logData_t)*nlogs))){
            fprintf(stderr, "Erro de alocacao no vetor de logs\n");
            exit(4);
        }
        
    }

    bLista = lista_destroi(bLista);

    return b;
}


/* scanea arquivos e coloca na estrutura */
//void scanlogs(bike_t* b, int *bTam){



//IR *di

//}



int main (int argc, char **argv){
    DIR *directory;         /* Abre stream do diretorio */
    //lista_t *lFiles;        /* Lista que guarda o nome dos arquivos */
    bike_t *bike;           /* Vetor de estruturas de bicicletas */
    int nBikes = 0;         /* tamanho do vetor de bicicletas */

    /* Testa parametro */
    if (getopt(argc, argv, "d:") == -1){
        fprintf(stderr, "%s:Parametro errado\n", argv[2]);
        exit(1);
    }

    /* abre o caminho do diretorio de logs */
    if (!(directory = opendir(argv[2]))){
        perror("Não foi possivel acesssar o diretorio\n");
        exit(2);
    }

    /* Retorna a estrutura alocada depois de ler os logs */
    bike = leAtribuiEstrutura(directory, argv[2], &nBikes);

    /* Reinicia ponteiro da stream do diretorio */
    rewinddir(directory);

    /* le os atributos dos logs e joga na estrutura */
    //scanLogs(bike, &nBikes);

    /* imprime os dados */

    /* destroi a estrutura */
    destroiBike(bike, nBikes);

    closedir(directory);

    return 0;
}

