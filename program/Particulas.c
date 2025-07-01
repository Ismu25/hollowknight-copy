#include "Particulas.h"
#include <stdlib.h>
#include <stdio.h>

struct Particulastr
{
    int x;
    int y;
    int h;
    int w;
    int frame;
    SDL_RendererFlip dir_espejo;
    Animacion imagenes;

};

struct Partstr
{
    struct Particulastr * datos;
    struct Partstr * sig;

};

typedef struct Partstr * Particulas;

Particulas crea_particulas()
{
    Particulas cabezera = malloc(sizeof(struct Partstr));
    cabezera->datos = NULL;
    cabezera->sig = NULL;
    return cabezera;
}

void introduce_particula(Particulas c, int x, int y, int w, int h,SDL_RendererFlip espejo , Animacion anima)
{
    Particulas nuevo= malloc(sizeof(struct Partstr));
    nuevo->datos= malloc(sizeof(struct Particulastr));
    nuevo->datos->x = x;
    nuevo->datos->y = y;
    nuevo->datos->w = w;
    nuevo->datos->h = h;
    nuevo->datos->frame=0;
    nuevo->datos->imagenes = anima;
    nuevo->datos->dir_espejo = espejo;
    nuevo->sig=NULL;

    Particulas aux=c;
    while (aux->sig != NULL)
    {
        aux= aux->sig;
    }
    aux->sig = nuevo;

    return;
}

void limpia_particulas(Particulas c)
{
    Particulas aux,aux2=c->sig;

    while(aux2!=NULL)
    {
        aux=aux2;
        aux2=aux->sig;
        free(aux->datos);
        free(aux);
    }
    c->sig=NULL;
    return;
}

void libera_particulas(Particulas c)
{
    Particulas aux,aux2=c;

    while(aux2!=NULL)
    {
        aux=aux2;
        aux2=aux->sig;
        free(aux->datos);
        free(aux);
    }
    return;
}

void dibuja_particulas(Particulas c)
{
    Particulas aux=c;
    while(aux->sig != NULL)
    {
        if( aux->sig->datos->frame == get_n_acimacion(aux->sig->datos->imagenes))
        {
            Particulas borrar = aux->sig;
            aux->sig = aux->sig->sig;
            free(borrar->datos);
            free(borrar);
        }
        else
        {
            dibuja_animacion(aux->sig->datos->frame,aux->sig->datos->imagenes, aux->sig->datos->x,aux->sig->datos->y,aux->sig->datos->w,aux->sig->datos->h,0,aux->sig->datos->dir_espejo);
            aux->sig->datos->frame = aux->sig->datos->frame + 1;
            aux = aux->sig;
        }
    }
    return;
}

