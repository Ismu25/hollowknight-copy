#ifndef __Ejercito_H__
#define __Ejercito_H__

#include "Colisiones.h"
#include "Rafaga.h"
#include "Escenario.h"
#include "Animacion.h"
#include "Particulas.h"
#include "Enemigo.h"

/**
    \file Ejercito.h
    \brief Fichero cabezera para usar las funciones de Ejercito
*/

/**
    \brief TDA Ejercito
*/
typedef struct EjercitoStr * Ejercito;

/**
    \brief Crea un ejercito
    \pre maximo debe de ser mayor que 0
    \param maximo Numero maximo de enemigos que caben el ejercito
    \return Ejercito nuevo
*/
Ejercito crea_ejercito(int maximo);
/**
    \brief Libera la memoria del ejercito
    \param e Ejercito a liberar
*/
void libera_ejercito( Ejercito e );
/**
    \brief Elemina a todos los enemigos del ejercito
    \param e Ejercito a limpiar
*/
void limpia_ejercito( Ejercito e );
/**
    \brief Inserta un enemigo nuevo enemigo
    \param e Ejercito en el que insertar el enemigo
    \param tipo_enemigo Tipo de enemigo, cambiara su tipo de movimiento
    \param x Coordenada x del punto de spawn
    \param y Coordenada y del punto de spawn
    \param w Anchura del enemigo
    \param h Altura del enemigo
    \param animacion_movimiento Animacion del enemigo al moverse
    \param animacion_muerte Animacion del enemigo al morir
    \param animacion_atk Animacion del enemigo al lanzar una bala
*/
void inserta_enemigo(Ejercito e, TipoEnemigo tipo_enemigo,double x,double y,double h,double w,int vida, Animacion animacion_movimiento, Animacion animacion_muerte, Animacion animacion_atk);
/**
    \brief Dibuja los enemigos
    \param e Ejercito a dibujar
*/
void dibuja_ejercito( Ejercito e);
/**
    \brief Busca la colision entre el ejercito y un rectangulo
    \param e Ejercito a buscar la colision
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \return 1 Hay colision
    \return 0 No hay colision
*/
int colision_ejercito_objeto( Ejercito e, double x, double y, double w, double h );
/**
    \brief Mueve a los enemigos del Ejercito segun el tipo
    \param e Ejercito a mover
    \param center_x Coordenada x del Punto de interes para los enemigos
    \param center_y Coordenada y del Punto de interes para los enemigos
*/
void mueve_ejercito(Ejercito e, Escenario s,double center_x, double center_y);
/**
    \brief Busca si hay colision entre el ejercito y las balas.
    \param e Ejercito a comparar
    \param r Rafaga a comparar
    \param tipo_bala Tipo de bala con el que hace la colision el ejercito
    \return Devuele el numero de enemigos muertos
*/
int colision_ejercito_rafaga( Ejercito e, Rafaga r, int tipo_bala );
/**
    \brief Crea balas para los enemigos de un mismo tipo
    \param e Ejercito a disparar
    \param tipo Tipos del enemigo a generar las balas
    \param r Rafaga en la que guardar las balas
    \param img Imagen de la bala a crear
    \param center_x Punto de coordenada x al que va la bala
    \param center_y Punto de coordenada y al que va la bala

*/
void ejercito_crea_balas(Ejercito e, int tipo, Rafaga r, Imagen img,double center_x,double center_y);
/**
    \brief Devuelve el numero de enemigos en el Ejercito
    \param e Ejercito del que se va ha obtener el numero de enemigos
    \return Numero de enemigos
*/
int get_n_enemigos(Ejercito e);
/**
    \brief Busca la colision entre el ejercito y un rectangulo, si es positivo quita puntos de vida al enemigo
    \param e Ejercito a buscar la colision
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param damage Vida que se le quita al enemigo si hay colision
    \return numero de enemigos muertos
*/
int colision_ejercito_objeto_damage(Ejercito e, double x, double y, double w, double h, int damage);
void ejercito_crea_balas_compl(Ejercito e, Rafaga r, Imagen img,double center_x,double center_y);
#endif
