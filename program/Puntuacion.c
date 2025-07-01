#include <stdlib.h>
#include <stdio.h>
#include "Puntuacion.h"



struct PuntuacionesStr
{
    int capacity;
    int * points;
    char ** names;
};

Puntuaciones crear_puntuacion(int capacity)
{
    Puntuaciones punts = malloc(sizeof(struct PuntuacionesStr));
    punts->capacity = capacity;
    punts->points = malloc(capacity * sizeof(int));
    punts->names = malloc(capacity * sizeof(char*));
    for(int i=0; i<capacity; i++) punts->names[i] = malloc(4 * sizeof(char));

    int i = 0;
    while(i < capacity)
    {
        punts->points[i] = 25269;
        punts->names[i][0] = 'N';
        punts->names[i][1] = 'U';
        punts->names[i][2] = 'L';
        punts->names[i][3] = 'L';
        i++;
    }

    return punts;
}

void libera_puntuacion(Puntuaciones punts)
{
    for(int i=0; i < punts->capacity; i++)
        free(punts->names[i]);
    free(punts->names);
    free(punts->points);
    free(punts);
}



Puntuaciones leer_puntuacion(char * ruta)
{
    FILE * puntos = NULL;
    puntos = fopen(ruta,"a+");

    if(puntos == NULL) return crear_puntuacion(DEFAULT_CAPACITY);
    Puntuaciones punts = crear_puntuacion(DEFAULT_CAPACITY);

    int i = 0;
    while(!feof(puntos) && (i < DEFAULT_CAPACITY))
    {
        fscanf(puntos,"%c%c%c%c %d\n",&(punts->names[i][0]),&(punts->names[i][1]),
               &(punts->names[i][2]),&(punts->names[i][3]),&(punts->points[i]));
        i++;
    }


    fclose(puntos);
    return punts;
}

void introducir_puntuacion(Puntuaciones punts, int puntos, char * nombre)
{
    int maximo = punts->points[0];
    int indice = 0;
    for(int i = 1; i < punts->capacity; i++)
    {
        if (punts->points[i] > maximo)
        {
            indice = i;
            maximo = punts->points[i];
        }
    }

    if (puntos < maximo)
    {
        punts->points[indice] = puntos;
        punts->names[indice][0] = nombre[0];
        punts->names[indice][1] = nombre[1];
        punts->names[indice][2] = nombre[2];
        punts->names[indice][3] = nombre[3];
    }
}

void guardar_puntuacion_archivo(Puntuaciones punts, char * ruta)
{
    FILE * puntos = NULL;
    puntos = fopen(ruta,"w");

    if (puntos == NULL) return;
    for (int i=0; i < punts->capacity; i++)
    {
        fprintf(puntos,"%c%c%c%c %d\n", punts->names[i][0],punts->names[i][1],
                punts->names[i][2], punts->names[i][3], punts->points[i]);
    }
    fclose(puntos);
}

int get_puntuacion(Puntuaciones punt, int indice)
{
    return punt->points[indice];
}

char * get_nombre(Puntuaciones punt, int indice)
{
    return punt->names[indice];
}
