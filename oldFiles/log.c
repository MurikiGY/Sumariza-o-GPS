#include <stdio.h>
#include <string.h>

#include "log.h"

void leLinha (char *linha, FILE *file){
    fgets(linha, LOGLINESIZE, file);
    linha[strcspn(linha, "\n")] = '\0';
    return;
}

/* le e retorna o valor lido */
void leAtributoValor (char *atributo, char *valor, FILE *logFile){
    char logLine[LOGLINESIZE];

    /* logLine recebe a string do .log */
    leLinha(logLine, logFile);

    /* guarda o atributo */
    strcpy(atributo, strtok(logLine, ": "));

    /* guarda o valor da linha */
    strcpy(valor, strtok(NULL, "\0"));
}


