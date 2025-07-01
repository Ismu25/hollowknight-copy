#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Pantalla.h"
#include "Colisiones.h"
#include "Rafaga.h"
#include "Animacion.h"
#include "Ejercito.h"
#include "Escenario.h"
#include "Particulas.h"
#include "Mapa.h"
#include "Tokens.h"
#include "Puntuacion.h"

#define pantalla_anchura 1024
#define pantalla_altura 508

#define UP REC_PLAYER1_A
#define UP_SCREEN REC_PLAYER1_UP
#define DOWN REC_PLAYER1_DOWN
#define LEFT REC_PLAYER1_LEFT
#define RIGHT REC_PLAYER1_RIGHT
#define DISPARO REC_PLAYER1_C
#define CARGA REC_PLAYER1_D
#define ATAQUE REC_PLAYER1_B
#define ACCEPT REC_PLAYER1_A
#define BACK REC_PLAYER1_B

#define POINT_R_X 730
#define POINT_L_X 221
#define POINT_Y 334
#define RIGHT_BORDER 906
#define LEFT_BORDER 138

#define DEATH -2
#define START -1
#define IDLE   0
#define CUR_I  1  /* CURA INICIAL */
#define COR_P   2 /* CORRER INICIAL */
#define SUB_D   3 /* SUBTERRANEA INICIAL */
#define SPI_D   4 /* SPIKES INICIAL */
#define LAS_I   5 /* LASER INICIAL */
#define PRJ_I   6 /* PROJECTILE INICIAL */
#define CUR_P   7
#define COR_I   8
#define COR_D   9
#define SUB_F   10
#define SUB_U   11
#define SPI_F   12
#define SPI_S   13
#define SPI_U   14
#define LAS_L   15
#define PRJ_L   16

/**
    \mainpage Juego
*/
/**
    \file main.c
    \brief Fichero con el contenido del juego
*/

int isTimeToStop = 0;

struct ProtStruct
{
    double x;
    double y;
    double vx;
    double vy;
    double h;
    double w;
    int vida;
    int void_energy;
    int invulnerable;
    SDL_RendererFlip dir_espejo;
    int atk_charge;
    int estado;
    int cura_reloj;
    int atk_sw_reloj;
    Animacion img_est[4];
    int jump_status;
};

struct BossStruct
{
    double x;
    double y;
    double h;
    double w;
    int vida;
    int estado;
    int timer;
    SDL_RendererFlip dir_espejo;
    Animacion charge;
    Animacion death;
    Animacion idle;
    Animacion jump;
    Animacion launch;
    Animacion run;
    int inv;
    int hasbeenAttacked;
    double vy;
    double vx;
};
//Estructura del protagonista
typedef struct ProtStruct ProtStr;
typedef struct ProtStruct * Protagonista;
typedef struct BossStruct * Boss;

# define numero_pantallas_ayuda 3
//Funcion de ayuda
void ayuda()
{
    Imagen fondo [numero_pantallas_ayuda] ;
    char r[30];
    for (int i = 0; i < numero_pantallas_ayuda; i++)
    {
        sprintf(r,"texturas/menus/ayuda%d.bmp",i);
        fondo[i] = Pantalla_ImagenLee(r,0);
    }
    Imagen select = Pantalla_ImagenLee("texturas/menus/select.bmp",10);
    int indice = 0, _end = 1, cont = 0, swap = 1;
    while(Pantalla_Activa() && _end && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;
        Pantalla_DibujaImagen(fondo[indice],0,0,Pantalla_Anchura(),Pantalla_Altura());

        if(indice < (numero_pantallas_ayuda - 1))
        {
            if (Pantalla_TeclaPulsada(RIGHT)) indice++;
            Pantalla_DibujaImagen(select,960-cont*1.5,455-cont*1.5,60+cont*1.5,45+cont*1.5);
        }
        if(indice > 0)
        {
            if(Pantalla_TeclaPulsada(LEFT)) indice--;
            Pantalla_DibujaImagenTransformada(select,5,455-cont*1.5,60+cont*1.5,45+cont*1.5,180,SDL_FLIP_NONE);
        }
        if (Pantalla_TeclaPulsada(BACK))
        {
            _end = 0;
        }


        if (swap)
        {
            cont++;
            if (cont == 10) swap = 0;
        }
        else
        {
            cont--;
            if (cont == 0) swap = 1;
        }

        Pantalla_Actualiza();
        Pantalla_Espera(80);
    }
    for (int i = 0; i < numero_pantallas_ayuda; i++)
        Pantalla_ImagenLibera(fondo[i]);
    Pantalla_ImagenLibera(select);

    return;
}
//Funcion de menu
int menu()
{
    Imagen fondo= Pantalla_ImagenLee("texturas/menus/menu_logo.bmp",0);
    Imagen jugar= Pantalla_ImagenLee("texturas/menus/jugar_1.bmp",10);
    Imagen ayuda= Pantalla_ImagenLee("texturas/menus/ayuda_1.bmp",10);
    Imagen puntuacion = Pantalla_ImagenLee("texturas/menus/puntuacion.bmp",10);
    Imagen seleccion = Pantalla_ImagenLee("texturas/menus/select.bmp",40);
    int seleccion_placement = 0;

    while(Pantalla_Activa() && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;
        // Adaptar
        if(Pantalla_TeclaPulsada(UP_SCREEN))
        {
            if(seleccion_placement)
                seleccion_placement = (seleccion_placement - 1) % 3;
            else
                seleccion_placement = 2;
        }
        else if(Pantalla_TeclaPulsada(DOWN))
            seleccion_placement = (seleccion_placement + 1) % 3;

        // Dibuja fondo
        Pantalla_DibujaImagen(fondo,0,0,pantalla_anchura,pantalla_altura);

        // Seleccion Dibujo
        if(seleccion_placement == 0)
        {
            Pantalla_DibujaImagen(seleccion,340,250,55,49);
            Pantalla_DibujaImagenTransformada(seleccion,629, 250, 55 , 49, 0, SDL_FLIP_HORIZONTAL);
        }
        if(seleccion_placement == 1)
        {
            Pantalla_DibujaImagen(seleccion,330,320,55,49);
            Pantalla_DibujaImagenTransformada(seleccion,640,320, 55 , 49, 0, SDL_FLIP_HORIZONTAL);
        }
        if(seleccion_placement == 2)
        {
            Pantalla_DibujaImagen(seleccion,315,398,55,49);
            Pantalla_DibujaImagenTransformada(seleccion,650,398, 55 , 49, 0, SDL_FLIP_HORIZONTAL);
        }

        // Pulsacion tecla
        if(Pantalla_TeclaPulsada(ACCEPT))
        {
            Pantalla_ImagenLibera(fondo);
            Pantalla_ImagenLibera(jugar);
            Pantalla_ImagenLibera(ayuda);
            Pantalla_ImagenLibera(puntuacion);
            Pantalla_ImagenLibera(seleccion);
            return seleccion_placement;
        }

        // Pantalla menu
        Pantalla_DibujaImagen(jugar,384,254,256,52);
        Pantalla_DibujaImagen(ayuda,384,327,256,52);
        Pantalla_DibujaImagen(puntuacion,384,400,256,52);
        // Actualizacion
        Pantalla_Actualiza();
        Pantalla_Espera(100);
    }
    Pantalla_ImagenLibera(fondo);
    Pantalla_ImagenLibera(jugar);
    Pantalla_ImagenLibera(ayuda);
    Pantalla_ImagenLibera(puntuacion);
    Pantalla_ImagenLibera(seleccion);
    return -1;
}
//Funcion de terminar juego
void end_p()
{
    Imagen screen = Pantalla_ImagenLee("texturas/menus/bad_end_screen.bmp",10);
    Pantalla_DibujaImagen(screen, 0, 0, anchura_pantalla(), altura_pantalla());
    Pantalla_Actualiza();

    while(Pantalla_Activa() && !(Pantalla_TeclaPulsada(ACCEPT) || Pantalla_TeclaPulsada(BACK)) && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;
        Pantalla_Espera(100);
    }
    Pantalla_ImagenLibera(screen);
}

