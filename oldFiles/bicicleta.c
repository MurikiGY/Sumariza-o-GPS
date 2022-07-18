#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bicicleta.h"

/* Arrumar essa função de acordo com o NLOGS passado por parametro */
int criaBike(bike_t *vBike, char *name, int *vtam){

    /* atribui o nome */
    strcpy(vBike[*vtam].bikeName, name);
    
    /* aloca vetor de logs */
/*    if (!(vBike[*vtam].logVector = malloc(sizeof(logData_t)*NLOGS))){
        fprintf(stderr, "Falha em criar uma nova bicicleta");
        return 0;
    }
*/
    return 1;
}

void destroiBike(bike_t *vBike, int vtam){
    int i;

    /* desaloca vetor de logs */
    for (i=0; i<vtam ;i++){
        free(vBike[i].logVector);
    }

    /* desaloca vetor de bikes */
        free(vBike);

    return;
}

int existeBike(bike_t *vBike, char *name, int *vtam){
    int i;

    /* loop de busca pelo nome */
    for (i=0; i<*vtam ;i++)
        if (!strcmp(vBike[i].bikeName, name))
            return i;

    /* bicicleta nao encontrada */
    return -1;
}

