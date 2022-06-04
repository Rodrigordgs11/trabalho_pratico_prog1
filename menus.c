//
// Created by rodri on 04/06/2022.
//

#include "menus.h"

int menuEstatisticas(){
    int resmenuEstatisticas;
    do{
        system("cls");
        printf("** Estatísticas **\n");
        printf("1 - Número de processos processados de cada lista\n");
        printf("2 - Número de processos em espera em cada uma das lista\n");
        printf("3 - Número total de processos rejeitados\n");
        printf("4 - Processo que mais tempo e menos tempo demorou a ser executado\n");
        printf("5 - Tempo médio de espera dos processos de cada uma das listas de espera\n");
        printf("6 - Número atual de processos normais e urgentes de um determinado utilizador\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resmenuEstatisticas);
    }while (resmenuEstatisticas > 6 || resmenuEstatisticas < 0);
    return resmenuEstatisticas;
}

int gestaoProcesso(){
    int resProcesso;
    do {
        system("cls");
        printf("** GESTÃO DE PROCESSOS **\n");
        printf("1 - Inserir Processo\n");
        printf("2 - Remover Processo\n");
        printf("3 - Imprimir os meus Processos\n");
        printf("4 - Executar Processo\n");
        printf("5 - Executar Processo Rejeitado\n");
        printf("6 - Pesquisar Processo\n");
        printf("7 - Ranking de processos por tempo de espera\n");
        printf("8 - Criar relatório de processos ordenados por nome\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resProcesso);
    } while (resProcesso > 8 || resProcesso < 0);
    return resProcesso;
}

int MenuAdmin(){
    int resMenuAdmin = 0;
    do {
        printf("\n");
        printf("1 - Utilizadores\n");
        printf("2 - Processos\n");
        printf("3 - Estatísticas\n");
        printf("0 - Sair\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", &resMenuAdmin);
    }while(resMenuAdmin > 3 || resMenuAdmin < 0);
    return resMenuAdmin;
}

int gestaoUtilizador(){
    int resUtilizador;
    do {
        system("cls");
        printf("GESTÃO DE UTILIZADORES\n");
        printf("1 - Inserir Utilizador\n");
        printf("2 - Remover Utilizador\n");
        printf("3 - Imprimir Utilizador\n");
        printf("4 - Editar Utilizador\n");
        printf("0 - Sair\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", &resUtilizador);
    } while (resUtilizador > 4 || resUtilizador < 0);
    return resUtilizador;
}

int gestaoProcessoU(){
    int resProcessoU;
    do {
        system("cls");
        printf("** GESTÃO DE PROCESSOS **\n");
        printf("1 - Inserir Processo\n");
        printf("2 - Imprimir os meus Processos\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resProcessoU);
    } while (resProcessoU > 2 || resProcessoU < 0);
    return resProcessoU;
}

int menuConvidado(){
    int resConvidado;
    do {
        system("cls");
        printf("*** MENU CONVIDADOS ***\n");
        printf("1 - Processos\n");
        printf("2 - Perfil\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resConvidado);
    } while (resConvidado > 2 || resConvidado < 0);
    return resConvidado;
}