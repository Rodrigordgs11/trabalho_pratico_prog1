//
// Created by rodri on 15/05/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef TRABALHO_PRATICO_PROG1_USER_H
#define TRABALHO_PRATICO_PROG1_USER_H

typedef struct utilizador{
    int tipoDeUtilizador;  /* 1 - admin, 0 - convidado */
    char nomeUtilizador[50];
    char pp[50];
} UTILIZADOR;

typedef struct ElemU {
    UTILIZADOR info; //conteúdo do nó.
    struct ElemU *next; //apontador para o próximo nó
}UElemento;

void imprimeElementosDaLista(UElemento *iniLista);
int insertEndList(UElemento **iniListU, UTILIZADOR newUser);
int removeInicioLista(UElemento **iniLista);

#endif //TRABALHO_PRATICO_PROG1_USER_H
