#ifndef	__Rafaga_H__
#define	__Rafaga_H__

#include "Bala.h"
#include "Escenario.h"
#include "Colisiones.h"


/**
    \file Rafaga.h
    \brief Fichero cabezera para usar las funciones de Rafaga
*/

/**
    \brief TDA Rafaga
*/
typedef struct RafagaStr * Rafaga;
/**
 \brief Crea una rafaga
 \return Devuelve la rafaga recien creada
*/
Rafaga crea_rafaga();
/**
 \brief Introduce una nueva bala a la rafaga
 \param b Bala que se va a introducir en la rafaga
*/
void inserta_rafaga( Rafaga raf, Bala b);
/**
  \brief Libera la memoria la rafaga
  \param raf Rafaga a liberar
*/
void libera_rafaga(Rafaga raf);
/**
  \brief Elimina la balas de la rafaga
  \param raf Rafaga a limpiar
*/
void limpia_rafaga(Rafaga raf);
/**
 \brief Mueve todas las balas de la Rafaga y elimina a aquellas que se hallan salido de la pantalla
 \param raf Rafaga a mover las balas
*/
void mueve_rafaga(Rafaga raf, int anchura_pantalla, int altura_pantalla);
/**
 \brief Dibuja todas las balas de la Rafaga
 \param raf Rafaga a dibujar
*/
void dibuja_rafaga(Rafaga raf);
/**
 \brief Compueba si hay colision de alguna de la balas de la rafaga con un rectangulo, si encuntra una la elimina y para
 \param raf Rafaga de la que se va a comprobar la colision
 \param x Coordenada X de la esquina superior izquierda del rectangulo
 \param y Coordenada Y de la esquina superior izquierda del rectangulo
 \param w Anchura del rectangulo
 \param h Altura del rectangulo
 \return 0 No hay ninguna bala que haya colisionado
 \return 1 Ha encontrado y eliminado una bala de la rafaga
*/
int colision_rafaga(Rafaga raf, double x, double y, double w, double h);
/**
 \brief Compueba si hay colision de alguna de la balas de un mismo tipo de la rafaga con un rectangulo, si encuntra una la elimina y para
 \param raf Rafaga de la que se va a comprobar la colision
 \param x Coordenada X de la esquina superior izquierda del rectangulo
 \param y Coordenada Y de la esquina superior izquierda del rectangulo
 \param w Anchura del rectangulo
 \param h Altura del rectangulo
 \param tipo Tipo de bala a comprobar
 \return 0 No hay ninguna bala que haya colisionado
 \return 1 Ha encontrado y eliminado una bala de la rafaga
*/
int colision_rafaga_especifico(Rafaga raf, double x, double y, double w, double h,int tipo);
/**
    \brief Comprueba la colision de balas de un tipo especifico con el Escenario y las elimina si es el caso
    \param raf Rafaga de la que se va a comprobar la colision
    \param rect Escenario a comparar
    \param tipo Tipo de bala a comprobar
*/
void elimina_bala_colision_rafaga(Rafaga raf, Escenario rect, int tipo);
void elimina_balas_tipo(Rafaga raf, int tipo);
#endif
