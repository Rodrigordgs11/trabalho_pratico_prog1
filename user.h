//
// Created by rodri on 23/05/2022.
//

#ifndef UNTITLED4_USER_H
#define UNTITLED4_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct utilizador{
    int id;
    int tipoDeUtilizador;  /* 1 - admin, 0 - convidado */
    char nomeUtilizador[50];
    char pp[50];
} UTILIZADOR;

typedef struct ElemU {
    UTILIZADOR info; //conteúdo do nó.
    struct ElemU *next; //apontador para o próximo nó
} UElemento;

UTILIZADOR pedeDados(UElemento *ListaU);
void UserDefault(UElemento *Lista, UTILIZADOR dados);
int login(UElemento **iniListaU, int *id);
int InserirFimLista(UElemento **iniListaU, UTILIZADOR novoUtilizador);
int lerUtilizador(UElemento **iniListaU);
int tamanhoLista(UElemento *iniListaU);
int escreveFicheiroU(UElemento *iniListaU);
void imprimeListaU(UElemento *iniListaU);
void alterarUser(UElemento *iniListaU, UTILIZADOR dados);
void perfilUser(UElemento *iniListaU, UTILIZADOR dados, int id);

int MenuAdmin();
int gestaoUtilizador();
int gestaoProcessoU();

#endif //UNTITLED4_USER_H
