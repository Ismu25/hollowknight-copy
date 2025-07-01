#include "Enemigo.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct EnemigoStr
{
    TipoEnemigo tipo_enemigo;
    double x;
    double y;
    double vx;
    double vy;
    double h;
    double w;
    int vida;
    int atk_timer;
    int atk_stop;
    int tiempo_de_invinvibilidad;
    int estado_animacion;
    int instante_frame;
    SDL_RendererFlip dir_espejo;
    Animacion animaciones[3];
    int first;

};

typedef struct EnemigoStr * Enemigo;

Enemigo crea_enemigo(TipoEnemigo tipo_enemigo,double x,double y,double h,double w,int vida, Animacion animacion_movimiento, Animacion animacion_muerte, Animacion animacion_atk)
{

    Enemigo e= malloc(sizeof(struct EnemigoStr));
    e->tipo_enemigo = tipo_enemigo;
    e->x = x;
    e->y = y;
    e->vx = 0;
    e->vy = 0;
    e->h = h;
    e->w = w;
    e->vida = vida;
    e->atk_timer = 0;
    e->atk_stop = 0;
    e->tiempo_de_invinvibilidad = 0;
    e->estado_animacion = 0;
    e->dir_espejo = SDL_FLIP_HORIZONTAL;
    e->animaciones[0] = animacion_movimiento;
    e->animaciones[2] = animacion_muerte;
    e->animaciones[1] = animacion_atk;
    e->instante_frame= 0;
    e->first = 0;
    return e;

}

void dibuja_enemigo( Enemigo e)
{
    dibuja_animacion_reversible(e->instante_frame,e->animaciones[e->estado_animacion],e->x,e->y,e->w,e->h,0,e->dir_espejo);
    e->instante_frame= e->instante_frame + 1;
    if(e->estado_animacion==1 && e->instante_frame == get_n_acimacion(e->animaciones[1])) e->estado_animacion= 0;
};

int solape_enemigo(Enemigo e, double x, double y, double w, double h)
{
    if (solape_rectangulos( e->x,e->y,e->w,e->h,x,y,w,h)) return 1;
    return 0;
}
void mueve_enemigo(Enemigo e,Escenario s,double center_x, double center_y)
{
    if(e->atk_stop == 0)
    {
        double m=0;

        switch (e->tipo_enemigo)
        {
        case DISTANCIADOR:
        case DISPARADORDOBLE:
            e->vx = center_x - e->x;
            e->vy = center_y - e->y;

            m = sqrt( e->vx*e->vx + e->vy*e->vy );
            if ( m > 0 )
            {
                e->vy = e->vy / m;
                e->vx = e->vx / m;
            }


            if(solape_cicunferencia_rectangulo(e->x,e->y,e->w,e->h,center_x,center_y,70))
            {
                e->vx =  -e->vx;
                e->vy =  -e->vy;
            }
            else if(solape_cicunferencia_rectangulo(e->x,e->y,e->w,e->h,center_x,center_y,120))
            {
                e->vx = 0;
                e->vy = 0;
            }

            e->x = e->x + 3 * e->vx;
            e->y = e->y + 3 * e->vy;
            break;

        case MULTIPLICADOR:
        case VOLARAPIDO:

            e->vx = center_x - e->x;
            e->vy = center_y - e->y;

            m = sqrt( e->vx*e->vx + e->vy*e->vy );
            if ( m > 0 )
            {
                e->vy = e->vy / m;
                e->vx = e->vx / m;
            }

            if(solape_cicunferencia_rectangulo(e->x,e->y,e->w,e->h,center_x,center_y,6))
            {
                e->vx =  0;
                e->vy =  0;
            }

            e->x = e->x + 4 * e->vx;
            e->y = e->y + 4 * e->vy;
            break;

        case VOLADORULTRARAPIDO:
            e->vx = center_x - e->x;
            e->vy = center_y - e->y;

            m = sqrt( e->vx*e->vx + e->vy*e->vy );
            if ( m > 0 )
            {
                e->vy = e->vy / m;
                e->vx = e->vx / m;
            }

            if(solape_cicunferencia_rectangulo(e->x,e->y,e->w,e->h,center_x,center_y,6))
            {
                e->vx =  0;
                e->vy =  0;
            }

            e->x = e->x + 5 * e->vx;
            e->y = e->y + 5 * e->vy;
            break;

        case DESLIZASUELOS:
            e->vy = e->vy + 0.8;

            e->x = e->x + e->vx;
            e->y = e->y + e->vy;
            int p_cont_suelo= buscar_plataforma_entidad_arriba(e->x,e->y,e->w,e->h,s);
            if(!solape_con_bloque(e->x-10,e->y+e->h,2,2,s,p_cont_suelo) && e->dir_espejo==SDL_FLIP_NONE)
            {
                e->vx = 0.7;
                e->dir_espejo=SDL_FLIP_HORIZONTAL;
            }
            else if(!solape_con_bloque(e->x+e->w+8,e->y+e->h,2,2,s,p_cont_suelo) && e->dir_espejo==SDL_FLIP_HORIZONTAL)
            {
                e->vx = -0.7;
                e->dir_espejo=SDL_FLIP_NONE;
            }
            break;

        default:
            e->vx = center_x - e->x;
            e->vy = center_y - e->y;

            m = sqrt( e->vx*e->vx + e->vy*e->vy );
            if ( m > 0 )
            {
                e->vy = e->vy / m;
                e->vx = e->vx / m;
            }

            if(solape_cicunferencia_rectangulo(e->x,e->y,e->w,e->h,center_x,center_y,6))
            {
                e->vx =  0;
                e->vy =  0;
            }

            e->x = e->x + 2 * e->vx;
            e->y = e->y + 2 * e->vy;
        }


        if(solape_suelo(e->x,e->y,e->w,e->h,s))
        {
            e->vy = 0;
        }

        if(e->vx < -0.001)
        {
            e->dir_espejo = SDL_FLIP_NONE;
        }
        else if(e->vx > 0.001)
        {
            e->dir_espejo = SDL_FLIP_HORIZONTAL;
        }

        Direccicion posc;
        while((posc = comp_de_pos_plataforma(e->x,e->y,e->w,e->h,s)) != 0)
        {
            int j=buscar_plataforma_solape(e->x,e->y,e->w,e->h,s);
            switch(posc)
            {
            case IZQUIERDA:

                while(solape_con_bloque(e->x,e->y,e->w,e->h,s,j))
                {
                    e->x = e->x - 2;
                }
                e->y = e->y + 3 * e->vy;
                break;

            case DERECHA:

                while(solape_con_bloque(e->x,e->y,e->w,e->h,s,j))
                {
                    e->x = e->x + 2;
                }
                e->y = e->y + 3 * e->vy;
                break;

            case ARRIBA:

                while(solape_con_bloque(e->x,e->y,e->w,e->h,s,j))
                {
                    e->y = e->y - 0.1;
                }
                e->x = e->x + 3 * e->vx;
                break;

            case ABAJO:

                while(solape_con_bloque(e->x,e->y,e->w,e->h,s,j))
                {
                    e->y = e->y + 0.1;
                }
                e->x = e->x + 3 * e->vx;
                break;
            }
        }

    }
    else e->atk_stop = e->atk_stop - 1;

    if (e->tiempo_de_invinvibilidad > 0) e->tiempo_de_invinvibilidad = e->tiempo_de_invinvibilidad - 1;
}

