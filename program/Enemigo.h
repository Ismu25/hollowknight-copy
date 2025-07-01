#ifndef __Enemigo_H__
#define __Enemigo_H__

#include "Colisiones.h"
#include "Rafaga.h"
#include "Escenario.h"
#include "Animacion.h"

/**
    \file Enemigo.h
    \brief Fichero cabezera para usar las funciones de Enemigo
*/
/**
    \brief Tipo de Dato Enemigo
*/
typedef struct EnemigoStr * Enemigo;
/**
    \brief Tipo de Enemigo
*/
typedef enum TipoEnemigoStr {DISTANCIADOR,VOLARAPIDO,DESLIZASUELOS,VOLADOR,VOLADORULTRARAPIDO,DISPARADORDOBLE,MULTIPLICADOR} TipoEnemigo; // D R S V

/**
    \brief Crea un enemigo
    \param tipo_enemigo Tipo de enemigo, cambiara su tipo de movimiento
    \param x Coordenada x del punto de spawn
    \param y Coordenada y del punto de spawn
    \param w Anchura del enemigo
    \param h Altura del enemigo
    \param animacion_movimiento Animacion del enemigo al moverse
    \param animacion_muerte Animacion del enemigo al morir
    \param animacion_atk Animacion del enemigo al lanzar una bala
    \return Nuevo Enemigo
*/
Enemigo crea_enemigo(TipoEnemigo tipo_enemigo,double x,double y,double h,double w,int vida, Animacion animacion_movimiento, Animacion animacion_muerte, Animacion animacion_atk);
/**
    \brief Dibuja al Enemigo
    \param e Enemigo a dibujar
*/
void dibuja_enemigo( Enemigo e);
/**
    \brief Busca la colision entre el enemigo y un rectangulo
    \param e Enemigo a buscar la colision
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \return 1 Hay colision
    \return 0 No hay colision
*/
int solape_enemigo(Enemigo e, double x, double y, double w, double h);
/**
    \brief Mueve al enemigo
    \param e Enemigo a mover
    \param center_x Coordenada x del Punto de interes para el enemigo
    \param center_y Coordenada y del Punto de interes para el enemigo
*/
void mueve_enemigo(Enemigo e,Escenario s,double center_x, double center_y);
/**
    \brief Devuelve la vida del enemigo
    \param e Enemigo del que se va a obtener la vida
    \return Vida del enemigo
*/
int vida_enemigo(Enemigo e);
/**
    \brief Devuelve la animacion de muerte del enemigo
    \param e Enemigo del que se va a obtener la animacion
    \return Animacion de muerte del enemigo
*/
Animacion muerte_enemigo(Enemigo e);
/**
    \brief Devuelve la coordenada x del enemigo
    \param e Enemigo del que se va a obtener la coordenada x
    \return Coordenada x del enemigo
*/
double get_x_enemigo(Enemigo e);
/**
    \brief Devuelve la coordenada y del enemigo
    \param e Enemigo del que se va a obtener la coordenada y
    \return Coordenada y del enemigo
*/
double get_y_enemigo(Enemigo e);
/**
    \brief Devuelve la anchura del enemigo
    \param e Enemigo del que se va a obtener la anchura
    \return Anchura del enemigo
*/
double get_w_enemigo(Enemigo e);
/**
    \brief Devuelve la altura del enemigo
    \param e Enemigo del que se va a obtener la altura
    \return Altura del enemigo
*/
double get_h_enemigo(Enemigo e);
/**
    \brief Devuelve el giro que se hace al dibujar al enemigo
    \param e Enemigo del que se va a obtener el giro
    \return Devuelve el giro
*/
SDL_RendererFlip get_dir_espejo_enemigo(Enemigo e);
/**
    \brief Crea balas para desde el enemigo
    \param e Enemigo a disparar
    \param r Rafaga en la que guardar la bala
    \param img Imagen de la bala a crear
    \param center_x Punto de coordenada x al que va la bala
    \param center_y Punto de coordenada y al que va la bala

*/
void enemigo_crea_bala(Enemigo e, Rafaga r, Imagen img,double center_x,double center_y);
/**
    \brief Devuelve el tipo del enemigo
    \param e Enemigo del que se va a obtener el tipo
    \return Tipo del enemigo
*/
TipoEnemigo get_tipo_enemigo(Enemigo e);
/**
    \brief Libera al Enemigo de memoria
    \param e Enemigo a liberar de memoria
*/
void libera_enemigo(Enemigo e);
/**
    \brief Busca si hay colision entre el enemigo y la rafaga.
    \param e Enemigo a comparar
    \param r Rafaga a comparar
    \param tipo_bala Tipo de bala con el que hace la colision al enemigo
    \return 1 Si ha habido colision, ademas elimina la bala y le quita vida al enemigo
    \return 0 Si no hay colsion
*/
int colision_enemigo_rafaga(Enemigo e , Rafaga r, int tipo_bala);
/**
    \brief Busca si hay colision entre el enemigo y el rectangulo, si es así le quita vida al enemigo.
    \param e Enemigo a comparar
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param damage Vida a quitar si hay colision con el rectangulo
    \return 1 Si hay colsion, ademas le quita la vida al enemigo
    \return 0 Si no hay colsion

*/
int colision_enemigo_objeto_damage(Enemigo e, double x, double y, double w, double h, int damage);
Animacion get_mov_enemigo(Enemigo e);
Animacion get_atk_enemigo(Enemigo e);
Animacion get_muerte_enemigo(Enemigo e);

#endif // __Enemigo_H__
