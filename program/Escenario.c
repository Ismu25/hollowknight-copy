#include "Escenario.h"
#include <stdio.h>
#include <stdlib.h>

struct BlockStruct
{
    int x;
    int y;
    int w;
    int h;
    int visible;
};

struct EscenarioStr
{
    int n_bloques;
    int n_max;
    struct BlockStruct * bloques;
};

typedef struct EscenarioStr * Escenario;

Escenario crear_escenario(int maximo)
{
    if (maximo < 0)
    {
        printf("El numero  %d de bloques del escenario no esta permitido", maximo);
        return NULL;
    }

    Escenario nuevo= malloc(sizeof(struct EscenarioStr));
    nuevo->n_max=maximo;
    nuevo->n_bloques=0;
    if (maximo == 0) nuevo->bloques = NULL;
    else nuevo->bloques=malloc(maximo*sizeof(struct BlockStruct));
    return nuevo;
}

void inserta_bloque(Escenario esc, int x, int y, int w, int h,int visible)
{
    if(esc->n_max != esc->n_bloques)
    {
        esc->bloques[esc->n_bloques].x = x,
                                     esc->bloques[esc->n_bloques].y = y;
        esc->bloques[esc->n_bloques].w = w;
        esc->bloques[esc->n_bloques].h = h;
        esc->bloques[esc->n_bloques].visible = visible;
        esc->n_bloques = esc->n_bloques + 1;
    }
}

Escenario cargar_bloques_achivo (char * a)
{
    FILE * fp;
    fp = fopen(a, "r");
    if(fp != NULL)
    {

        int c;
        fscanf(fp,"%d\n",&c);

        Escenario b= malloc(sizeof(struct EscenarioStr));
        b->n_bloques = c;
        b->n_max=c;
        b->bloques= malloc((c)*sizeof(struct BlockStruct));
        for (int i = 0; i < c; i++)
        {
            fscanf(fp, "%d,%d,%d,%d,%d\n",&(b->bloques[i].x),&(b->bloques[i].y),&(b->bloques[i].w),&(b->bloques[i].h),&(b->bloques[i].visible));
        }
        return b;
    }

    printf("Fallo al abrir el escenario");
    return NULL;
}

int buscar_plataforma_solape (double x, double y, double w, double h,Escenario rect)
{
    for (int i=0; i< rect->n_bloques; i++)
    {
        if(solape_rectangulos(rect->bloques[i].x,rect->bloques[i].y,rect->bloques[i].w,rect->bloques[i].h,x ,y,w,h))
        {
            return i;
        }
    }
    return -1;
}

int buscar_plataforma_entidad_arriba(double x, double y, double w, double h,Escenario rect)
{
    for (int i=0; i< rect->n_bloques; i++)
    {
        if(solape_rectangulos(rect->bloques[i].x,rect->bloques[i].y,rect->bloques[i].w,rect->bloques[i].h,x,y,w,h))
        {
            double py = y+h/2;
            if ( py < rect->bloques[i].y ) return i;
        }
    }
    return 0;
}

Direccicion comp_de_pos_plataforma(double x,double y,double w,double h, Escenario rect)
{
    int i = buscar_plataforma_solape(x,y,w,h,rect);
    double px = x+w/2, py = y+h/2;
    if(i != -1)
    {
        if ( py < rect->bloques[i].y )
        {
            return ARRIBA;
        }
        if ( py > rect->bloques[i].y + rect->bloques[i].h )
        {
            return ABAJO;
        }
        if ( px < rect->bloques[i].x )
        {
            return IZQUIERDA;
        }
        if ( px > rect->bloques[i].x + rect->bloques[i].w )
        {
            return DERECHA;
        }
    }
    return 0;
}

int solape_suelo (double x, double y, double w, double h,Escenario rect)
{
    for (int i=0; i < rect->n_bloques; i++)
    {
        if(solape_rectangulos(rect->bloques[i].x,rect->bloques[i].y,rect->bloques[i].w,rect->bloques[i].h,x ,y,w,h))
        {
            return 1;
        }
    }
    return 0;
}

int solape_suelo_circunferencia(double x, double y, double r,Escenario rect)
{
    for (int i=0; i< rect->n_bloques; i++)
    {
        if(solape_cicunferencia_rectangulo(rect->bloques[i].x,rect->bloques[i].y,rect->bloques[i].w,rect->bloques[i].h,x,y,r))
        {
            return 1;
        }
    }
    return 0;
}

int solape_con_bloque(double x, double y, double w, double h,Escenario rect,int plat)
{
    if(solape_rectangulos(rect->bloques[plat].x,rect->bloques[plat].y,rect->bloques[plat].w,rect->bloques[plat].h,x ,y,w,h))
    {
        return 1;
    }
    return 0;
}

void dibuja_suelo(Imagen img, Escenario s)
{
    for(int i= 0; i < s->n_bloques; i++)
    {
        if(s->bloques[i].visible) Pantalla_DibujaImagen(img,s->bloques[i].x,s->bloques[i].y-3,s->bloques[i].w,s->bloques[i].h+3);
    }
}

void libera_escenario(Escenario esc)
{
    free(esc->bloques);
    free(esc);
}


