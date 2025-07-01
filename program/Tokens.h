#ifndef __Tokens_H__
#define __Tokens_H__

#include "Animacion.h"
#include "Pantalla.h"
#include "Colisiones.h"

/**
    \file Tokens.h
    \brief Fichero cabezera para usar las funciones de Tokens
*/
/**
    \brief TDA Tokens
*/
typedef struct TokenStr * Token;
/**
    \brief Estados en los que puede estar el token
*/
typedef enum EstadoTokenStr {OBTENIDO,ACTIVO,DESACTIVO} Estado_token;
/**
    \brief Crea un conjunto de tokens con un maximo de n
    \pre n debe ser mayor que 0
    \param n Numero maximo de tokens
    \return Tokens creados
*/
Token crea_tokens(int n_tokens_maximo);
/**
    \brief Libera la memoria asociada a los tokens, excepto por las animaciones, que deben de ser liberadas aparte
    \param tokens Tokens a liberar
*/
void libera_tokens(Token tokens);
/**
    \brief Inserta un nuevo Token
    \param tokens Tokens donde insertar el nuevo token
    \param x Coordenada x del nuevo token
    \param y Coordenada y del nuevo token
    \param w Anchura del nuevo token
    \param h Altura del nuevo token
    \param estado Define el estado del nuevo token
*/
void inserta_token(Token tokens, int x, int y, int w, int h, Estado_token estado);
/**
    \brief Dibuja los tokens si su estado es ACTIVO
    \param tokens Tokens a dibujar
    \param anima Animacion del los tokens
*/
void dibuja_tokens(Token tokens, Animacion anima);
/**
    \brief Activa los tokens que esten DESACTIVADOS
    \param tokens Tokens a Activar
*/
void activa_tokens(Token tokens);
/**
    \brief Compara si algun token estan tocando el rectangulo, cambia el estado del primero si es asi
    \param tokens Tokens a comparar
    \param x Coordenada x del rectangulo
    \param y Coordenada y del rectangulo
    \param w Anchura del rectangulo
    \param h Altura del rectangulo
    \return 1 Si ha habido colsion
    \return 0 Si no ha habido colsion
*/
int comp_tokens(Token tokens, double x, double y, double w, double h);

int all_completed(Token tokens);


#endif // __Tokens_H__
