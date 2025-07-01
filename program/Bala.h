#ifndef	__Bala_H__
#define	__Bala_H__

#include "Pantalla.h"
#include "Colisiones.h"

/**
    \file Bala.h
    \brief Fichero cabezera para usar las funciones de Bala
*/

/**
    \brief Tipo de Dato Bala
*/
typedef struct BalaStruct * Bala;

/**
 \brief Crea una Bala con los datos aportados
 \param textura La Imagen que se utiliza para mostrar la bala
 \param x Coordenada x inicial de la bala
 \param y Coordenada y inicial de la bala
 \param vx Velocidad lateral de la bala
 \param vx Velocidad vertical de la bala
 \param h Altura de la bala
 \param w Anchura de la bala
 \param type Tipo de bala
 \return Devuelve la Bala creada
*/
Bala crea_bala ( Imagen textura, double x, double y, double vx, double vy, double h, double w, int type);

/**
 \brief Libera de memoria la bala
 \param a Bala a Eliminar
 */
void libera_bala( Bala a);

/**
 \brief Mueve la bala
 \param a Bala a mover
 */
void mueve_bala(Bala a);

/**
\brief Muestra la bala en pantalla
\param imag La Imagen que se utiliza para mostrar la bala
\param x Coordenada x de la bala
\param y Coordenada y de la bala
\param vx Velocidad lateral de la bala
\param vx Velocidad vertical de la bala
\param h Altura de la bala
\param w Anchura de la bala
*/
void dibuja_bala(Bala a);

/**
\brief Devuelve la coordenada x de la bala
\param b Bala de la que se quiere obtener la coordenada
\return Coordenada x de la bala
*/
double get_x_bala( Bala b );

/**
\brief Devuelve la coordenada y de la bala
\param b Bala de la que se quiere obtener la coordenada
\return Coordenada y de la bala
*/
double get_y_bala( Bala b );

/**
\brief Devuelve la anchura de la bala
\param b Bala de la que se quiere obtener la anchura
\return Anchura de la bala
*/
double get_w_bala( Bala b );

/**
\brief Devuelve la altura de la bala
\param b Bala de la que se quiere obtener la altura
\return Altura de la bala
*/
double get_h_bala( Bala b );

/**
\brief Devuelve el tipo de la bala
\param b Bala de la que se quiere obtener el tipo
\return Tipo de bala
*/
int get_type_bala( Bala b );
/**
\brief Comprueba si hay colision entre una bala y un rectangulo definido por sus coordenadas x e y, altura y anchura
\param b Bala a la que se va a comprobar su colision
\param x Coordenada X de la esquina superior izquierda del rectangulo
\param y Coordenada Y de la esquina superior izquierda del rectangulo
\param w Anchura del rectangulo
\param h Altura del rectangulo
\return 1 Hay colision
\return 0 No hay colision
*/
int colision_bala( Bala b, double x, double y, double w, double h );

#endif
