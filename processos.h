//
// Created by rodri on 15/05/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef TRABALHO_PRATICO_PROG1_PROCESSOS_H
#define TRABALHO_PRATICO_PROG1_PROCESSOS_H

typedef struct processo{
    int long ProcessID; /* número único*/
    int tipoProcesso; /* 0 - normal, 1 - Urgente, 2 - processado, 3 - recusado */
    char nomeUtilizador[50];
    char descricao[50];
    int dono;
    struct tm *tempCriado; /* o momento temporal em que o mesmo foi registado */
    struct tm *tempExecutado; /* temporal em que foi executado*/
} PROCESSO;

typedef struct ElemP {
    PROCESSO info; //conteúdo do nó.
    struct ElemP *next; //apontador para o próximo nó
    struct ElemP *before; //apontador para o próximo nó
}PELEMENTO;

void imprimeElementosDaListaP(PELEMENTO *iniListaP, int *id, int admin);
int removeInicioListaP(PELEMENTO **iniListaP);
int InserirFimListaP (PELEMENTO **iniLista, PELEMENTO **fimLista, PROCESSO newInfo);
int InserirInicioListaP (PELEMENTO **iniLista, PELEMENTO **fimLista,PROCESSO newInfo);
int lerProcessos(PELEMENTO **IniLista, PELEMENTO **FimLista, int tipoDeProcesso);
int escreveFicheiroP(PELEMENTO *iniListaN, PELEMENTO *iniListaU, PELEMENTO *iniListaR, PELEMENTO *iniListaP);
int tamanhoP(PELEMENTO *iniListaP);

int gestaoProcesso(int admin);
int menuConvidado();

#endif //TRABALHO_PRATICO_PROG1_PROCESSOS_H
