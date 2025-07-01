#include "Colisiones.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int dentro_rectangulo( double x, double y, double w, double h, double px, double py)
{

    if ((x<=px)&&(px<=(x+w))&&(y<=py)&&(py<=(y+h)))
    {
        return 1;
    }
    return 0;
}

double distancia_punto_punto ( double x1,double y1, double x2, double y2)
{
    return(sqrt(pow(x1-x2, 2)+ pow(y1-y2,2)));
}

int solape_circunferencias( double x1, double y1, double r1, double x2, double y2, double r2)
{

    if ((distancia_punto_punto(x1,y1,x2,y2) < (r1+r2))||(fabs(distancia_punto_punto(x1,y1,x2,y2) - (r1+r2) < 0.0001)))
    {
        return 1;
    }
    return 0;

}

int solape_rectangulos( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2 )
{
    if ( x1 > x2+w2 ) return 0;
    if ( x1+w1 < x2 ) return 0;
    if ( y1 > y2+h2 ) return 0;
    if ( y1+h1 < y2 ) return 0;

    return 1;
}

int solape_cicunferencia_rectangulo(double x1, double y1, double w1, double h1, double x2, double y2, double r)
{
    double px = x2, py = y2;

    if ( px < x1 )
    {
        px = x1;
    }
    if ( px > x1 + w1 )
    {
        px = x1 + w1;
    }

    if ( py < y1 )
    {
        py = y1;
    }
    if ( py > y1 + h1 )
    {
        py = y1 + h1;
    }

    double distancia = sqrt((x2-px)*(x2-px)+(y2-py)*(y2-py));
    if (distancia < r)
    {
        return 1;
    }
    return 0;
}
