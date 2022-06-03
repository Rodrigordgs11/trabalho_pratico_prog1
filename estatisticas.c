//
// Created by rodri on 02/06/2022.
//

#include "estatisticas.h"

int lerEstatisticas(Estatisticas *estatisticas){
    FILE *fp = fopen("estatisticas.dat", "rb");
    fread(estatisticas,sizeof(Estatisticas),1, fp);
    fclose(fp);
    return 0;
}

void gravaEstatisticas(Estatisticas *estatisticas){
    FILE *fp = NULL;
    fp = fopen("estatisticas.dat","wb");
    fwrite(estatisticas, sizeof(Estatisticas), 1, fp);
    fclose(fp);
}

void imprimeProcessosJaProcessados(Estatisticas estatisticas){
    printf("Número de processos processados normais: %d\n", estatisticas.numerosProcessosProcessadosN);
    printf("Número de processos processados urgentes: %d\n", estatisticas.numerosProcessosProcessadosU);
}

