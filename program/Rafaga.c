#include "Rafaga.h"
#include <math.h>
#include <stdlib.h>

struct RafagaStr
{
    Bala datos;
    struct RafagaStr * sig;
};

typedef struct RafagaStr * Rafaga;

Rafaga crea_rafaga()
{
    Rafaga nuevo=malloc(sizeof(struct RafagaStr));
    nuevo->datos = NULL;
    nuevo->sig = NULL;

    return(nuevo);
}

void inserta_rafaga( Rafaga raf, Bala b)
{
    Rafaga nuevo = malloc(sizeof(struct RafagaStr));
    nuevo->datos=b;
    nuevo->sig = raf->sig;
    raf->sig = nuevo;

    return;
}
void libera_rafaga(Rafaga raf)
{
    Rafaga aux=raf->sig, aux_2;

    while(aux != NULL)
    {
        aux_2=aux->sig;
        libera_bala(aux->datos);
        free(aux);
        aux = aux_2;
    }
    free(raf);
}

void limpia_rafaga(Rafaga raf)
{
    Rafaga aux=raf->sig, aux_2;

    while(aux != NULL)
    {
        aux_2=aux->sig;
        libera_bala(aux->datos);
        free(aux);
        aux = aux_2;
    }

    raf->sig=NULL;
}

void mueve_rafaga(Rafaga raf, int anchura_pantalla, int altura_pantalla)
{
    Rafaga aux=raf,aux_2=NULL;
    while(aux->sig != NULL)
    {
        mueve_bala(aux->sig->datos);
        if((get_x_bala(aux->sig->datos) > anchura_pantalla)||(get_x_bala(aux->sig->datos)<0)||(get_y_bala(aux->sig->datos) > altura_pantalla)||(get_y_bala(aux->sig->datos) < 0))
        {
            aux_2=aux->sig;
            aux->sig= aux_2->sig;
            libera_bala(aux_2->datos);
            free(aux_2);
            aux_2= NULL;

        }
        else
        {
            aux = aux->sig;
        }
    }

    return;
}

void dibuja_rafaga(Rafaga raf)
{
    Rafaga aux=raf->sig;

    while(aux != NULL)
    {
        dibuja_bala(aux->datos);
        aux = aux->sig;
    }

    return;
}

int colision_rafaga(Rafaga raf, double x, double y, double w, double h)
{
    Rafaga aux=raf->sig, aux2=raf;

    while((aux!=NULL)&&(!colision_bala(aux->datos,x,y,w,h)))
    {
        aux2=aux;
        aux= aux->sig;
    }
    if ((aux!=NULL))
    {
        aux2->sig= aux->sig;
        libera_bala(aux->datos);
        free(aux);
        return 1;
    }
    return 0;
}

int colision_rafaga_especifico(Rafaga raf, double x, double y, double w, double h, int tipo)
{
    Rafaga aux=raf->sig, aux2=raf;

    while((aux!=NULL)&&((!colision_bala(aux->datos,x,y,w,h))||(get_type_bala(aux->datos) != tipo)))
    {
        aux2=aux;
        aux= aux->sig;
    }
    if ((aux!=NULL))
    {
        if(tipo != 6)
        {
            aux2->sig= aux->sig;
            libera_bala(aux->datos);
            free(aux);
        }
        return 1;
    }
    return 0;
}

void elimina_bala_colision_rafaga(Rafaga raf, Escenario rect, int tipo)
{
    Rafaga aux=raf;
    while(aux->sig!=NULL)
    {
        if(solape_suelo(get_x_bala(aux->sig->datos),get_y_bala(aux->sig->datos),get_w_bala(aux->sig->datos),get_h_bala(aux->sig->datos), rect)&&(get_type_bala(aux->sig->datos) == tipo))
        {
            Rafaga borrar=aux->sig;
            aux->sig= aux->sig->sig;
            libera_bala(borrar->datos);
            free(borrar);
        }
        else
        {
            aux= aux->sig;
        }
    }
}

void elimina_balas_tipo(Rafaga raf, int tipo)
{
    Rafaga aux=raf,aux_2=NULL;
    while(aux->sig != NULL)
    {
        if(get_type_bala(aux->sig->datos) == tipo)
        {
            aux_2=aux->sig;
            aux->sig= aux_2->sig;
            libera_bala(aux_2->datos);
            free(aux_2);
            aux_2 = NULL;

        }
        else
        {
            aux = aux->sig;
        }
    }

    return;

}

