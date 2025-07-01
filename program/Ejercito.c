#include "Ejercito.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct EjercitoStr
{
    int max;
    int numero_enemigos;
    Particulas muertos;
    Enemigo * enemigos;
};

typedef struct EjercitoStr * Ejercito;

Ejercito crea_ejercito(int maximo)
{
    Ejercito nuevo = malloc(sizeof(struct EjercitoStr));
    nuevo->numero_enemigos = 0;
    if (maximo == 0) nuevo->enemigos = NULL;
    else nuevo->enemigos= malloc(maximo*sizeof(Enemigo));
    nuevo->max= maximo;
    nuevo->muertos = crea_particulas();
    return nuevo;
};

void libera_ejercito( Ejercito e )
{
    libera_particulas(e->muertos);
    for (int i=0; i < e->numero_enemigos; i++)
    {
        libera_enemigo(e->enemigos[i]);
    }
    free(e);
};

void limpia_ejercito( Ejercito e )
{
    for (int i=0; i < e->numero_enemigos; i++)
    {
        libera_enemigo(e->enemigos[i]);
    }
    e->numero_enemigos=0;
}

void inserta_enemigo(Ejercito e, TipoEnemigo tipo_enemigo,double x,double y,double h,double w,int vida, Animacion animacion_movimiento, Animacion animacion_muerte, Animacion animacion_atk)
{


    if (e->numero_enemigos == e->max)
    {
        printf("No queda hueco en el ejercito");
        return;
    }

    e->enemigos[e->numero_enemigos] = crea_enemigo(tipo_enemigo,x,y,h,w,vida,animacion_movimiento,animacion_muerte,animacion_atk);
    e->numero_enemigos = e->numero_enemigos + 1;

};

void dibuja_ejercito( Ejercito e)
{
    for(int i=0; i < e->numero_enemigos; i++)
    {
        dibuja_enemigo(e->enemigos[i]);
    }
    dibuja_particulas(e->muertos);
};

int colision_ejercito_objeto( Ejercito e, double x, double y, double w, double h )
{
    for (int i=0; i < e->numero_enemigos; i++)
    {
        if (solape_enemigo(e->enemigos[i],x,y,w,h)) return 1;
    }
    return 0;
};

void mueve_ejercito(Ejercito e, Escenario s,double center_x, double center_y)
{
    for(int i=0; i < e->numero_enemigos; i++)
    {
        mueve_enemigo(e->enemigos[i],s,center_x,center_y);
    }
};

int colision_ejercito_rafaga( Ejercito e, Rafaga r, int tipo_bala )
{
    int n=e->numero_enemigos;
    for (int i=0; i < e->numero_enemigos; i++)
    {
        if(colision_enemigo_rafaga(e->enemigos[i],r,tipo_bala))
        {
            if (vida_enemigo(e->enemigos[i]) <= 0)
            {
                if(get_tipo_enemigo(e->enemigos[i]) == MULTIPLICADOR)
                {
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i])+10,get_y_enemigo(e->enemigos[i]),25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i])+10,25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i])-10,25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                }
                introduce_particula(e->muertos,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i]),get_w_enemigo(e->enemigos[i]),get_h_enemigo(e->enemigos[i]),get_dir_espejo_enemigo(e->enemigos[i]),muerte_enemigo(e->enemigos[i]));
                libera_enemigo(e->enemigos[i]);
                if(e->numero_enemigos > 1) e->enemigos[i] = e->enemigos[e->numero_enemigos-1];
                e->numero_enemigos = e->numero_enemigos - 1;
                i= i - 1;
            }
        }
    }
    return (n - e->numero_enemigos);
};

void ejercito_crea_balas(Ejercito e, int tipo, Rafaga r, Imagen img,double center_x,double center_y)
{
    for(int i=0; i < e->numero_enemigos; i++)
    {
        if(get_tipo_enemigo(e->enemigos[i]) == tipo)
        {
            enemigo_crea_bala(e->enemigos[i],r,img,center_x,center_y);
        }
    }
};

void ejercito_crea_balas_compl(Ejercito e, Rafaga r, Imagen img,double center_x,double center_y)
{
    for(int i=0; i < e->numero_enemigos; i++)
    {
        if(get_tipo_enemigo(e->enemigos[i]) == DISPARADORDOBLE
                || get_tipo_enemigo(e->enemigos[i]) == DISTANCIADOR)
        {
            enemigo_crea_bala(e->enemigos[i],r,img,center_x,center_y);
        }
    }
};

int get_n_enemigos(Ejercito e)
{
    return e->numero_enemigos;
}

int colision_ejercito_objeto_damage(Ejercito e, double x, double y, double w, double h, int damage)
{

    int n=e->numero_enemigos;
    for (int i=0; i < e->numero_enemigos; i++)
    {
        if(colision_enemigo_objeto_damage(e->enemigos[i],x,y,w,h,damage))
        {
            if(vida_enemigo(e->enemigos[i]) <= 0)
            {
                if(get_tipo_enemigo(e->enemigos[i]) == MULTIPLICADOR)
                {
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i])+10,get_y_enemigo(e->enemigos[i]),25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i])+10,25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                    inserta_enemigo(e,VOLADORULTRARAPIDO,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i])-10,25,25,10,
                                    get_mov_enemigo(e->enemigos[i]),get_muerte_enemigo(e->enemigos[i]),get_atk_enemigo(e->enemigos[i]));
                }
                introduce_particula(e->muertos,get_x_enemigo(e->enemigos[i]),get_y_enemigo(e->enemigos[i]),get_w_enemigo(e->enemigos[i]),get_h_enemigo(e->enemigos[i]),get_dir_espejo_enemigo(e->enemigos[i]),muerte_enemigo(e->enemigos[i]));
                libera_enemigo(e->enemigos[i]);
                if(e->numero_enemigos > 1) e->enemigos[i] = e->enemigos[e->numero_enemigos-1];
                e->numero_enemigos = e->numero_enemigos - 1;
                i= i - 1;
            }
        }
    }
    return (n - e->numero_enemigos);
}