void end_game(time_t start, time_t endt, char * ruta)
{
    // MOSTRAR PANTALLA DE ACIERTO, MOSTRAR EL TIEMPO,PEDIR LETRAS
    int seg, min; // Necesario
    char r[25];
    double diff = difftime(endt,start);
    int time = (int) diff;
    char name[5] = "AAAA"; // Name

    seg = time % 60; // Time print
    min = time /60;
    sprintf(r,"%02d:%02d",min,seg);
    Imagen screen = Pantalla_ImagenLee("texturas/menus/good_end_screen.bmp",0);
    Imagen select = Pantalla_ImagenLee("texturas/menus/select.bmp",10);


    Pantalla_ColorTrazo(255,255,255,255);

    int cont = 1; // mantener
    int indice = 0; // Indice de nombre
    while(Pantalla_Activa() && cont && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;
        Pantalla_DibujaImagen(screen, 0, 0, anchura_pantalla(), altura_pantalla()); // Fondo de pantalla

        if(name[indice] < 'Z')  // Cambio de letra
        {
            if(Pantalla_TeclaPulsada(UP_SCREEN)) name[indice] = name[indice] + 1;
            Pantalla_DibujaImagenTransformada(select, indice * 9 + 507, 290, 20, 25,90,SDL_FLIP_NONE);
        }

        if(name[indice] > 'A')
        {
            if(Pantalla_TeclaPulsada(DOWN)) name[indice] = name[indice] - 1;
            Pantalla_DibujaImagenTransformada(select, indice * 9 + 505, 340, 20, 25,270,SDL_FLIP_NONE);
        }

        if(Pantalla_TeclaPulsada(RIGHT)&& indice < 3) indice++; // Cambio de indice
        if(Pantalla_TeclaPulsada(LEFT) && indice > 0) indice--;
        if(Pantalla_TeclaPulsada(ACCEPT)) cont = 0; // Finalizar o guardar

        Pantalla_DibujaTexto(name, 512, 320 ); // Dibuja
        Pantalla_DibujaTexto(r, 512, 245);

        Pantalla_Actualiza(); // Actualiza
        Pantalla_Espera(100);
    }
    Puntuaciones punt = leer_puntuacion(ruta); // Guardar
    introducir_puntuacion(punt,diff,name);
    guardar_puntuacion_archivo(punt,ruta);
    libera_puntuacion(punt);
}

int map_select()
{
    int indice = 0; // Indice de nombre
    Imagen screen = Pantalla_ImagenLee("texturas/menus/elg_map.bmp",0);
    Imagen selector = Pantalla_ImagenLee("texturas/menus/select.bmp",1);
    Pantalla_Espera(160);
    while(Pantalla_Activa() && !Pantalla_TeclaPulsada(BACK) && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;
        Pantalla_DibujaImagen(screen, 0, 0, anchura_pantalla(), altura_pantalla()); // Fondo de pantalla
        Pantalla_DibujaImagen(selector,295,65*indice+160,60,60);
        Pantalla_DibujaImagenTransformada(selector,655,67*indice+162,60,60,180,SDL_FLIP_NONE);
        if(Pantalla_TeclaPulsada(DOWN)&& indice < 4) indice++; // Cambio de indice
        if(Pantalla_TeclaPulsada(UP_SCREEN) && indice > 0) indice--;
        if(Pantalla_TeclaPulsada(ACCEPT))
        {
            Pantalla_ImagenLibera(screen);
            Pantalla_ImagenLibera(selector);
            Pantalla_Espera(160);
            return indice;
        }
        Pantalla_Actualiza(); // Actualiza
        Pantalla_Espera(100);
    }
    Pantalla_Espera(160);
    Pantalla_ImagenLibera(screen);
    Pantalla_ImagenLibera(selector);
    return -1;

}

#define MAX_HEALTH 6
//Funcion para mostrar la vida
void health (int vida,Imagen vida_llena, Imagen vida_vacia)
{
    char a[5]; //MAS VIDA

    for(int i = 0; i < vida; i++) {
        Pantalla_DibujaImagen(vida_llena,10+40*i,10, 25,30);
    }

    for(int i = vida; i < MAX_HEALTH; i++){
        Pantalla_DibujaImagen(vida_vacia,10+40*i,10, 25,30);
    }

    sprintf(a,"%d",vida);
    Pantalla_DibujaTexto(a,240,30);
}
//Funcion para mostrar el nivel de energia
void cantidad_energia(int energia, int n_imagenes, Imagen * contenedor_energia)
{
    if(energia >= n_imagenes || energia < 0) return;
    Pantalla_DibujaImagen(contenedor_energia[energia],925,10,100,100);
}

//Funcion de movimiento del protagonista
void movimiento_protagonista (Protagonista prot,Escenario b)
{
    //gravedad del protagonista
    if(!solape_suelo(prot->x,prot->y,prot->w,prot->h,b)) prot->vy = prot->vy + 0.8;
    //Movemos el protagonista
    prot->x = prot->x + prot->vx;
    prot->y = prot->y + prot->vy;
    //Comparamos si hay solape y si lo hay le reseteamos su velocidad de caida
    if(comp_de_pos_plataforma(prot->x,prot->y,prot->w,prot->h,b)==1)
    {
        prot->vy = 0;
        if(prot->jump_status) prot->jump_status-- ;
    };


    //salto del protagonista y funcion para que el salto sea dependiente al tiempo que se tiene pulsado la flecha superior
    if((Pantalla_TeclaPulsada(UP))&&(comp_de_pos_plataforma(prot->x,prot->y,prot->w,prot->h,b)==1)&& !prot->jump_status)
    {
        prot->vy = -14.5 ;
        prot->jump_status = 3;
    }
    if((prot->vy < 0) && !(Pantalla_TeclaPulsada(UP))) prot->vy = prot->vy + 1;

    //movimiento izquierta y derecha, y reduccion de velocidad lateral
    if(Pantalla_TeclaPulsada(RIGHT) )
    {
        if (prot->x + prot->w > pantalla_anchura) prot->vx=0;
        else
        {
            prot->vx = 4 ;
            prot->dir_espejo=SDL_FLIP_NONE;
        }
    }
    else if(Pantalla_TeclaPulsada(LEFT))
    {
        if(prot->x < 0) prot->vx=0;
        else
        {
            prot->vx = -4;
            prot->dir_espejo=SDL_FLIP_HORIZONTAL;
        }
    }
    else if(solape_suelo(prot->x,prot->y,prot->w,prot->h,b))
    {
        prot->vx= prot->vx / 1.8;
    }
    else
    {
        prot->vx= prot->vx / 1.2;
    }


    //Reajuste de posicion segun los bloques del escenario
    prot->estado=0;
    Direccicion i;
    int errorEx = 0;
    while ((i = comp_de_pos_plataforma(prot->x,prot->y,prot->w,prot->h,b)) != 0)
    {
        int j= buscar_plataforma_solape(prot->x,prot->y,prot->w,prot->h,b);
        if(i==IZQUIERDA)
        {
            while(solape_con_bloque(prot->x,prot->y,prot->w,prot->h,b,j))
            {
                prot->x = prot->x - 4.3;
            }
            prot->estado=0;
        }
        else if(i==DERECHA)
        {
            while(solape_con_bloque(prot->x,prot->y,prot->w,prot->h,b,j))
            {
                prot->x = prot->x + 4.3;
            }
            prot->estado=0;
        }
        else if(i==ARRIBA)
        {
            while(solape_con_bloque(prot->x,prot->y,prot->w,prot->h,b,j))
            {
                prot->y = prot->y - 0.1;
            }
            if(abs(prot->vx) < 0.01) prot->estado=1;
            else prot->estado=2;

        }
        else if (i==ABAJO)
        {
            while(solape_con_bloque(prot->x,prot->y,prot->w,prot->h,b,j))
            {
                prot->y = prot->y + 0.1;
            }
            if(prot->vy < 0) prot->vy=0;
            else prot->estado=0;
        }
        errorEx++;
        if (errorEx == 500){
            printf("MAP ERROR CAUSED BY TWO BLOCK OVERLAPING WITH PROTAGONIST : REFER TO ISMU WITH THIS MATTER");
            isTimeToStop = 1;
            return;
        }
    }
}

