#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POSICIONES_SCHEDULER 10


static int infi = 0;

typedef struct proceso{
    int procesador;
    int id_proceso;
    int prioridad;
    char estado[10];
} proceso;

proceso* scheduling[POSICIONES_SCHEDULER];

/** OK Asigna el siguiente estado según el orden enunciado antes */
void asignaEstado(proceso*);
/** OK Ingresa el proceso al Scheduler en el primer espacio libre que encuentre*/
void ingresaProceso();
/**Quita el proceso de la cola liberando y retornando el lugar liberado*/
int terminaProceso();
/**Recorrera todos los procesos de la cola, haciendo el cambio del estado de los mismos*/
void recorreCola();
/** OK Lista los procesos de la cola*/
void mostrarScheduler();

int main (void){
    for(int i = 0; i < POSICIONES_SCHEDULER; i++){  /**pongo cada posicion del scheduler en NULL como me indica la consigna**/
        scheduling[i] = NULL;
    }

    for(int i = 0; i < POSICIONES_SCHEDULER; i++){
        ingresaProceso();
    }

    for(int i = 0; i < 5; i++){
        asignaEstado(scheduling[i]);  //Prueba de la funcion que cambia los estados
    }


    printf("Primer muestra:\n");
    mostrarScheduler();

    printf("Segunda muestra:\n");
    mostrarScheduler();



    return 0;
}

void ingresaProceso(){
    for(int i = 0; i < POSICIONES_SCHEDULER; i++){
        if(scheduling[i] == NULL){
            scheduling[i] = malloc(sizeof(proceso));
            scheduling[i] ->procesador = 0;
            scheduling[i] ->id_proceso = rand() % 9999;/**tengo que poner un num random**/
            scheduling[i] ->prioridad = infi++;
            strcpy(scheduling[i] ->estado, "NUEVO");
            return; /**pongo el return aca asi no sigue el bucle**/
        }

    }
    printf("No hay lugar en las posiciones de scheduling\n");
}

void mostrarScheduler(){
    for(int i = 0; i < POSICIONES_SCHEDULER; i++){
        printf("[%d]\t", i);
        if(scheduling[i] != NULL){
            printf("%d, %d, %d, '%s'\n", scheduling[i]->procesador,
            scheduling[i]->id_proceso, scheduling[i]->prioridad, scheduling[i]->estado);
        }
    }
}

void asignaEstado(proceso *prc){
    char *cpy_estado = prc->estado; /**simplemente lo copio para trabajar mas facil**/
    if(strcmp(cpy_estado, "NUEVO") == 0){  /**comparo y si es true (igual a 0) le cambio el estado**/
        strcpy(cpy_estado, "LISTO");
        return;
    }
    if(strcmp(cpy_estado, "LISTO") == 0){
        strcpy(cpy_estado, "CORRIENDO");
        return;
    }
    if(strcmp(cpy_estado, "CORRIENDO") == 0){
        strcpy(cpy_estado, "TERMINADO");
        return;
    }
}

int terminaProceso(){
    for(int i = 0; i < POSICIONES_SCHEDULER; i++){
        if(scheduling[i] != NULL && strcmp(scheduling[i]->estado, "TERMINADO")){
            free(scheduling[i]);
            scheduling[i] = NULL;
            return i;
        }
    }
    return -1;  /**lo pongo porque tiene que devolver un int, si llega hasta aqui se rompe**/
}

void recorreCola(){

}



