//
// Created by rodri on 15/05/2022.
//

#include <stdio.h>
#include <stdlib.h>
#ifndef TRABALHO_PRATICO_PROG1_PROCESSOS_H
#define TRABALHO_PRATICO_PROG1_PROCESSOS_H

typedef struct processo{
    int long ProcessID; /* número único*/
    int tipoProcesso; /* 1 - urgente , 0 - normal */
    char nomeUtilizador[50];
    char data[50]; /* o momento temporal em que o mesmo foi registado, temporal em que foi executado*/
    //struct tm created_at;
    //struct tm executed_at;
} INFO;

typedef struct ElemP {
    INFO info; //conteúdo do nó.
    struct ElemP *next; //apontador para o próximo nó
}PELEMENTO;



void imprimeElementosDaLista(PELEMENTO *iniLista);
int insertEndList(PELEMENTO **iniListU, INFO novoProcesso);
int removeInicioLista(PELEMENTO **iniLista);

#endif //TRABALHO_PRATICO_PROG1_PROCESSOS_H