void dibuja_reloj(time_t start)
{
    int seg=0, min=0;
    char r[25];

    time_t current = time(NULL);
    int time = difftime(current,start);

    seg = time % 60;
    min = time /60;

    sprintf(r,"%02d:%02d",min,seg);
    Pantalla_DibujaTexto(r,450,5);
}

void juego_norm(int mapa)
{
    //creamos los datos que vamos a necesitar
    Particulas lista_particulas= crea_particulas();
    Ejercito grupo_enemigos;
    Rafaga lista_balas = crea_rafaga();
    ProtStr sprot = {.h=42, .w=25};
    Protagonista prot= &sprot;
    Imagen * soul_meter = malloc(sizeof(Imagen)*11);


    //Cargamos todas las imagenes y animaciones
    soul_meter[0]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter0.bmp", 1);
    soul_meter[1]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter1.bmp", 1);
    soul_meter[2]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter2.bmp", 1);
    soul_meter[3]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter3.bmp", 1);
    soul_meter[4]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter4.bmp", 1);
    soul_meter[5]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter5.bmp", 1);
    soul_meter[6]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter6.bmp", 1);
    soul_meter[7]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter7.bmp", 1);
    soul_meter[8]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter8.bmp", 1);
    soul_meter[9]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter9.bmp", 1);
    soul_meter[10]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter10.bmp", 1);

    Animacion respawn_p = carga_animacion(10,"texturas/particulas/respawn#.bmp");
    Animacion void_p = carga_animacion(5,"texturas/particulas/void_p#.bmp");
    Animacion soul_p= carga_animacion(5,"texturas/particulas/soul_p#.bmp");

    Animacion soul_explotion = carga_animacion(10,"texturas/particulas/soulexpotion#.bmp");
    Animacion soul_charge = carga_animacion(3,"texturas/particulas/charge#.bmp");

    Animacion sw = carga_animacion(3,"texturas/particulas/sw#.bmp");
    Animacion token_imgs = carga_animacion(6,"texturas/tokens/token#.bmp");

    prot->img_est[0]=carga_animacion(4,"texturas/knight/fall#.bmp");
    prot->img_est[1]=carga_animacion(4,"texturas/knight/stand#.bmp");
    prot->img_est[2]=carga_animacion(6,"texturas/knight/walk#.bmp");
    prot->img_est[3]=carga_animacion(8,"texturas/knight/regenerate#.bmp");

//    Animacion vacia = NULL;

    Imagen vida_llena= Pantalla_ImagenLee("texturas/variados/full_mask.bmp", 1);
    Imagen vida_vacia= Pantalla_ImagenLee("texturas/variados/empty_mask.bmp",1);
    Imagen imag_bala = Pantalla_ImagenLee("texturas/variados/Projectile.bmp",1);
    Imagen imag_prot_proj = Pantalla_ImagenLee("texturas/variados/Shade_Soul.bmp",255);
    Imagen imag_suelo = Pantalla_ImagenLee("texturas/variados/suelo.bmp",255);
    Imagen soul_beam = Pantalla_ImagenLee("texturas/variados/Soul_beam.bmp",255);

    char root [20];
    sprintf(root,"data/mapa_%d.txt",mapa + 1);
    Mapa escena = cargar_escenarios(root);

    int frame_time=0;
    time_t start_time=time(NULL);

    //Inicializacion de las variables
    prot->vida=MAX_HEALTH;
    prot->dir_espejo=SDL_FLIP_HORIZONTAL;
    prot->atk_charge=0;
    prot->void_energy=10;
    prot->cura_reloj=10;
    prot->vx=0;
    prot->vy=0;
    frame_time=0;
    Posicion pos = get_posicion_incial(escena);
    prot->x=get_spawn_x(pos);
    prot->y=get_spawn_y(pos);
//        spawn_enemigos(grupo_enemigos,lista_particulas,pos,vf,vfmuerte,vacia,dc,dcmuerte,ach,achmuerte,ach_atk,spawn_p);
    grupo_enemigos = get_mapa_ejercito(escena, pos);
    start_time= time(NULL);

    //Comienzo del juego
    while(Pantalla_Activa() && (prot->vida > 0 && !all_token_taken(escena)) && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) {isTimeToStop = 1; prot->vida = 0;}
        //Cambio de escenarios
        int escenario_actual = get_escenario(pos);
        if(comprueba_conex_escenarios(escena,pos,&(prot->x),&(prot->y),prot->w,prot->h))
        {
            prot->vx=0;
            prot->vy=0;

            if(get_escenario(pos) != escenario_actual)
            {
                limpia_rafaga(lista_balas);
                limpia_particulas(lista_particulas);
                grupo_enemigos = get_mapa_ejercito(escena, pos);
            }
        }

        //Quita vida al protagonista si hat colsion con el acido del mapa
        if(prot->y > pantalla_altura + 20)
        {
            prot->x= get_spawn_x(pos);
            prot->y= get_spawn_y(pos);
            prot->vx = 0;
            prot->vy = 0;
            introduce_particula(lista_particulas,get_spawn_x(pos)+prot->w/2-40,get_spawn_y(pos)+prot->h/2-40,80,80,SDL_FLIP_NONE,respawn_p);
            prot->invulnerable= 60;
        }

        //movimiento del protagonista

        movimiento_protagonista(prot,get_mapa_bloques(escena,pos));

        //activa los tokens si no hay enemigos
        if(get_n_enemigos(grupo_enemigos) == 0) activa_tokens(get_mapa_tokens(escena,pos));

        //Comprueba si los tokens estan tokando a los protagonistas
        comp_tokens(get_mapa_tokens(escena,pos),prot->x,prot->y,prot->w,prot->h);

        //Quita vida al protagonista si hay colsion con los enemigos
        if(colision_ejercito_objeto(grupo_enemigos, prot->x, prot->y, prot->w, prot->h) && prot->invulnerable == 0)
        {
            prot->vida= prot->vida - 1;
            introduce_particula(lista_particulas,prot->x+prot->w/2-40,prot->y+prot->h/2-40,80,80,SDL_FLIP_NONE,void_p);
            prot->invulnerable= 60;
        }

        //Quita vida al protagonista si hat colsion con el acido del mapa
        if(solape_suelo(prot->x,prot->y,prot->w,prot->h,get_mapa_acido(escena,pos)))
        {
            prot->vida= prot->vida - 1;
            prot->x= get_spawn_x(pos);
            prot->y= get_spawn_y(pos);
            prot->vx = 0;
            prot->vy = 0;
            introduce_particula(lista_particulas,get_spawn_x(pos)+prot->w/2-40,get_spawn_y(pos)+prot->h/2-40,80,80,SDL_FLIP_NONE,respawn_p);
            prot->invulnerable= 60;
        }


        //mueve al ejercito y crea balas
        mueve_ejercito(grupo_enemigos,get_mapa_bloques(escena,pos),prot->x+prot->w/2,prot->y+prot->h/2);
        ejercito_crea_balas_compl(grupo_enemigos,lista_balas,imag_bala,prot->x+prot->w/2,prot->y+prot->h/2);

        //Cura del protagonista
        if( Pantalla_TeclaPulsada(CARGA) && prot->void_energy >= 2 && prot->estado == 1 && prot->vida < MAX_HEALTH)
        {
            prot->estado = 3;
            prot->cura_reloj--;
            introduce_particula(lista_particulas,prot->x+prot->w/2-20,prot->y+prot->h/2-20,40,40,SDL_FLIP_NONE,soul_charge);
            if(prot->cura_reloj == 0)
            {
                prot->vida++;
                prot->cura_reloj=15;
                prot->void_energy = prot->void_energy - 2;
                introduce_particula(lista_particulas,prot->x+prot->w/2-40,prot->y+prot->h/2-40,80,80,SDL_FLIP_NONE,soul_explotion);
            }

        }
        else
        {
            prot->cura_reloj=15;
        }


        //Colsion de balas enemigas con el protagonista
        if(prot->invulnerable == 0 && colision_rafaga_especifico(lista_balas,prot->x,prot->y,prot->w,prot->h,0))
        {
            prot->vida= prot->vida - 1;
            introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
            prot->invulnerable = 60;
        }


        //mueve las balas
        mueve_rafaga(lista_balas,pantalla_anchura,pantalla_altura);
        //Comprueba que las balas enemigas y las principales balas del protagonista estan tocando algun bloque y las elimina
        elimina_bala_colision_rafaga(lista_balas,get_mapa_bloques(escena,pos),0);
        elimina_bala_colision_rafaga(lista_balas,get_mapa_bloques(escena,pos),2);

        //Comprueba si alguna bala del protagonista esta tocando a algun enemigo y aporta energia al protagonista si es as�
        int n= colision_ejercito_rafaga(grupo_enemigos,lista_balas,1) + colision_ejercito_rafaga(grupo_enemigos,lista_balas,2);
        for(int i=0; i < n; i++)
        {
            if(prot->void_energy < 9)prot->void_energy = prot->void_energy + 2;
            else prot->void_energy =10;
        }

        //Reduce el tiempo de espera para las balas del protagonista
        if (prot->atk_charge > 0) prot->atk_charge = prot->atk_charge - 1;
        //Crea las balas del protagonista
        if((prot->atk_charge == 0)&&(Pantalla_TeclaPulsada(DISPARO)))
        {
            if(prot->void_energy > 0)
            {
                if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
                {
                    inserta_rafaga(lista_balas,crea_bala(imag_prot_proj,prot->x+15,prot->y+8,-3,0,20,40,1));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
                }
                else
                {
                    inserta_rafaga(lista_balas,crea_bala(imag_prot_proj,prot->x-15,prot->y+8,3,0,20,40,1));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
                }
                prot->atk_charge = 10;
                prot->void_energy--;
            }
            else
            {
                if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
                {
                    inserta_rafaga(lista_balas,crea_bala(soul_beam,prot->x+15,prot->y+8,-2,0,20,40,2));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,soul_p);
                }
                else
                {
                    inserta_rafaga(lista_balas,crea_bala(soul_beam,prot->x-15,prot->y+8,2,0,20,40,2));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,soul_p);
                }
                prot->atk_charge = 10;
            }
        }

        //ataque con espada del protagonista
        if(prot->atk_sw_reloj == 0 && Pantalla_TeclaPulsada(ATAQUE))
        {
            if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
            {

                for(int i=0; i < colision_ejercito_objeto_damage(grupo_enemigos,prot->x-60,prot->y,85,prot->h,6); i++)
                {
                    if(prot->void_energy < 9)prot->void_energy = prot->void_energy + 2;
                    else prot->void_energy =10;
                }
                introduce_particula(lista_particulas,prot->x-60,prot->y,60,prot->h,SDL_FLIP_NONE,sw);

            }
            else
            {

                for(int i=0; i < colision_ejercito_objeto_damage(grupo_enemigos,prot->x,prot->y,85,prot->h,6); i++)
                {
                    if(prot->void_energy < 9)prot->void_energy = prot->void_energy + 2;
                    else prot->void_energy =10;
                }
                introduce_particula(lista_particulas,prot->x+prot->w,prot->y,60,prot->h,SDL_FLIP_HORIZONTAL,sw);

            }
            prot->atk_sw_reloj = 10;
        }
        else if(prot->atk_sw_reloj > 0) prot->atk_sw_reloj--;

        //Reduccion de la invulnerabilidad contra ataques del protagonista
        if(prot->invulnerable != 0 ) prot->invulnerable--;

        //Renderizado de Pantalla

        Pantalla_ColorTrazo(255,255,255,255);
        Pantalla_DibujaImagen(get_mapa_imagen(escena,pos),0,0,pantalla_anchura,pantalla_altura);

        dibuja_animacion(frame_time/2,prot->img_est[prot->estado],prot->x,prot->y,prot->w,prot->h,0,prot->dir_espejo);

        dibuja_suelo(imag_suelo,get_mapa_bloques(escena,pos));
        dibuja_ejercito(grupo_enemigos);
        dibuja_tokens(get_mapa_tokens(escena,pos),token_imgs);
        dibuja_rafaga(lista_balas);
        dibuja_particulas(lista_particulas);
        dibuja_reloj(start_time);

        health(prot->vida,vida_llena,vida_vacia);
        cantidad_energia(prot->void_energy,11,soul_meter);
        frame_time = frame_time + 1;

        Pantalla_Actualiza();
        Pantalla_Espera(40);
    }
    // Elimina todas las rafagas, enemigos, particulas y la posicion para la siguiente partida
    if (all_token_taken(escena))
    {
        end_game(start_time,time(NULL), get_puntuacion_ruta(escena));
    }
    else
    {
        end_p();
    }

    libera_posicion(pos);
    libera_mapa(escena);

    //Si no se quiere continuar se libera toda la memoria que se hab�a reservado durante la ejecucion del programa

    for (int i=0;  i < 11; i++)
    {
        Pantalla_ImagenLibera(soul_meter[i]);
    }
    free(soul_meter);
    libera_animacion(respawn_p);

    libera_animacion(void_p);
    libera_animacion(soul_p);

    libera_animacion(soul_explotion);
    libera_animacion(soul_charge);

    libera_animacion(sw);
    libera_animacion(token_imgs);

    for(int i=0; i < 4; i++)
    {
        libera_animacion(prot->img_est[i]);
    }

    Pantalla_ImagenLibera(vida_llena);
    Pantalla_ImagenLibera(vida_vacia);
    Pantalla_ImagenLibera(imag_bala);
    Pantalla_ImagenLibera(imag_prot_proj);
    Pantalla_ImagenLibera(imag_suelo);
    Pantalla_ImagenLibera(soul_beam);

    //libera_ejercito(grupo_enemigos);
    libera_particulas(lista_particulas);
    libera_rafaga(lista_balas);
}

