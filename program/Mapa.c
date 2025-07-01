#include "Mapa.h"
#include <stdio.h>
#include <stdlib.h>

struct ConexStr
{
    double x1;
    double y1;
    double h1;
    double w1;
    double x2;
    double y2;
    int escenario2;
};

struct Conexstr_l
{
    int n_conexiones;
    struct ConexStr * esc;
};
typedef struct Conexstr_l * Conex;

struct PosicionStr
{
    int n;
    double x;
    double y;
};

typedef struct PosicionStr * Posicion;

struct MapaConjuntoStr
{
    Imagen fondo;
    Escenario bloques_escenario;
    Escenario acido_escenario;
    Conex conexiones_escenario;
    Token tokens_escenario;
    Ejercito enemigos_escenario;
};

struct MapaStr
{
    int n_escenarios;
    struct MapaConjuntoStr * escenario;
    int n_animaciones;
    Animacion * animaciones;
    struct PosicionStr inicial;
    char ruta_puntos [32];
};

typedef struct MapaStr * Mapa;



Mapa cargar_escenarios(char * nombre_archivo)
{
    FILE * fp;
    fp = fopen(nombre_archivo, "r");
    if(fp != NULL)
    {
        int numer = 0;
        char ru[40];
        Mapa nuevo = malloc(sizeof(struct MapaStr));

        fscanf (fp,"Numero de Animaciones: %d\n\n",&(nuevo->n_animaciones));
        nuevo->animaciones = malloc(sizeof(Animacion) * nuevo->n_animaciones);
        for(int j = 0; j < nuevo->n_animaciones; j++)
        {
            fscanf(fp,"Numero de frames: %d\n", &numer);
            fscanf(fp,"Ruta: %s\n\n",ru);
            nuevo->animaciones[j] = carga_animacion(numer, ru);
        }

        fscanf(fp,"Numero de Escenarios: %d\n",&(nuevo->n_escenarios));
        nuevo->escenario = malloc(nuevo->n_escenarios * sizeof(struct MapaConjuntoStr));
        fscanf(fp,"Posicion Inicial: %d,%lf,%lf\n",&(nuevo->inicial.n),&(nuevo->inicial.x),&(nuevo->inicial.y));
        fscanf(fp,"Ruta puntos: %s\n\n",nuevo->ruta_puntos);
        for (int i=0; i < nuevo->n_escenarios; i++)
        {

            char cp[50];
            fscanf(fp,"Nombre de Imagen: %s\n",cp);
            nuevo->escenario[i].fondo = Pantalla_ImagenLee(cp, 0);


            int n_bloques, n_tokens, x, y, w, h, visible, estado, n_enemigos;

            fscanf(fp,"Numero de bloques: %d\n",&n_bloques);
            nuevo->escenario[i].bloques_escenario = crear_escenario(n_bloques);
            for (int j = 0; j < n_bloques ; j++)
            {
                fscanf(fp,"%d,",&x);
                fscanf(fp,"%d,",&y);
                fscanf(fp,"%d,",&w);
                fscanf(fp,"%d,",&h);
                fscanf(fp,"%d\n",&visible);
                inserta_bloque(nuevo->escenario[i].bloques_escenario,x,y,w,h,visible);
            }

            fscanf(fp,"Numero de bloques de acido: %d\n",&n_bloques);
            nuevo->escenario[i].acido_escenario = crear_escenario(n_bloques);
            for (int j = 0; j < n_bloques ; j++)
            {
                fscanf(fp,"%d,",&x);
                fscanf(fp,"%d,",&y);
                fscanf(fp,"%d,",&w);
                fscanf(fp,"%d,",&h);
                fscanf(fp,"%d\n",&visible);
                inserta_bloque(nuevo->escenario[i].acido_escenario,x,y,w,h,visible);
            }

            nuevo->escenario[i].conexiones_escenario = malloc(sizeof(struct Conexstr_l));
            fscanf(fp,"Numero de conexiones: %d\n",&(nuevo->escenario[i].conexiones_escenario->n_conexiones));

            nuevo->escenario[i].conexiones_escenario->esc= malloc(nuevo->escenario[i].conexiones_escenario->n_conexiones * sizeof(struct ConexStr));
            for (int j = 0; j < nuevo->escenario[i].conexiones_escenario->n_conexiones ; j++)
            {
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].x1));
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].y1));
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].w1));
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].h1));
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].x2));
                fscanf(fp,"%lf,",&(nuevo->escenario[i].conexiones_escenario->esc[j].y2));
                fscanf(fp,"%d\n",&(nuevo->escenario[i].conexiones_escenario->esc[j].escenario2));
            }


            fscanf(fp,"Numero de tokens: %d\n",&n_tokens);
            nuevo->escenario[i].tokens_escenario = crea_tokens(n_tokens);
            for (int j = 0; j < n_tokens ; j++)
            {
                fscanf(fp,"%d,",&x);
                fscanf(fp,"%d,",&y);
                fscanf(fp,"%d,",&w);
                fscanf(fp,"%d,",&h);
                fscanf(fp,"%d\n",&estado);
                inserta_token(nuevo->escenario[i].tokens_escenario,x,y,w,h,estado);
            }


            fscanf(fp,"Numero de enemigos: %d\n",&n_enemigos);
            char tipo;
            TipoEnemigo te;
            int amv, amu, aa, vida;
            nuevo->escenario[i].enemigos_escenario = crea_ejercito(n_enemigos+8);
            for(int j = 0; j < n_enemigos; j++)
            {
                fscanf(fp,"%c,%d,%d,%d,%d,%d,%d,%d,%d\n", &tipo,&x,&y,&h,&w,&vida,&amv,&amu,&aa);
                if(tipo == 'D') te = DISTANCIADOR;
                else if (tipo == 'R') te = VOLARAPIDO;
                else if (tipo == 'S') te = DESLIZASUELOS;
                else if (tipo == 'V') te = VOLADOR;
                else if (tipo == 'U') te = VOLADORULTRARAPIDO;
                else if (tipo == 'B') te = DISPARADORDOBLE;
                else if (tipo == 'M') te = MULTIPLICADOR;

                inserta_enemigo(nuevo->escenario[i].enemigos_escenario,te, x, y ,h, w, vida,
                                nuevo->animaciones[amv], nuevo->animaciones[amu], nuevo->animaciones[aa]);
            }
            fscanf(fp,"\n");
        }

        return nuevo;
    }

    printf("Error al abrir el archivo\n");
    return NULL;
}

