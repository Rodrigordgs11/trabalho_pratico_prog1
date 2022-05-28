#include <stdio.h>
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
            printf("Escolha a opção desejada: ");
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
        printf("3 - Estatisticas\n");
        printf("0 - Sair\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", &resMenuAdmin);
    }while(resMenuAdmin > 3 || resMenuAdmin < 0);
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

PROCESSO pedeDadosP(int id){
    time_t rawtime;
    time( &rawtime );
    PROCESSO dados;
    int tipoDeProcessoP;
    do{
        printf("Urgente(1) ou Normal(0): ");
        scanf("%d", &tipoDeProcessoP);
    } while ( tipoDeProcessoP > 1 || tipoDeProcessoP < 0 );
    dados.tipoProcesso = tipoDeProcessoP;
    dados.tempCriado = *localtime( &rawtime );
    dados.dono = id;
    printf("Nome: ");
    scanf("%s", &dados.nomeUtilizador);
    printf("Descrição: ");
    scanf("%s", &dados.descricao);
    return dados;
}

int main(){
    SetConsoleOutputCP(CP_UTF8); //carateres especiais

    UElemento *Lista = NULL;        //lista ligada utilizador
    PELEMENTO *NIniLista = NULL, *NFimLista = NULL;     //lista duplamente ligada processos Normais
    PELEMENTO *UIniLista = NULL, *UFimLista = NULL;     //lista duplamente ligada processos Urgentes
    PELEMENTO *PIniLista = NULL, *PFimLista = NULL;     //lista duplamente ligada processos Processados
    PELEMENTO *RIniLista = NULL, *RFimLista = NULL;     //lista duplamente ligada processos Recusados
    UTILIZADOR dados;   //estruturas de dados Utilizador
    PROCESSO dadosP;    //estruturas de dados Processos

    int id;     //variável id do utilizador
    int admin, tipoDeProcesso, tamLista = 0, Login;

    lerUtilizador(&Lista);      //ler ficheiro utilizadores.dat
    lerProcessos(&NIniLista,&NFimLista, 0);     //ler ficheiro processo.dat, lista Normal
    lerProcessos(&PIniLista,&PFimLista, 2);     //ler ficheiro processo.dat, lista processado
    lerProcessos(&UIniLista,&UFimLista, 1);     //ler ficheiro processo.dat, lista urgente
    lerProcessos(&RIniLista,&RFimLista, 3);     //ler ficheiro processo.dat, lista recusado

    FILE *fp = fopen("utilizadores.dat", "rb");
    if (fp == NULL){
        dados = pedeDados();
        dados.id = tamanhoLista(Lista) + 1;
        InserirFimLista(&Lista, dados);
        escreveFicheiroU(Lista);
    }

    Login = login(&Lista, &id);
    if( Login == -1 ){
        printf("lOGIN FALHADO");
        exit(-5);
    }
    else if (Login  == 1 ){
        do{
            admin = 1;
            system("cls");
            switch (MenuAdmin()){
                case 1:
                    system("cls");
                    switch (gestaoUtilizador()){
                        case 1:
                            dados = pedeDados();
                            dados.id = tamanhoLista(Lista) + 1;
                            InserirFimLista(&Lista, dados);
                            escreveFicheiroU(Lista);
                        break;
                        case 2:
                            //remover user
                        break;
                        case 3:
                            imprimeListaU(Lista);
                            system("pause");
                        break;
                        case 4:
                            alterarUser(Lista, dados);
                        break;
                    }
                break;
                case 2:
                    switch (gestaoProcesso()) {
                        case 1:
                            //inserir
                            dadosP = pedeDadosP(id);
                            tamLista = tamanhoP(NIniLista) + tamanhoP(RIniLista) +
                                       tamanhoP(UIniLista) + tamanhoP(PIniLista);
                            dadosP.ProcessID = tamLista + 1;
                            if (dadosP.tipoProcesso == 0) {
                                if(tamanhoP(NIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP);
                                }else{
                                    InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                                }
                            } else if (dadosP.tipoProcesso == 1) {
                                if(tamanhoP(UIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP); //nao guarda direito
                                }else{
                                    InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                                }
                            }
                            escreveFicheiroP(NIniLista, PIniLista, UIniLista, RIniLista);
                            break;
                        case 2:
                            //remover
                            break;
                        case 3:
                            //imprimir
                            system("cls");
                            printf("** PROCESSOS INSERIDOS **\n");
                            printf("\n** Lista Urgente **\n");
                            imprimeElementosDaListaP(UIniLista, id, admin);
                            printf("** Lista Normal **\n");
                            imprimeElementosDaListaP(NIniLista, id, admin);
                            printf("** Lista Processados **\n");
                            imprimeElementosDaListaP(PIniLista, id, admin);
                            printf("** Lista Recusados **\n");
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            system("pause");
                        break;
                        case 4:
                            //executar - remover no fim e inserir
                        break;
                    }
                case 3:
                    switch (menuEstatisticas()) {
                        case 1:
                            printf("Número de processos urgentes: %d\n", tamanhoP(UIniLista));
                            printf("Número de processos normais: %d\n", tamanhoP(NIniLista));
                            printf("Número de processos processados: %d\n", tamanhoP(PIniLista));
                            printf("Número de processos recusados: %d\n", tamanhoP(RIniLista));
                            system("pause");
                            system("cls");
                        break;
                        case 6:
                            numAtualProcessos(UIniLista, NIniLista, Lista);
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
                            dadosP = pedeDadosP(id);
                            tamLista = tamanhoP(NIniLista) + tamanhoP(RIniLista) +
                                       tamanhoP(UIniLista) + tamanhoP(PIniLista);
                            dadosP.ProcessID = tamLista + 1;
                            if (dadosP.tipoProcesso == 0) {
                                if(tamanhoP(NIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP);
                                }else{
                                    InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                                }
                            } else if (dadosP.tipoProcesso == 1) {
                                if(tamanhoP(UIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP); //nao guarda direito
                                }else{
                                    InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                                }
                            }
                            escreveFicheiroP(NIniLista, PIniLista, UIniLista, RIniLista);
                        break;
                        case 2:
                            //remover
                        break;
                        case 3:
                            //imprimir
                            system("cls");
                            printf("** PROCESSOS INSERIDOS **\n");
                            printf("\n** Lista Urgente **\n");
                            imprimeElementosDaListaP(UIniLista, id, admin);
                            printf("** Lista Normal **\n");
                            imprimeElementosDaListaP(NIniLista, id, admin);
                            printf("** Lista Processados **\n");
                            imprimeElementosDaListaP(PIniLista, id, admin);
                            printf("** Lista Recusados **\n");
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            system("pause");
                        break;
                    }
                    break;
                case 2:
                    //perfil
                    perfilUser(Lista, dados, id);
                break;
                case 3:

                break;
                case 0:
                    system("cls");
                    printf("\nA fechar o programa..");
                    sleep(1);
                    break;
            }
        } while (menuConvidado() != 0);
    }
    printf("\nA fechar o programa..");
    sleep(1);
    return -5;
}