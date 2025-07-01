#ifndef __Animacion_H__
#define __Animacion_H__
#include "Pantalla.h"

/**
    \file Animacion.h
    \brief Fichero cabezera para usar las funciones de Animacion
*/

/**
    \brief TDA Animacion
*/
typedef struct Animestr * Animacion;
/**
    \brief Muestra por pantalla la imagen de la animacion correspondiente a la instancia actual. Si supera el numero de imagenes se volvera a hacer el ciclo
    \param instancia Imagen que se quiere mostrar.
    \param a Animacion que se desea mostrar
    \param x Coordenada x de la animacion a mostrar
    \param y Coordenada y de la animacion a mostrar
    \param w Anchura de la animacion a mostrar
    \param h Altura de la animacion a mostrar
    \param ang angulo Angulo con el que se quiere mostrar la animacion
    \param dir_espejo Indica el tipo de trasformacion: SDL_FLIP_NONE no hace nada, SDL_FLIP_HORIZONTAL voltea horizontalmente, SDL_FLIP_VERTICAL voltea verticalmente.
*/
void dibuja_animacion(int instancia, Animacion a, double x, double y, double w, double h, double ang, SDL_RendererFlip dir_espejo);
/**
    \brief Muestra por pantalla la imagen de la animacion correspondiente a la instancia actual, pero recorriendo inversamente las imagenes cuando se supere el maximo
    \param instancia Imagen que se quiere mostrar.
    \param a Animacion que se desea mostrar
    \param x Coordenada x de la animacion a mostrar
    \param y Coordenada y de la animacion a mostrar
    \param w Anchura de la animacion a mostrar
    \param h Altura de la animacion a mostrar
    \param ang angulo Angulo con el que se quiere mostrar la animacion
    \param dir_espejo Idica el tipo de trasformacion: SDL_FLIP_NONE no hace nada, SDL_FLIP_HORIZONTAL voltea horizontalmente, SDL_FLIP_VERTICAL voltea verticalmente.
*/
void dibuja_animacion_reversible(int instancia, Animacion a, double x, double y, double w, double h, double ang, SDL_RendererFlip dir_espejo);
/**
    \brief Carga la animacion de n numero de imagenes de la cadena de strg. La cadena sustituye # por el numero 0-9, para cargar las imagenes
    \pre Las imagenes deben de existir y estar en formato BMP
    \pre n no puede ser mayor de 11 ni menor que 1
    \pre strg no puede ser mas de 99 caracteres de largo
    \param n Numero de imagenes de la animacion
    \param strg Nombre de las imagenes sustiyuyendo el numero por #
    \return Animacion recien creada
*/
Animacion carga_animacion(int n, char * strg);

/**
    \brief Devuelve el numero de imagenes que componen la animacion
    \param a Animacion de la que se quiere obtener el numero de imagenes
    \return Numero de imagenes de la animacion
*/
int get_n_acimacion(Animacion a);

/**
    \brief Libera una animacion de memoria
    \param a Animacion a liberar
*/
void libera_animacion(Animacion a);


#endif
