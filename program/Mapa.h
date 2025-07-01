#ifndef __Mapa_H__
#define __Mapa_H__

#include "Ejercito.h"
#include "Animacion.h"
#include "Escenario.h"
#include "Pantalla.h"
#include "Tokens.h"


/**
    \file Mapa.h
    \brief Fichero cabezera para usar las funciones de Mapa
*/

/**
    \brief TDA Mapa
*/
typedef struct MapaStr * Mapa;
/**
    \brief Tipo de dato Posicion
*/
typedef struct PosicionStr * Posicion;


/**
    \brief Inicializa la posicion en un punto de un escenario
    \pre Solo se contemplan escenarios en [0,n_escenarios-1]
    \param escenario Escenario de inicializacion
    \param spawn_x Coordenada x de inicializacion
    \param spawn_y Coordenada y de inicializacion
    \return Nueva Posicion
*/
Posicion incializa_posicion(int escenario,double spawn_x, double spawn_y);
/**
    \brief Devuelve la cordenada x de inicializacion actual
    \param p Posicion de la que se va a obtener la coordenada
    \return Coordenada x de inicializacion
*/
double get_spawn_x (Posicion p);
/**
    \brief Devuelve la cordenada y de inicializacion actual
    \param p Posicion de la que se va a obtener la coordenada
    \return Coordenada y de inicializacion
*/
double get_spawn_y (Posicion p);
/**
    \brief Devuelve el identificador del escenario actual
    \param p Posicion de la que se va a obtener el identificador de escenario
    \return Identificador del Escenario
*/
int get_escenario(Posicion p);
/**
    \brief Libera la memoria asociada a la posicion
    \param p Poscion a liberar
*/
void libera_posicion(Posicion p);

/**
    \brief Carga el Mapa en memoria desde un archivo de texto
    \param nombre_archivo Nombre del archivo que contiene la informacion del Mapa
    \return Mapa creado
*/
Mapa cargar_escenarios(char * nombre_archivo);
/**
    \brief Devuelve la imagen asociada al escenario actual
    \param a Mapa con el que se esta trabajando
    \param p Posicion de la que se va a devolver la imagen
    \return Imagen del escenario actual
*/
Imagen get_mapa_imagen(Mapa a,Posicion p);
/**
    \brief Devuelve el escenario actual
    \param a Mapa con el que se esta trabajando
    \param p Posicion de la que se va a devolver el escenario
    \return Escenario actual
*/
Escenario get_mapa_bloques(Mapa a,Posicion p);
/**
    \brief Devuelve el escenario Acido
    \param a Mapa del que se van a obtener los bloques de acido
    \param p Posicion de la que se va a devolver el escenario
    \return Bloques de acido
*/
Escenario get_mapa_acido(Mapa a,Posicion p);
/**
    \brief Devuelve los tokens del escenario actual
    \param a Mapa del que se van a obtener los tokens
    \param p Posicion de la que se va a devolver el tokens
    \return Tokens del escenaio actual
*/
Token get_mapa_tokens(Mapa a, Posicion p);
/**
    \brief Comprueba que el rectangulo esta tocando la conexion entre mapas, si es asi cambia el escenario y los valores de x e y
    \param m Mapa con el que se esta trabajando
    \param p Posicion actual
    \param x Coordenada x del Rectangulo a comprobar si esta tocando la intercambio
    \param y Coordenada y del Rectangulo a comprobar si esta tocando la intercambio
    \param w Anchura del Rectangulo a comprobar si esta tocando la intercambio
    \param h Altura del Rectangulo a comprobar si esta tocando la intercambio
    \return 1 Ha habido colision y se han cambiado los valor de x e y, asi como el escenario
    \return 0 No ha habido conexion
*/
int comprueba_conex_escenarios(Mapa m, Posicion p, double * x, double * y,double w,double h);
/**
    \brief permite mostrar las interconexiones para comprobar que se encuentran en los lugares correctos
    \param m Mapa con el que se esta trabajando
    \param p Posicion actual
*/
void test_dibuja_conex_escenarios(Mapa m, Posicion p);
/**
    \brief Libera la memoria asociada a la posicion
    \param m Mapa a liberar

*/
void libera_mapa(Mapa m);

Ejercito get_mapa_ejercito(Mapa a, Posicion p);
int all_token_taken(Mapa m);
Posicion get_posicion_incial(Mapa m);
char * get_puntuacion_ruta(Mapa m);

#endif // __Mapa_H__