Imagen get_mapa_imagen(Mapa a,Posicion p)
{
    return a->escenario[p->n].fondo;
}

Escenario get_mapa_bloques(Mapa a,Posicion p)
{
    return a->escenario[p->n].bloques_escenario;
}

Escenario get_mapa_acido(Mapa a,Posicion p)
{
    return a->escenario[p->n].acido_escenario;
}

Token get_mapa_tokens(Mapa a,Posicion p)
{
    return a->escenario[p->n].tokens_escenario;
}

Ejercito get_mapa_ejercito(Mapa a, Posicion p)
{
    return a->escenario[p->n].enemigos_escenario;
}

Posicion incializa_posicion(int escenario,double spawn_x, double spawn_y)
{
    if(escenario < 0)
    {
        printf("Escenario no contemplado");
        return NULL;
    }
    Posicion p= malloc(sizeof(struct PosicionStr));
    p->n=escenario;
    p->x =spawn_x;
    p->y=spawn_y;
    return p;
}

Posicion get_posicion_incial(Mapa m)
{
    return incializa_posicion(m->inicial.n,m->inicial.x,m->inicial.y);
}

char * get_puntuacion_ruta(Mapa m)
{
    return m->ruta_puntos;
}
double get_spawn_x (Posicion p)
{
    return p->x;
}

double get_spawn_y (Posicion p)
{
    return p->y;
}

int get_escenario(Posicion p)
{
    return p->n;
}

int comprueba_conex_escenarios(Mapa m, Posicion p, double * x, double * y,double w,double h)
{
    for(int i=0; i< m->escenario[p->n].conexiones_escenario->n_conexiones; i++)
    {
        if(solape_rectangulos(*x,*y,w,h,m->escenario[p->n].conexiones_escenario->esc[i].x1,m->escenario[p->n].conexiones_escenario->esc[i].y1,
                              m->escenario[p->n].conexiones_escenario->esc[i].w1,m->escenario[p->n].conexiones_escenario->esc[i].h1))
        {
            p->x=m->escenario[p->n].conexiones_escenario->esc[i].x2;
            p->y=m->escenario[p->n].conexiones_escenario->esc[i].y2;
            p->n=m->escenario[p->n].conexiones_escenario->esc[i].escenario2;
            *x=p->x;
            *y=p->y;
            return 1;
        }
    }
    return 0;
}

void test_dibuja_conex_escenarios(Mapa m, Posicion p)
{

    for(int i=0; i< m->escenario[p->n].conexiones_escenario->n_conexiones; i++)
    {
        Pantalla_ColorTrazo(255, 0, 0, 255);
        Pantalla_DibujaRectangulo(m->escenario[p->n].conexiones_escenario->esc[i].x1,m->escenario[p->n].conexiones_escenario->esc[i].y1,
                                  m->escenario[p->n].conexiones_escenario->esc[i].w1,m->escenario[p->n].conexiones_escenario->esc[i].h1);
        if(m->escenario[p->n].conexiones_escenario->esc[i].escenario2 == p->n)
        {
            Pantalla_ColorTrazo(0,255, 0, 255);
            Pantalla_DibujaRectangulo(m->escenario[p->n].conexiones_escenario->esc[i].x2,m->escenario[p->n].conexiones_escenario->esc[i].y2,10,10);
        }
    }
    Pantalla_ColorTrazo(255,255, 255, 255);
}

void libera_mapa(Mapa m)
{
    for(int i=0; i<m->n_animaciones; i++)
    {
        libera_animacion(m->animaciones[i]);
    }
    free(m->animaciones);
    for(int i=0; i<m->n_escenarios; i++)
    {
        Pantalla_ImagenLibera(m->escenario[i].fondo);
        libera_escenario(m->escenario[i].bloques_escenario);
        libera_escenario(m->escenario[i].acido_escenario);
        free(m->escenario[i].conexiones_escenario->esc);
        free(m->escenario[i].conexiones_escenario);
        libera_tokens(m->escenario[i].tokens_escenario);
        libera_ejercito(m->escenario[i].enemigos_escenario);
    }
    free(m->escenario);
    free(m);
    return;
}

void libera_posicion(Posicion p)
{
    free(p);
}

int all_token_taken(Mapa m)
{
    for(int i=0; i < m->n_escenarios; i++)
    {
        if (!all_completed(m->escenario[i].tokens_escenario)) return 0;
    }
    return 1;
}
