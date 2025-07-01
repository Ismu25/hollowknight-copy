#ifndef	__Escenario_H__
#define	__Escenario_H__

#include "Colisiones.h"
#include "Pantalla.h"

/**
    \file Escenario.h
    \brief Fichero cabezera para usar las funciones de Escenario
*/

/**
    \brief TDA Escenario
*/
typedef struct EscenarioStr * Escenario;
typedef enum DireccicionRep {ARRIBA=1,DERECHA,ABAJO,IZQUIERDA} Direccicion;
/**
    \brief Crea un escenario con un maximo de rectangulos
    \pre maximo no puede ser negativo
    \param maximo Numero maximo de rectangulos que pueden haber dentro del escenario
    \return Escenario creado
*/
Escenario crear_escenario(int maximo);
/**
    \brief Inserta un nuevo bloque dentro del escenario
    \param esc Escenario donde se va añadir el bloque
    \param x Coordenada x del bloque
    \param y Coordenada y del bloque
    \param w Anchura del bloque
    \param h Altura del bloque
    \param v Visibilidad, indica si el bloque va a ser dibujado (1) o no (0)
*/
void inserta_bloque(Escenario esc, int x, int y, int w, int h,int visible);
/**
    \brief Carga un escenario desde un archivo de texto
    \param a Nombre del archivo del que se va a obtener el escenario
    \return Devuelve el nuevo escenario
*/
Escenario cargar_bloques_achivo (char * a);
/**
    \brief Busca la primera plataforma que se solape con el rectangulo
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param rect Escenario donde buscar la colision
    \return Devuelve el indicador del bloque con el que se esta solapando el rectangulo
*/
int buscar_plataforma_solape (double x, double y, double w, double h,Escenario rect);
/**
    \brief Busca el bloque del cual su zona superior se solapa con el rectangulo
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param rect Escenario donde buscar la colision
    \return Devuelve el indicador del bloque cuya zona superior se ha solapado el rectangulo
*/
int buscar_plataforma_entidad_arriba(double x, double y, double w, double h,Escenario rect);
/**
    \brief Devuelve la direccion con la que se esta solapando el rectangulo del primer bloque con el que hace contacto
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param rect Escenario donde buscar la colision
    \return Devuelve la direccion en la que se esta solapando
*/
Direccicion comp_de_pos_plataforma(double x,double y,double w,double h, Escenario rect);
/**
    \brief Comprueva si algun bloque esta haciendo solape con el rectangulo
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \return 1 Si hay colision
    \return 0 Si no hay colision

*/
int solape_suelo (double x, double y, double w, double h,Escenario rect);
/**
    \brief Comprueva si algun bloque esta haciendo solape con la circunferencia
    \param x Coordenada x del la circunferencia
    \param y Coordenada y del la circunferencia
    \param r Radio del la circunferencia
    \return 1 Si hay colision
    \return 0 Si no hay colision
*/
int solape_suelo_circunferencia(double x, double y, double r,Escenario rect);
/**
    \brief Comprueva si el bloque especifico esta haciendo solape con el rectangulo
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \param plat plataforma del escenario que se quiere comprobar
    \return 1 Si hay colision
    \return 0 Si no hay colision
*/
int solape_con_bloque(double x, double y, double w, double h,Escenario rect,int plat);
/**
    \brief Dibuja los bloques que sean visibles
    \param img Imagen con la que se va dibujar los bloques
    \param s Escenario a dibujar
*/
void dibuja_suelo(Imagen img, Escenario s);
/**
    \brief Libera al escenario
    \param esc Escenario a eliminar de memoria
*/
void libera_escenario(Escenario esc);


#endif
