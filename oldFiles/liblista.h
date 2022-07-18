#ifndef _LIBLISTA_
#define _LIBLISTA_

#include "bicicleta.h"

/* no de dados da bicicleta */
struct nodo_l {
    char nomeMarca[BIKENAMESIZE];
    int nlogs;
    struct nodo_l *prox;
};
typedef struct nodo_l nodo_l_t;

/* lista da bicicleta */
struct lista {
    int tamanho;
    nodo_l_t *head;
};
typedef struct lista lista_t;

/* no com os nomes dos arquivos */



/* Cria uma lista e retorna o ponteiro */
lista_t *lista_cria();

/* Destroi/Desaloca a lista */
lista_t *lista_destroi (lista_t *l);

/* Retorna tamanho da lista */
int lista_tamanho(lista_t *l);

/* Procura uma chave na lista
 * incrementa numero de passagens se encontrar e retorna 1
 * retorna 0 do contrario */
int lista_pertence_incrementa(lista_t *l, char *nome);

/* insere um novo nó no fim da lista
 * em sucesso returna 1
 * em falha retorna 0 */
int lista_insere_fim(lista_t *l, char *nome);

/* remove o no do inicio
 * retorna nlogs e nome por parametro
 * destroi o no */
int lista_retira_inicio(lista_t *l, char *nome);

/* imprime os nodos da lista
 * imprime o nome
 * imprime o numero de logs */
void lista_imprime(lista_t *l);



#endif
