#ifndef __Puntuacion_H__
#define __Puntuacion_H__

#define DEFAULT_CAPACITY 10
typedef struct PuntuacionesStr * Puntuaciones;

Puntuaciones crear_puntuacion(int capacity);
void libera_puntuacion(Puntuaciones punts);
Puntuaciones leer_puntuacion(char * ruta);
void introducir_puntuacion(Puntuaciones punts, int puntos, char * nombre);
void guardar_puntuacion_archivo(Puntuaciones punts, char * ruta);
int get_puntuacion(Puntuaciones punt, int indice);
char * get_nombre(Puntuaciones punt, int indice);

#endif // __Puntuacion_H__