int vida_enemigo(Enemigo e)
{
    return e->vida;
}

Animacion muerte_enemigo(Enemigo e)
{
    return e->animaciones[2];
}

double get_x_enemigo(Enemigo e)
{
    return e->x;
}

double get_y_enemigo(Enemigo e)
{
    return e->y;
}

double get_w_enemigo(Enemigo e)
{
    return e->w;
}

double get_h_enemigo(Enemigo e)
{
    return e->h;
}

Animacion get_mov_enemigo(Enemigo e)
{
    return e->animaciones[0];
}

Animacion get_atk_enemigo(Enemigo e)
{
    return e->animaciones[1] ;
}

Animacion get_muerte_enemigo(Enemigo e)
{
    return e->animaciones[2] ;
}

SDL_RendererFlip get_dir_espejo_enemigo(Enemigo e)
{
    return e->dir_espejo;
}

void enemigo_crea_bala(Enemigo e, Rafaga r, Imagen img,double center_x,double center_y)
{
    if(e->atk_timer >= 100 || ((e->atk_timer >= 45 && e->first == 1) && e->tipo_enemigo ==  DISPARADORDOBLE))
    {
        double vx = center_x - e->x;
        double vy = center_y - e->y;

        double m = sqrt( vx*vx + vy*vy );
        if ( m > 0 )
        {
            vy = vy / m;
            vx = vx / m;
        }


        inserta_rafaga(r,crea_bala(img,e->x,e->y,vx,vy,20,20,0));
        e->atk_timer = 0;
        e->atk_stop= 10;
        e->atk_timer= (rand() % 50);
        e->estado_animacion= 1;
        e->instante_frame=0;
        e->first = !e->first;
    }
    else
    {
        e->atk_timer += 1;
    }
}

TipoEnemigo get_tipo_enemigo(Enemigo e)
{
    return e->tipo_enemigo;
}

void libera_enemigo(Enemigo e)
{
    free (e);
}

int colision_enemigo_rafaga(Enemigo e , Rafaga r, int tipo_bala)
{
    if((colision_rafaga_especifico(r,e->x,e->y,e->w,e->h,tipo_bala))&&(e->tiempo_de_invinvibilidad == 0))
    {
        e->vida = e->vida - 10;
        e->tiempo_de_invinvibilidad = 10;
        e->atk_stop= 10;
        return 1;
    }
    return 0;
}

int colision_enemigo_objeto_damage(Enemigo e, double x, double y, double w, double h, int damage)
{
    if(solape_rectangulos(x,y,w,h,e->x,e->y,e->w,e->h)&&(e->tiempo_de_invinvibilidad == 0))
    {
        e->vida = e->vida - damage;
        e->tiempo_de_invinvibilidad = 2;
        e->atk_stop= 8;
        return 1;
    }
    return 0;
}

