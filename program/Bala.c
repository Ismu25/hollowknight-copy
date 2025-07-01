#include "Bala.h"

#include <stdio.h>
#include <stdlib.h>
struct BalaStruct
{
    double x;
    double y;
    double vx;
    double vy;
    double h;
    double w;
    SDL_RendererFlip dir_espejo;
    Imagen img;
    int type;
};

typedef struct BalaStruct * Bala;

Bala crea_bala ( Imagen textura, double x, double y, double vx, double vy, double h, double w,int type)
{
    Bala bala = malloc(sizeof(struct BalaStruct));
    bala->x= x;
    bala->y= y;
    bala->vx= vx;
    bala->vy= vy;
    bala->h= h;
    bala->w= w;
    bala->img=textura;
    bala->type=type;

    if(vx > 0)
    {
        bala->dir_espejo=SDL_FLIP_NONE;
    }
    else
    {
        bala->dir_espejo=SDL_FLIP_HORIZONTAL;
    }

    return bala;
};
void libera_bala( Bala a)
{
    free(a);
    return;
};
void mueve_bala(Bala a)
{
    a->x= a->x + 10 * a->vx;
    a->y= a->y + 10 * a->vy;
};
void dibuja_bala(Bala a)
{
    if (a->img != NULL) Pantalla_DibujaImagenTransformada(a->img,a->x,a->y,a->w,a->h,0,a->dir_espejo);
};
double get_x_bala( Bala b )
{
    return(b->x);
}
double get_y_bala( Bala b )
{
    return(b->y);
}
double get_w_bala( Bala b )
{
    return(b->w);
}
double get_h_bala( Bala b )
{
    return(b->h);
}
int get_type_bala( Bala b)
{
    return(b->type);
}
int colision_bala( Bala b, double x, double y, double w, double h)
{
    if(b->type == 0 && solape_cicunferencia_rectangulo(x,y,w,h,b->x + b->w/2,b->y +b->h/2, b->h))
    {
        return 1;
    }
    else if (solape_rectangulos(x,y,w,h,b->x,b->y,b->w,b->h))
    {
        return 1;
    }

    return 0;

}
