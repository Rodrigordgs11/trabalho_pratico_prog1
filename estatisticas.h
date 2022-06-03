//
// Created by rodri on 02/06/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct estatisticas{
    int numerosProcessosProcessadosU;
    int numerosProcessosProcessadosN;
    int numeroTotalRejeitados;
}Estatisticas;


#ifndef UNTITLED4_ESTATISTICAS_H
#define UNTITLED4_ESTATISTICAS_H

int lerEstatisticas(Estatisticas *estatisticas);
void gravaEstatisticas(Estatisticas *estatisticas);
void imprimeProcessosJaProcessados(Estatisticas estatisticas);

#endif //UNTITLED4_ESTATISTICAS_H
