#include "Animacion.h"
#include <stdlib.h>
#include <stdio.h>

struct Animestr
{
    int numero_frames;
    Imagen * frames;
};

typedef struct Animestr * Animacion;

void dibuja_animacion(int instancia, Animacion a, double x, double y, double w, double h, double ang, SDL_RendererFlip dir_espejo)
{
    Pantalla_DibujaImagenTransformada(a->frames[instancia % a->numero_frames],x,y,w,h,ang,dir_espejo);
}

void dibuja_animacion_reversible(int instancia, Animacion a, double x, double y, double w, double h, double ang, SDL_RendererFlip dir_espejo)
{

    int i = instancia % (a->numero_frames * 2 -1);
    if(i > (a->numero_frames-1))
    {
        i= (a->numero_frames-1)*2 - i;
    }
    Pantalla_DibujaImagenTransformada(a->frames[i],x,y,w,h,ang,dir_espejo);
    return;
}

Animacion carga_animacion(int n, char * strg)
{
    if((n > 10)||(n<1))
    {
        printf("El numero de imagenes indicado para %s no esta soportado : %d",strg,n);
        return NULL;
    }

    Animacion nuevo=malloc(sizeof(struct Animestr));
    nuevo->numero_frames=n;
    nuevo->frames= malloc(n * sizeof(Imagen));

    int i=99,k=0;
    char copia[100];

    while(strg[k] != '\0')
    {
        if(strg[k] == '#') i=k;
        copia[k]=strg[k];
        k++;
    }
    copia[k] = '\0';

    for (int j=0; j<n; j++)
    {
        copia[i] = j + '0';
        nuevo->frames[j]= Pantalla_ImagenLee(copia,255);
    }
    return nuevo;
}

int get_n_acimacion(Animacion a)
{
    return a->numero_frames;
}

void libera_animacion(Animacion a)
{
    for (int i=0; i < a->numero_frames; i++)
    {
        Pantalla_ImagenLibera(a->frames[i]);
    }
    free(a->frames);
    free(a);
}

