#ifndef	__Colisiones_H__
#define	__Colisiones_H__


/**
    \file Colisiones.h
    \brief Fichero cabezera para usar las funciones de Colisiones
*/

/**
 \brief Comprueba si el punto esta dentro del rectangulo
 \param x Coordenada X de la esquina superior izquierda del rectangulo
 \param y Coordenada Y de la esquina superior izquierda del rectangulo
 \param w Anchura del rectangulo
 \param h Altura del rectangulo
 \param px Coordenada X del punto
 \param py Coordenada Y del punto
 \param h Altura del rectangulo
 \return 1 Si el punto esta dentro del rectangulo
 \return 0 Si el punto no esta dentro del rectangulo
*/
int dentro_rectangulo( double x, double y, double w, double h, double px, double py);
/**
 \brief Calcula la distancia entre dos puntos
 \param x1 Coordenada X del punto del primer punto
 \param y1 Coordenada Y del punto del primer punto
 \param x1 Coordenada X del punto del segundo punto
 \param y1 Coordenada Y del punto del segundo punto
 \return Devuelve la distancia
*/
double distancia_punto_punto ( double x1,double y1, double x2, double y2);
/**
 \brief Comprueba si hay solape entre las dos circunferencias
 \param x1 Coordenada X del la Circunferencia 1
 \param y1 Coordenada Y del la Circunferencia 1
 \param r1 Radio del la Circunferencia 1
 \param x2 Coordenada X del la Circunferencia 2
 \param y2 Coordenada Y del la Circunferencia 2
 \param r2 Radio del la Circunferencia 2
 \return 1 Si hay solape
 \return 0 Si no hay solape
*/
int solape_circunferencias( double x1, double y1, double r1, double x2, double y2, double r2);
/**
 \brief Comprueba si dos rectangulos se estan solapando
 \param x1 Coordenada X de la esquina superior izquierda del rectangulo 1
 \param y1 Coordenada Y de la esquina superior izquierda del rectangulo 1
 \param w1 Anchura del rectangulo 1
 \param h1 Altura del rectangulo 1
 \param x1 Coordenada X de la esquina superior izquierda del rectangulo 2
 \param y1 Coordenada Y de la esquina superior izquierda del rectangulo 2
 \param w1 Anchura del rectangulo 2
 \param h1 Altura del rectangulo 2
 \return 1 Si hay solape
 \return 0 Si no hay solape
*/
int solape_rectangulos( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2 );
/**
 \brief Comprueba si el rectangulo y el circulo se estan solapando
 \param x1 Coordenada X de la esquina superior izquierda del rectangulo
 \param y1 Coordenada Y de la esquina superior izquierda del rectangulo
 \param w1 Anchura del rectangulo
 \param h1 Altura del rectangulo
 \param x2 Coordenada X del la Circunferencia
 \param y2 Coordenada Y del la Circunferencia
 \param r Radio del la Circunferencia
 \return 1 Si hay solape
 \return 0 Si no hay solape
*/
int solape_cicunferencia_rectangulo(double x1, double y1, double w1, double h1, double x2, double y2, double r);



#endif
