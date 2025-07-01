#include <stdio.h>
#include <stdlib.h>
#include "Tokens.h"

struct TokenContentStr
{
    int x;
    int y;
    int h;
    int w;
    Estado_token estado;
};

struct TokenStr
{
    int n_tokens;
    int max_tokens;
    int frame;
    struct TokenContentStr * tokens;
};

typedef struct TokenStr * Token;


Token crea_tokens(int n_tokens_maximo)
{
    if(n_tokens_maximo < 0)
    {
        printf("El numero de tokens no esta permitido");
        return NULL;
    }


    Token nuevo = malloc(sizeof(struct TokenStr));
    nuevo->n_tokens= 0;
    nuevo->frame = 0;
    nuevo->max_tokens= n_tokens_maximo;
    nuevo->tokens = NULL;
    if(n_tokens_maximo != 0) nuevo->tokens = malloc(n_tokens_maximo*sizeof(struct TokenContentStr));
    return nuevo;
}

void libera_tokens(Token tokens)
{
    if(tokens->tokens != NULL) free(tokens->tokens);
    free(tokens);
}

void inserta_token(Token tokens, int x, int y, int w, int h, Estado_token estado)
{
    if(tokens->n_tokens == tokens->max_tokens) return;
    tokens->tokens[tokens->n_tokens].x=x;
    tokens->tokens[tokens->n_tokens].y=y;
    tokens->tokens[tokens->n_tokens].w=w;
    tokens->tokens[tokens->n_tokens].h=h;
    tokens->tokens[tokens->n_tokens].estado=estado;
    tokens->n_tokens = tokens->n_tokens + 1;
}


void dibuja_tokens(Token tokens, Animacion anima)
{
    for(int i=0; i < tokens->n_tokens; i++)
    {
        if(tokens->tokens[i].estado == ACTIVO) dibuja_animacion(tokens->frame,anima,tokens->tokens[i].x,tokens->tokens[i].y,tokens->tokens[i].w,tokens->tokens[i].h,0,SDL_FLIP_NONE);
    }
    tokens->frame = tokens->frame + 1;
    tokens->frame = tokens->frame % 65536;
}

void activa_tokens(Token tokens)
{
    for(int i=0; i< tokens->n_tokens; i++)
    {
        if(tokens->tokens[i].estado == DESACTIVO) tokens->tokens[i].estado = 1;
    }
}

int comp_tokens(Token tokens, double x, double y, double w, double h)
{
    for(int i=0; i< tokens->n_tokens; i++)
    {
        if(tokens->tokens[i].estado == ACTIVO)
        {
            if(solape_rectangulos(tokens->tokens[i].x,tokens->tokens[i].y,tokens->tokens[i].w,tokens->tokens[i].h,x,y,w,h))
            {
                tokens->tokens[i].estado = OBTENIDO;
                return 1;
            }
        }
    }
    return 0;
}

int all_completed(Token tokens)
{
    for(int i=0; i< tokens->n_tokens; i++)
    {
        if(tokens->tokens[i].estado != OBTENIDO) return 0;
    }
    return 1;
}
