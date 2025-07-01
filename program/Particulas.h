#ifndef __Particulas_H__
#define __Particulas_H__

#include "Animacion.h"
#include "Pantalla.h"


/**
    \file Particulas.h
    \brief Fichero cabezera para usar las funciones de Particulas
*/

/**
    \brief TDA Particulas
*/
typedef struct Partstr * Particulas;
/**
    \brief Crea particulas
    \return Particula nuevas
*/
Particulas crea_particulas();
/**
    \brief Introduce una nueva Particula
    \param c Particulas en la que insertar
    \param x Coordenada x la particula nueva
    \param y Coordenada y la particula nueva
    \param w Anchura la particula nueva
    \param h Altura la particula nueva
    \param espejo Indica el tipo de trasformación: SDL_FLIP_NONE no hace nada, SDL_FLIP_HORIZONTAL voltea horizontalmente, SDL_FLIP_VERTICAL voltea verticalmente.
    \param anima Animacion de la particula
*/
void introduce_particula(Particulas c, int x, int y, int w, int h, SDL_RendererFlip espejo, Animacion anima );
/**
    \brief Dibuja las particulas y elimina las que ya hayan finalizado
    \param c Particulas a dibujar
*/
void dibuja_particulas(Particulas c);
/**
    \brief Elimina las particulas
    \param c Particulas a limpiar
*/
void limpia_particulas(Particulas c);
/**
    \brief Libera la memoria asociada a las particulas, las animaciones asocidas no se eliminan, estas se deben liberar aparte
    \param c Particulas a liberar
*/
void libera_particulas(Particulas c);


#endif // __Particulas_H__