int boss_select(Boss boss)
{
    return rand() % 6 + 1;
}

/*
*/
void dibuja_boss(Boss boss, int frame_time, Particulas part, Animacion part1, Animacion part2, Animacion part3, Animacion part4, int* stop, Animacion part5,
                 Animacion part6, double center_x, Imagen bal, Animacion bal_up, Rafaga raf, Animacion bal_down, Animacion launch_big, Imagen launch_ray,
                 Imagen launch_ray_p, Imagen boss_orbs, int center_y, Imagen proj)
{
    if (boss->vida <= 0 && boss->estado != DEATH)
    {
        introduce_particula(part,boss->x+20,boss->y+20,76,70,boss->dir_espejo,boss->death);
        boss->estado = DEATH;
        boss->timer = 50;
    }

    if(boss->estado == START)
    {
        if (boss->timer > 50 && boss->timer % 5 == 0)  // SPAWN
        {
            introduce_particula(part,732,410,63,15,SDL_FLIP_NONE,part2);
            introduce_particula(part,739,390,49,39,SDL_FLIP_NONE,part3);
        }
        if (boss->timer == 54) introduce_particula(part,715,329,100,100,SDL_FLIP_NONE,part4);
        if (boss->timer <= 50) dibuja_animacion(frame_time/2,boss->charge,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if (boss->timer == 50)
        {
            introduce_particula(part,710,320,120,120,SDL_FLIP_NONE,part1);
        }
        if (boss->timer == 35)
        {
            introduce_particula(part,710,320,120,120,SDL_FLIP_NONE,part1);
        }
        if (boss->timer == 20)
        {
            introduce_particula(part,710,320,120,120,SDL_FLIP_NONE,part1);
        }
        if (boss->timer == 0)
        {
            boss->estado = IDLE;
            boss->timer = 20;
        }

    }
    else if (boss->estado == IDLE)    // ESTADO IDLE
    {
        dibuja_animacion(frame_time/2,boss->idle,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->timer == 0) boss->estado = boss_select(boss);
    }
    else if (boss->estado == DEATH)    // MUERTE
    {
        if (boss->timer == 0) *stop = 1;
    }
    else if (boss->estado == CUR_I)    // CURA -- INCICIALIZACION
    {
        if (boss->vida > 200)   // DEMASIADA VIDA
        {
            boss->estado = IDLE;
            boss->timer = 10;
            dibuja_animacion(frame_time/2,boss->idle,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        }
        else     // SUFICIENTE VIDA
        {
            boss->timer = 40;
            boss->estado = CUR_P;
            dibuja_animacion(frame_time/2,boss->charge,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
            introduce_particula(part,boss->x+boss->w/2-40,boss->y+boss->h/2-40,80,80,SDL_FLIP_NONE,part5);
        }
    }
    else if (boss->estado == CUR_P)    // CURA
    {
        dibuja_animacion(frame_time/4,boss->charge,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->timer % 3 == 0) introduce_particula(part,boss->x+boss->w/2-40,boss->y+boss->h/2-40,80,80,SDL_FLIP_NONE,part5);
        if (boss->hasbeenAttacked)   // Si es atacado, para
        {
            boss->timer = 20;
            boss->estado = IDLE;
        }
        else if (boss->timer == 0)    // Si termina se cura
        {
            boss->vida = boss->vida + 50;
            introduce_particula(part,boss->x+boss->w/2-60,boss->y+boss->h/2-60,120,120,SDL_FLIP_NONE,part6);
            boss->timer = 30;
            boss->estado = IDLE;
        }
    }
    else if (boss->estado == COR_P)    // CORRER - PRINERA PARTE
    {
        dibuja_animacion(frame_time/2,boss->run,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if (boss->dir_espejo == SDL_FLIP_NONE)
        {
            if(boss->x > LEFT_BORDER)
            {
                boss->x = boss->x - 10;
            }
            else
            {
                boss->estado = COR_I;
                boss->dir_espejo = SDL_FLIP_HORIZONTAL;
            }
        }
        else
        {
            if(boss->x < (RIGHT_BORDER - boss->w))
            {
                boss->x = boss->x + 10;
            }
            else
            {
                boss->estado = COR_D;
                boss->dir_espejo = SDL_FLIP_NONE;
            }
        }

    }
    else if (boss->estado == COR_I)    // CORRER - RECOLOCARSE - HACIA LA IZQUIERDA
    {
        dibuja_animacion(frame_time/2,boss->run,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->x < POINT_L_X)
        {
            boss->x = boss->x + 5;
        }
        else
        {
            boss->estado = IDLE;
        }

    }
    else if (boss->estado == COR_D)    // CORRER - RECOLOCARSE - HACIA LA DERECHA
    {
        dibuja_animacion(frame_time/2,boss->run,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->x > POINT_R_X)
        {
            boss->x = boss->x - 5;
        }
        else
        {
            boss->estado = IDLE;
        }
    }
    else if (boss->estado == SUB_D)    // ATAQUE SUBTERRANEO - GOING DOWN
    {
        if (boss->vy < -9.2)
        {
            boss->vy = 0;
            boss->timer = 100;
            boss->estado = SUB_F;
            boss->y = -100;
        }
        else
        {
            if (boss->vy >= -8 && boss->vy < -7.6) introduce_particula(part,boss->x-10,329,80,100,SDL_FLIP_NONE,part4);
            dibuja_animacion(frame_time/2,boss->jump,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        }

        if(boss->timer == 0)
        {
            boss->timer = 100000;
            boss->vy = 9;
        }
        else
        {
            boss->y = boss->y - boss->vy;
            boss->vy = boss->vy - 0.4;
        }
    }
    else if (boss->estado == SUB_F)    // ATAQUE SUBTERRANEO - PERSEGUIR
    {
        if(boss->timer > 0) introduce_particula(part,boss->x-10,410,80,15,SDL_FLIP_NONE,part2);
        else boss->estado = SUB_U;

        if (boss->timer > 15)
        {
            boss->vx = center_x - boss->x - boss->w/2;
            boss->vx = boss->vx / 10;
            boss->x = boss->x + 0.7 * boss->vx;
        }
    }
    else if (boss->estado == SUB_U)     // ATAQUE SUBTERRANEO - SALIR E IR A UNA DE LAS POSICIONES
    {
        if(boss->timer == 0)
        {
            boss->timer = 10000;
            boss->vy = 12.5;
            boss->y = 330;
        }
        else if (boss->y >= POINT_Y && boss->vy < 0)
        {
            boss->vy = 0;
            boss->y = POINT_Y;
            boss->timer = 0;
            boss->estado = COR_P;
        }
        else
        {
            boss->y = boss->y - boss->vy;
            boss->vy = boss->vy - 0.4;
            if (boss->timer == 9999) introduce_particula(part,boss->x-10,329,80,100,SDL_FLIP_NONE,part4);
        }

        if (boss->timer < 9999)
        {
            dibuja_animacion(frame_time/2,boss->jump,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        }
    }
    else if (boss->estado == SPI_D)     // SURFACE PROJECT - ENTRAR EN EL SUELO
    {
        if (boss->vy < -9.2)
        {
            boss->vy = 0;
            boss->timer = 80;
            boss->estado = SPI_F;
            boss->y = -100;
        }
        else
        {
            if (boss->vy >= -8 && boss->vy < -7.6) introduce_particula(part,boss->x-10,329,80,100,SDL_FLIP_NONE,part4);
            dibuja_animacion(frame_time/2,boss->jump,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        }

        if(boss->timer == 0)
        {
            boss->timer = 100000;
            boss->vy = 9;
        }
        else
        {
            boss->y = boss->y - boss->vy;
            boss->vy = boss->vy - 0.4;
        }
    }
    else if (boss->estado == SPI_F )    // SURFACE PROJECT - PRIMER INTENTO
    {
        if (boss->timer <= 80 && boss->timer > 40)
        {
            for (int i=LEFT_BORDER + 10; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,415,40,15,SDL_FLIP_NONE,part2);
        }
        else if (boss->timer == 40)
        {
            for (int i=LEFT_BORDER + 10; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,230,40,200,SDL_FLIP_NONE,bal_up);
        }
        else if (boss->timer == 34)
        {
            for (int i=LEFT_BORDER + 10; i + 40 < RIGHT_BORDER; i = i + 80)
                inserta_rafaga(raf,crea_bala (bal, i, 230, 0, 0, 200, 40, 6));
        }
        else if (boss->timer == 0)
        {
            for (int i=LEFT_BORDER + 10; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,230,40,200,SDL_FLIP_NONE,bal_down);
            elimina_balas_tipo(raf, 6);
            boss->estado = SPI_S;
            boss->timer = 80;
        }
    }
    else if (boss->estado == SPI_S)    // SURFACE PROJECT - SEGUNDO INTENTO
    {
        if (boss->timer <= 80 && boss->timer > 40)
        {
            for (int i=LEFT_BORDER + 50; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,415,40,15,SDL_FLIP_NONE,part2);
        }
        else if (boss->timer == 40)
        {
            for (int i=LEFT_BORDER + 50; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,230,40,200,SDL_FLIP_NONE,bal_up);
        }
        else if (boss->timer == 34)
        {
            for (int i=LEFT_BORDER + 50; i + 40 < RIGHT_BORDER; i = i + 80)
                inserta_rafaga(raf,crea_bala (bal, i, 230, 0, 0, 200, 40, 6));
        }
        else if (boss->timer == 0)
        {
            for (int i=LEFT_BORDER + 50; i + 40 < RIGHT_BORDER; i = i + 80)
                introduce_particula(part,i,230,40,200,SDL_FLIP_NONE,bal_down);
            elimina_balas_tipo(raf, 6);
            boss->estado = SPI_U;
        }

    }
    else if (boss->estado == SPI_U)    // SURFACE PROJECT - SALIDA
    {
        if(boss->timer == 0)
        {
            boss->timer = 10000;
            boss->vy = 12.5;
            boss->y = 330;
        }
        else if (boss->y >= POINT_Y && boss->vy < 0)
        {
            boss->vy = 0;
            boss->y = POINT_Y;
            boss->timer = 30;
            boss->estado = IDLE;
        }
        else
        {
            boss->y = boss->y - boss->vy;
            boss->vy = boss->vy - 0.4;
            if (boss->timer == 9999) introduce_particula(part,boss->x-10,329,80,100,SDL_FLIP_NONE,part4);
        }

        if (boss->timer < 9999)
        {
            dibuja_animacion(frame_time/2,boss->jump,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        }
    }
    else if (boss->estado == LAS_I)    // INICIO LASER
    {
        boss->timer = 100;
        dibuja_animacion(frame_time/2,boss->launch,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        boss->estado = LAS_L;
    }
    else if (boss->estado == LAS_L)    // LASER
    {
        dibuja_animacion(frame_time/2,boss->launch,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->dir_espejo == SDL_FLIP_NONE)
        {
            if (boss->timer > 70)
            {
                Pantalla_DibujaImagen(launch_ray_p,LEFT_BORDER,382,boss->x - LEFT_BORDER,20);
            }
            else if(boss->timer == 70)
            {
                introduce_particula(part,LEFT_BORDER,367,boss->x - LEFT_BORDER,50,SDL_FLIP_NONE,launch_big);
            }
            else if (boss->timer == 65)
            {
                inserta_rafaga(raf,crea_bala(launch_ray,LEFT_BORDER,367,0,0,50,boss->x - LEFT_BORDER,6));
            }
            else if (boss->timer == 60)
            {
                elimina_balas_tipo(raf, 6);
                boss->timer = 30;
                boss->estado = IDLE;
            }
            Pantalla_DibujaImagen(boss_orbs,boss->x-15,boss->y+40,30,30);
        }
        else
        {
            if (boss->timer > 70)
            {
                Pantalla_DibujaImagen(launch_ray_p,boss->x+boss->w,382,RIGHT_BORDER - boss->x - boss->h,20);
            }
            else if(boss->timer == 70)
            {
                introduce_particula(part,boss->x+boss->w,367,RIGHT_BORDER - boss->x - boss->h,50,SDL_FLIP_NONE,launch_big);
            }
            else if (boss->timer == 65)
            {
                inserta_rafaga(raf,crea_bala(launch_ray,boss->x+boss->w,367,0,0,50,RIGHT_BORDER - boss->x - boss->h,6));

            }
            else if (boss->timer == 60)
            {
                elimina_balas_tipo(raf, 6);
                boss->timer = 30;
                boss->estado = IDLE;
            }
            Pantalla_DibujaImagen(boss_orbs,boss->x+55,boss->y+40,30,30);
        }
    }
    else if (boss->estado == PRJ_I)     // LANZAMIENTO -- INCIAL
    {
        boss->timer = 60;
        dibuja_animacion(frame_time/2,boss->launch,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        boss->estado = PRJ_L;
    }
    else if (boss->estado == PRJ_L)     // LANZAMIENTO -- LANZAL
    {
        dibuja_animacion(frame_time/2,boss->launch,boss->x,boss->y,boss->w,boss->h,0,boss->dir_espejo);
        if(boss->dir_espejo == SDL_FLIP_NONE)
        {
            if (boss->timer == 59 || boss->timer == 39 || boss->timer == 19)
            {

                double vx = center_x - boss->x;
                double vy = center_y - (boss->y + 30);

                double m = sqrt( vx*vx + vy*vy ) * 1.5;
                if ( m > 0 )
                {
                    vy = vy / m;
                    vx = vx / m;
                }

                inserta_rafaga(raf,crea_bala(proj,boss->x,boss->y+30,vx,vy,30,30,5));

            }
            else if (boss->timer == 0)
            {
                boss->timer = 30;
                boss->estado = IDLE;
            }
            Pantalla_DibujaImagen(boss_orbs,boss->x-15,boss->y+40,30,30);
        }
        else
        {
            if (boss->timer == 59 || boss->timer == 39 || boss->timer == 19)
            {
                double vx = center_x - (boss->x + boss->w);
                double vy = center_y - (boss->y + 30);

                double m = sqrt( vx*vx + vy*vy );
                if ( m > 0 )
                {
                    vy = vy / m;
                    vx = vx / m;
                }
                inserta_rafaga(raf,crea_bala(proj,boss->x+boss->w,boss->y+30,vx,vy,30,30,5));

            }
            else if (boss->timer == 0)
            {
                boss->timer = 30;
                boss->estado = IDLE;
            }
            Pantalla_DibujaImagen(boss_orbs,boss->x+55,boss->y+40,30,30);
        }
    }
}

void juego_boss_level(int mapa)
{
    Particulas lista_particulas= crea_particulas();
    Rafaga lista_balas = crea_rafaga();
    ProtStr sprot = {.h=42, .w=25};
    Protagonista prot= &sprot;
    struct BossStruct bossstruct= {};
    Boss boss = &bossstruct;
    Imagen * soul_meter = malloc(sizeof(Imagen)*11);


    //Cargamos todas las imagenes y animaciones
    soul_meter[0]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter0.bmp", 1);
    soul_meter[1]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter1.bmp", 1);
    soul_meter[2]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter2.bmp", 1);
    soul_meter[3]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter3.bmp", 1);
    soul_meter[4]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter4.bmp", 1);
    soul_meter[5]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter5.bmp", 1);
    soul_meter[6]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter6.bmp", 1);
    soul_meter[7]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter7.bmp", 1);
    soul_meter[8]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter8.bmp", 1);
    soul_meter[9]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter9.bmp", 1);
    soul_meter[10]=Pantalla_ImagenLee("texturas/soulmeter/soul_meter10.bmp", 1);

    Animacion respawn_p = carga_animacion(10,"texturas/particulas/respawn#.bmp");
    Animacion void_p = carga_animacion(5,"texturas/particulas/void_p#.bmp");
    Animacion soul_p= carga_animacion(5,"texturas/particulas/soul_p#.bmp");

    Animacion soul_explotion = carga_animacion(10,"texturas/particulas/soulexpotion#.bmp");
    Animacion soul_charge = carga_animacion(3,"texturas/particulas/charge#.bmp");

    Animacion sw = carga_animacion(3,"texturas/particulas/sw#.bmp");
    Animacion token_imgs = carga_animacion(6,"texturas/tokens/token#.bmp");

    Animacion burrow_e = carga_animacion(6,"texturas/particulas/burrow_#.bmp");
    Animacion burrow_p = carga_animacion(4,"texturas/particulas/burrow_p#.bmp");
    Animacion boss_spwan = carga_animacion(5,"texturas/particulas/boss_spawn#.bmp");
    Animacion atk_boss_up = carga_animacion(7,"texturas/particulas/atk_boss_floor_#.bmp");
    Animacion atk_boss_down = carga_animacion(7,"texturas/particulas/atk_boss_floor_rv#.bmp");
    Animacion launch_big = carga_animacion(6,"texturas/particulas/ray_#.bmp");

    prot->img_est[0]=carga_animacion(4,"texturas/knight/fall#.bmp");
    prot->img_est[1]=carga_animacion(4,"texturas/knight/stand#.bmp");
    prot->img_est[2]=carga_animacion(6,"texturas/knight/walk#.bmp");
    prot->img_est[3]=carga_animacion(8,"texturas/knight/regenerate#.bmp");

    boss->charge = carga_animacion(2,"texturas/boss/charge/3_#.bmp");
    boss->death = carga_animacion(7,"texturas/boss/death/6_#.bmp");
    boss->idle = carga_animacion(6,"texturas/boss/idle/1_#.bmp");
    boss->jump = carga_animacion(5,"texturas/boss/jump/4_#.bmp");
    boss->launch = carga_animacion(2,"texturas/boss/launch/5_#.bmp");
    boss->run = carga_animacion(6,"texturas/boss/run/2_#.bmp");
//    Animacion vacia = NULL;

    Imagen vida_llena= Pantalla_ImagenLee("texturas/variados/full_mask.bmp", 1);
    Imagen vida_vacia= Pantalla_ImagenLee("texturas/variados/empty_mask.bmp",1);
    Imagen imag_bala = Pantalla_ImagenLee("texturas/variados/Projectile.bmp",1);
    Imagen imag_prot_proj = Pantalla_ImagenLee("texturas/variados/Shade_Soul.bmp",255);
    Imagen imag_suelo = Pantalla_ImagenLee("texturas/variados/suelo.bmp",255);
    Imagen soul_beam = Pantalla_ImagenLee("texturas/variados/Soul_beam.bmp",255);
    Imagen atk_boss = Pantalla_ImagenLee("texturas/particulas/atk_boss_floor_6.bmp",1);
    Imagen launch_ray = Pantalla_ImagenLee("texturas/particulas/ray_5.bmp",1);
    Imagen launch_ray_p = Pantalla_ImagenLee("texturas/particulas/ray_0.bmp",1);
    Imagen boss_orb = Pantalla_ImagenLee("texturas/particulas/img_boss_charge.bmp",1);
    Imagen boss_proj = Pantalla_ImagenLee("texturas/particulas/boss_p2.bmp",1);

    char root [20];
    sprintf(root,"data/mapa_5.txt");
    Mapa escena = cargar_escenarios(root);

    int frame_time=0;
    time_t start_time=time(NULL);

    //Inicializacion de las variables
    prot->vida= MAX_HEALTH;
    prot->dir_espejo=SDL_FLIP_NONE;
    prot->atk_charge=0;
    prot->void_energy=10;
    prot->cura_reloj=10;
    prot->vx=0;
    prot->vy=0;
    frame_time=0;
    Posicion pos = get_posicion_incial(escena);
    prot->x=get_spawn_x(pos);
    prot->y=get_spawn_y(pos);
    start_time= time(NULL);

    boss->x = POINT_R_X;
    boss->y = POINT_Y;
    boss->w = 70;
    boss->h = 95;
    boss->timer = 100;
    boss->dir_espejo=SDL_FLIP_NONE;
    boss->estado = -1;
    boss->inv = 100;
    boss->vida = 350;
    boss->vy = 0;

    int isTimeToStop = 0;

    //Comienzo del juego
    while(Pantalla_Activa() && (prot->vida > 0 && !isTimeToStop))
    {

        if(Pantalla_TeclaPulsada(REC_STOP)) {isTimeToStop = 1; prot->vida = 0;}


        if(prot->y > pantalla_altura + 20)
        {
            prot->x= get_spawn_x(pos);
            prot->y= get_spawn_y(pos) - 40;
            prot->vx = 0;
            prot->vy = 0;
            introduce_particula(lista_particulas,get_spawn_x(pos)+prot->w/2-40,get_spawn_y(pos)+prot->h/2-40,80,80,SDL_FLIP_NONE,respawn_p);
            prot->invulnerable= 60;
        }

        boss->hasbeenAttacked = 0;
        movimiento_protagonista(prot,get_mapa_bloques(escena,pos));


        // CURA DEL PROTAGONISTA
        if( Pantalla_TeclaPulsada(CARGA) && prot->void_energy >= 2 && prot->estado == 1 && prot->vida<MAX_HEALTH)
        {
            prot->estado = 3;
            prot->cura_reloj--;
            introduce_particula(lista_particulas,prot->x+prot->w/2-20,prot->y+prot->h/2-20,40,40,SDL_FLIP_NONE,soul_charge);
            if(prot->cura_reloj == 0)
            {
                prot->vida++;
                prot->cura_reloj=15;
                prot->void_energy = prot->void_energy - 2;
                introduce_particula(lista_particulas,prot->x+prot->w/2-40,prot->y+prot->h/2-40,80,80,SDL_FLIP_NONE,soul_explotion);
            }

        }
        else
        {
            prot->cura_reloj=15;
        }


        // ATaque del Protagonista
        if(prot->atk_sw_reloj == 0 && Pantalla_TeclaPulsada(ATAQUE))
        {
            if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
            {

                if (solape_rectangulos(boss->x,boss->y,boss->w,boss->h,prot->x-60,prot->y,85,prot->h))
                {
                    if(prot->void_energy < 9)prot->void_energy = prot->void_energy + 2;
                    else prot->void_energy =10;
                    boss->vida = boss->vida - 6;
                    boss->hasbeenAttacked = 1;
                }
                introduce_particula(lista_particulas,prot->x-60,prot->y,60,prot->h,SDL_FLIP_NONE,sw);

            }
            else
            {

                if(solape_rectangulos(boss->x,boss->y,boss->w,boss->h,prot->x,prot->y,85,prot->h))
                {
                    if(prot->void_energy < 9)prot->void_energy = prot->void_energy + 2;
                    else prot->void_energy = 10;
                    boss->vida = boss->vida - 6;
                    boss->hasbeenAttacked = 1;
                }
                introduce_particula(lista_particulas,prot->x+prot->w,prot->y,60,prot->h,SDL_FLIP_HORIZONTAL,sw);

            }
            prot->atk_sw_reloj = 10;
        }
        else if(prot->atk_sw_reloj > 0) prot->atk_sw_reloj--;

        //Crea las balas del protagonista
        if((prot->atk_charge == 0)&&(Pantalla_TeclaPulsada(DISPARO)))
        {
            if(prot->void_energy > 0)
            {
                if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
                {
                    inserta_rafaga(lista_balas,crea_bala(imag_prot_proj,prot->x+15,prot->y+8,-3,0,20,40,1));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
                }
                else
                {
                    inserta_rafaga(lista_balas,crea_bala(imag_prot_proj,prot->x-15,prot->y+8,3,0,20,40,1));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
                }
                prot->atk_charge = 10;
                prot->void_energy--;
            }
            else
            {
                if(prot->dir_espejo == SDL_FLIP_HORIZONTAL)
                {
                    inserta_rafaga(lista_balas,crea_bala(soul_beam,prot->x+15,prot->y+8,-2,0,20,40,2));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,soul_p);
                }
                else
                {
                    inserta_rafaga(lista_balas,crea_bala(soul_beam,prot->x-15,prot->y+8,2,0,20,40,2));
                    introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,soul_p);
                }
                prot->atk_charge = 10;
            }
        }
        else if (prot->atk_charge > 0) prot->atk_charge--;

        if(solape_rectangulos(boss->x, boss->y, boss->w, boss->h, prot->x+5, prot->y, prot->w-10, prot->h) && prot->invulnerable == 0)
        {
            prot->vida= prot->vida - 1;
            introduce_particula(lista_particulas,prot->x+prot->w/2-40,prot->y+prot->h/2-40,80,80,SDL_FLIP_NONE,void_p);
            prot->invulnerable = 60;
        }

        //Colsion de balas enemigas con el protagonista
        if(prot->invulnerable == 0 && (colision_rafaga_especifico(lista_balas,prot->x,prot->y,prot->w,prot->h,6) ||
                                       colision_rafaga_especifico(lista_balas,prot->x,prot->y,prot->w,prot->h,5) ))
        {
            prot->vida= prot->vida - 1;
            introduce_particula(lista_particulas,prot->x-12,prot->y-2,50,50,SDL_FLIP_NONE,void_p);
            prot->invulnerable = 60;
        }


        // Colision balas con boss
        if(colision_rafaga_especifico(lista_balas, boss->x, boss->y, boss->w, boss->h, 1)||
                colision_rafaga_especifico(lista_balas, boss->x, boss->y, boss->w, boss->h, 2))
        {
            boss->inv = 15;
            boss->vida = boss->vida - 10;
            boss->hasbeenAttacked = 1;
        }

        mueve_rafaga(lista_balas,pantalla_anchura,pantalla_altura);
        elimina_bala_colision_rafaga(lista_balas, get_mapa_bloques(escena,pos), 1);
        elimina_bala_colision_rafaga(lista_balas, get_mapa_bloques(escena,pos), 5);
        //Reduccion de la invulnerabilidad contra ataques del protagonista
        if(prot->invulnerable != 0 ) prot->invulnerable--;
        if(boss->inv != 0 ) boss->inv--;
        if(boss->timer != 0 ) boss->timer--;

        //Renderizado de Pantalla

        Pantalla_ColorTrazo(255,255,255,255);
        Pantalla_DibujaImagen(get_mapa_imagen(escena,pos),0,0,pantalla_anchura,pantalla_altura);

        dibuja_boss(boss,frame_time,lista_particulas,void_p,burrow_e,burrow_p,boss_spwan, &isTimeToStop, soul_charge, soul_explotion
                    , prot->x + 20, atk_boss, atk_boss_up, lista_balas, atk_boss_down,launch_big,launch_ray,launch_ray_p,boss_orb, prot->y, boss_proj);
        dibuja_animacion(frame_time/2,prot->img_est[prot->estado],prot->x,prot->y,prot->w,prot->h,0,prot->dir_espejo);
        dibuja_suelo(imag_suelo,get_mapa_bloques(escena,pos));
        dibuja_rafaga(lista_balas);
        dibuja_particulas(lista_particulas);
        dibuja_reloj(start_time);

        health(prot->vida,vida_llena,vida_vacia);
        cantidad_energia(prot->void_energy,11,soul_meter);
        frame_time = frame_time + 1;

        Pantalla_Actualiza();

        Pantalla_Espera(40);
    }
    // Elimina todas las rafagas, enemigos, particulas y la posicion para la siguiente partida
    if (boss->vida <= 0)
    {
        end_game(start_time,time(NULL), get_puntuacion_ruta(escena));
    }
    else
    {
        end_p();
    }
    libera_posicion(pos);
    libera_mapa(escena);

    //Si no se quiere continuar se libera toda la memoria que se hab�a reservado durante la ejecucion del programa

    for (int i=0;  i < 11; i++)
    {
        Pantalla_ImagenLibera(soul_meter[i]);
    }
    free(soul_meter);
    libera_animacion(respawn_p);

    libera_animacion(void_p);
    libera_animacion(soul_p);

    libera_animacion(soul_explotion);
    libera_animacion(soul_charge);

    libera_animacion(sw);
    libera_animacion(token_imgs);

    libera_animacion(burrow_e);
    libera_animacion(burrow_p);
    libera_animacion(boss_spwan);
    libera_animacion(atk_boss_up);
    libera_animacion(atk_boss_down);
    libera_animacion(launch_big);

    for(int i=0; i < 4; i++)
    {
        libera_animacion(prot->img_est[i]);
    }

    Pantalla_ImagenLibera(vida_llena);
    Pantalla_ImagenLibera(vida_vacia);
    Pantalla_ImagenLibera(imag_bala);
    Pantalla_ImagenLibera(imag_prot_proj);
    Pantalla_ImagenLibera(imag_suelo);
    Pantalla_ImagenLibera(soul_beam);
    Pantalla_ImagenLibera(atk_boss);
    Pantalla_ImagenLibera(launch_ray);
    Pantalla_ImagenLibera(launch_ray_p);
    Pantalla_ImagenLibera(boss_orb);
    Pantalla_ImagenLibera(boss_proj);
    //libera_ejercito(grupo_enemigos);
    libera_particulas(lista_particulas);
    libera_rafaga(lista_balas);
}

void puntuacion_menu()
{
    int select = map_select() + 1;
    if (select == 0) return;
    char r [30];
    sprintf(r,"data/puntuacion%d",select);
    Puntuaciones punt = leer_puntuacion(r); // Guardar
    int  indices_ordenados [DEFAULT_CAPACITY];
    int  indices_obtenidos [DEFAULT_CAPACITY];
    for (int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        indices_obtenidos[i] = 0;
    }

    for (int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        int minimo = 25270;
        int indice = 0;
        for (int j=0; j < DEFAULT_CAPACITY; j++)
        {
            int punt_act = get_puntuacion(punt,j);
            if (!indices_obtenidos[j] && minimo >  punt_act)
            {
                minimo = punt_act;
                indice = j;
            }
        }
        indices_ordenados[i] = indice;
        indices_obtenidos[indice] = 1;
    }

    Pantalla_ColorTrazo(255,255,255,255);
    Imagen screen = Pantalla_ImagenLee("texturas/menus/punt.bmp",0);
    int cont = 1;
    sprintf(r,"MAPA %d",select);
    while(Pantalla_Activa() && cont && !isTimeToStop)
    {
        if(Pantalla_TeclaPulsada(REC_STOP)) isTimeToStop = 1;

        Pantalla_DibujaImagen(screen,0,0,Pantalla_Anchura(),Pantalla_Altura());
        Pantalla_DibujaTexto(r,400,120);
        Pantalla_DibujaTexto("NAME       TIME",400,150);
        for (int i = 0; i < DEFAULT_CAPACITY; i++)
        {
            int indice = indices_ordenados[i];
            int time = get_puntuacion(punt,indice);
            char n[5] = "____";
            char r[25];
            char * name = get_nombre(punt,indice);
            n[0] = name[0];
            n[1] = name[1];
            n[2] = name[2];
            n[3] = name[3];

            int seg = time % 60;
            int min = time /60;

            sprintf(r,"%02d:%02d",min,seg);
            Pantalla_DibujaTexto(r,500,25*i+180);
            Pantalla_DibujaTexto(n,400,25*i+180);
        }

        cont = !Pantalla_TeclaPulsada(BACK);
        Pantalla_Actualiza(); // Actualiza
        Pantalla_Espera(80);
    }
    Pantalla_ImagenLibera(screen);
    libera_puntuacion(punt);
}

void juego()
{
    int mapa = map_select();
    if (mapa == -1) return;
    if (mapa == 4) juego_boss_level(mapa);
    else juego_norm(mapa);
}

int main (int argc, char *argv[])
{
    // Creacion
    Pantalla_Crea("Hollow Knight", pantalla_anchura, pantalla_altura);
    int seleccion = menu(); // Menu
    while(!isTimeToStop && seleccion != -1) // Seleccionar
    {
        if(seleccion == 0)  // Segun tipo
        {
            juego();
        }
        else if (seleccion == 1)
        {
            ayuda();
        }
        else if (seleccion == 2)
        {
            puntuacion_menu();
        }
        Pantalla_Espera(250);
        seleccion = menu();
    }

    // Liberacion de la pantalla
    Pantalla_Libera();
    return 0;
}

