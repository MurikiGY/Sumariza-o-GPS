#ifndef _LOG_
#define _LOG_

#define LOGLINESIZE 50

/* arquivo que define as operações realizadas no log */

/* le uma linha do .log */
void leLinha(char *linha, FILE *file);

/* le e retorna o valor lido */
void leAtributoValor (char *atributo, char *valor, FILE *logFile);










#endif
