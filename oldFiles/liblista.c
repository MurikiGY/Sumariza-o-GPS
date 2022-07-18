#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "liblista.h"

/* Cria uma lista e retorna o ponteiro */
lista_t *lista_cria(){
    lista_t *l;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->tamanho = 0;
    l->head = NULL;

    return l;
}


/* Destroi/Desaloca a lista */
lista_t * lista_destroi(lista_t *l){
    nodo_l_t *aux;       /* Auxiliar de deslocamento */

    /* free do primeiro ao ultimo nodo */
    while (l->head != NULL)
    {
        aux = l->head->prox;
        free(l->head);
        l->head = aux;
    }

    l->tamanho = 0;
    free(l);
    return NULL;
}


/* Retorna tamanho da lista */
int lista_tamanho(lista_t *l){
    return l->tamanho;
}


/* Procura uma chave na lista
 * incrementa numero de passagens se encontrar e retorna 1
 * retorna 0 do contrario */
int lista_pertence_incrementa(lista_t *l, char *nome){
    nodo_l_t *aux;      /* auxiliar de deslocamento */

    /* aux percorre a lista */
    aux = l->head;
    while (aux != NULL){
        if (!(strcmp(aux->nomeMarca, nome))){
            (aux->nlogs)++;
            return 1;
        }
        aux = aux->prox;
    }

    /* elemento nao encontrado */
    return 0;
}


/* insere um novo nó no fim da lista
 * em sucesso retorna 1
 * em falha retorna 0 */
int lista_insere_fim(lista_t *l, char *nome){
    nodo_l_t *aux;      /* auxiliar de deslocamento */
    nodo_l_t *nodo;

    /* Testa alocacao do nodo */
    if (!(nodo = malloc(sizeof(nodo_l_t))))
        return 0;

    /* Configura nodo */
    strcpy(nodo->nomeMarca, nome);
    nodo->nlogs = 1;    /* 1 pois eh o primeiro log a ser lido */
    nodo->prox = NULL;

    /* Testa lista vazia */
    if (l->head == NULL){
        l->head = nodo;
        (l->tamanho)++;
        return 1;
    }

    /* faz aux apontar pro ultimo nodo da lista */
    aux = l->head;
    while (aux->prox != NULL)
        aux = aux->prox;

    /* Ultimo nodo aponta para o novo nodo */
    aux->prox = nodo;
    (l->tamanho)++;
    return 1;
}


/* remove o no do inicio
 * retorna nlogs e nome por parametro
 * retorna -1 em caso de lista vazia
 * destroi o no */
int lista_retira_inicio(lista_t *l, char *nome){
    nodo_l_t *aux;      /* auxiliar de deslocamento */
    int logs;           /* guarda numero de logs */

    /* testa lista vazia */
    if (l->tamanho == 0)
        return -1;

    /* altera ponteiros */
    aux = l->head;
    l->head = l->head->prox;
    strcpy(nome, aux->nomeMarca);
    logs = aux->nlogs;
    free(aux);

    return logs;
}


/* imprime os nodos da lista
 * imprime o nome
 * imprime o numero de logs */
void lista_imprime(lista_t *l){
    nodo_l_t *aux;

    if (!l->tamanho == 0){
        aux = l->head;
        while (aux != NULL){
            printf("Nome da bicicleta: %s\n", aux->nomeMarca);
            printf("Numero de logs: %d\n", aux->nlogs);
            aux = aux->prox;
        }
    }
}
