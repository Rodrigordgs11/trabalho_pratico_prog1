#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "processos.h"
#include <windows.h>


//2 QUEUES - 1 URGENTES 1 - NORMAIS - DEPOIS VAI PARA LISTA DUPLAMENTE EM PROCESSOS PROCESSADOS

int gestaoUtilizador(){
    int resUtilizador;
    do {
        system("cls");
        printf("GESTAO DE UTILIZADORES\n");
        printf("1 - Inserir Utilizador\n");
        printf("2 - Remover Utilizador\n");
        printf("3 - Imprimir Utilizador\n");
        printf("4 - Editar Utilizador\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resUtilizador);
    } while (resUtilizador > 4 || resUtilizador < 0);
    return resUtilizador;
}

int MenuAdmin(){
    int resMenuAdmin = 0;
    do {
        printf("\n");
        printf("1 - Utilizadores\n");
        printf("2 - Processos\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resMenuAdmin);
    }while(resMenuAdmin > 2 || resMenuAdmin < 0);
    return resMenuAdmin;
}

UTILIZADOR pedeDados(){
    UTILIZADOR dados;
    int tipo;
    printf("Introduza o seu nome: ");
    scanf("%s", &dados.nomeUtilizador);
    printf("Introduza a password: ");
    scanf("%s", &dados.pp);
    do {
        printf("Administrador(1) ou Utilizador(0)");
        scanf("%d", &dados.tipoDeUtilizador);
        tipo = dados.tipoDeUtilizador;
    } while (tipo > 1 || tipo < 0);
    return dados;
}

PROCESSO pedeDadosP(){
    PROCESSO dados;
    int tipoDeProcessoP;
    do{
        printf("Urgente(1) ou Normal(0): ");
        scanf("%d", &tipoDeProcessoP);
    } while ( tipoDeProcessoP > 1 || tipoDeProcessoP < 0 );
    dados.tipoProcesso = tipoDeProcessoP;
    printf("Nome: ");
    scanf("%s", &dados.nomeUtilizador);
    printf("Descrição: ");
    scanf("%s", &dados.descricao);
    return dados;
}

int main(){
    SetConsoleOutputCP(CP_UTF8); //carateres especiais

    UElemento *Lista = NULL;
    PELEMENTO *NIniLista = NULL, *NFimLista = NULL;
    PELEMENTO *UIniLista = NULL, *UFimLista = NULL;
    PELEMENTO *PIniLista = NULL, *PFimLista = NULL;
    PELEMENTO *RIniLista = NULL, *RFimLista = NULL;
    UTILIZADOR dados;
    PROCESSO dadosP;

    int *id = NULL;
    int admin, tipoDeProcesso, tamLista = 0, Login;

    lerUtilizador(&Lista);
    lerProcessos(&NIniLista,&NFimLista, 0);
    lerProcessos(&PIniLista,&PFimLista, 2);
    lerProcessos(&UIniLista,&UFimLista, 1);
    lerProcessos(&RIniLista,&RFimLista, 3);

    FILE *fp = fopen("utilizadores.dat", "rb");
    if (fp == NULL){
        dados = pedeDados();
        dados.id = tamanhoLista(Lista) + 1;
        InserirFimLista(&Lista, dados);
    }

    Login = login(&Lista, (int *) &id);
    if( Login == -1 ){
        printf("lOGIN FALHADO");
        exit(-5);
    }
    else if (Login  == 1 ){
        do{
            admin = 1;
            switch (MenuAdmin()){
                case 1:
                    system("cls");
                    switch (gestaoUtilizador()){
                        case 1:
                            dados = pedeDados();
                            dados.id = tamanhoLista(Lista) + 1;
                            InserirFimLista(&Lista, dados);
                            break;
                        case 2:
                            //remover user
                            break;
                        case 3:
                            imprimeListaU(Lista);
                            break;
                        case 4:
                            alterarUser(Lista, dados);
                            break;
                    }
                    break;
                case 2:
                    switch (gestaoProcesso(admin)) {
                        case 1:
                            //inserir
                            dadosP = pedeDadosP();
                            tamLista = tamanhoP(NIniLista) + tamanhoP(RIniLista) +
                                       tamanhoP(UIniLista) + tamanhoP(PIniLista);
                            dadosP.ProcessID = tamLista + 1;
                            if (dadosP.tipoProcesso == 0) {
                                InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                            } else if (dadosP.tipoProcesso == 1) {
                                InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                            }
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);
                            break;
                        case 2:
                            //remover
                            break;
                        case 3:
                            //imprimir
                            system("cls");
                            printf("** PROCESSOS INSERIDOS **\n");
                            printf("\n** Lista Urgente **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(UIniLista, id, admin);
                            printf("** Lista Normal **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(NIniLista, id, admin);
                            printf("** Lista Processados **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(PIniLista, id, admin);
                            printf("** Lista Recusados **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            system("pause");
                            break;
                        case 4:
                            //imprimir
                            system("cls");
                            printf("** PROCESSOS INSERIDOS **\n");
                            printf("\n** Lista Urgente **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(UIniLista, id, admin);
                            printf("** Lista Normal **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(NIniLista, id, admin);
                            printf("** Lista Processados **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(PIniLista, id, admin);
                            printf("** Lista Recusados **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            system("pause");
                            break;
                    }
                    break;
                case 0:
                    system("cls");
                    printf("\nA fechar o programa..");
                    sleep(1);
                    break;
            }
        } while (MenuAdmin()!=0);
    }
    else if( Login == 2 ){
        printf("Convidado");
        //Processos
        do {
            admin = 0;
            switch (menuConvidado()) {
                case 1:
                    switch (gestaoProcesso(admin)) {
                        case 1:
                            //inserir
                            dadosP = pedeDadosP();
                            tamLista = tamanhoP(NIniLista) + tamanhoP(RIniLista) +
                                       tamanhoP(UIniLista) + tamanhoP(PIniLista);
                            dadosP.ProcessID = tamLista + 1;
                            if (dadosP.tipoProcesso == 0) {
                                InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                            } else if (dadosP.tipoProcesso == 1) {
                                InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                            }
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);
                            break;
                        case 2:
                            //remover
                            break;
                        case 3:
                            //imprimir
                            system("cls");
                            printf("** PROCESSOS INSERIDOS **\n");
                            printf("\n** Lista Urgente **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(UIniLista, id, admin);
                            printf("** Lista Normal **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(NIniLista, id, admin);
                            printf("** Lista Processados **\n");
                            if (UIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(PIniLista, id, admin);
                            printf("** Lista Recusados **\n");
                            if (NIniLista == NULL) {
                                printf("Lista vazia\n");
                            }
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            system("pause");
                            break;
                    }
                    break;
                case 2:
                    //perfil
                    perfilUser(Lista, dados, id);
                    break;
                case 0:
                    system("cls");
                    printf("\nA fechar o programa..");
                    sleep(1);
                    break;
            }
        } while (menuConvidado() != 0);
    }
    escreveFicheiroU(Lista);
    printf("\nA fechar o programa..");
    sleep(1);
    return -5;
}