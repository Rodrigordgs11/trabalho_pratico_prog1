#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "processos.h"
#include <windows.h>

//NAO REMOVE DIREITO PROCESSOS,

//2 QUEUES - 1 URGENTES 1 - NORMAIS - DEPOIS VAI PARA LISTA DUPLAMENTE EM PROCESSOS PROCESSADOS

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
    int admin, Login, menuA, menuC, res;

    lerUtilizador(&Lista);      //ler ficheiro utilizadores.dat
    lerProcessos(&NIniLista,&NFimLista, 0);     //ler ficheiro processo.dat, lista Normal
    lerProcessos(&UIniLista,&UFimLista, 1);     //ler ficheiro processo.dat, lista urgente
    lerProcessos(&RIniLista,&RFimLista, 3);     //ler ficheiro processo.dat, lista recusado
    lerProcessos(&PIniLista,&PFimLista, 2);     //ler ficheiro processo.dat, lista processado

    UserDefault(Lista, dados);      //utilizador default se ficheiro for NULL (se nao existir)

    Login = login(&Lista, &id);     //faz login e verifica se o nome e a pass é igual a algum id da lista e retorna 1 ou 2 ou -1
    if( Login == -1 ){
        printf("lOGIN FALHADO");
        exit(-5);
    }
    else if (Login  == 1 ){
        do{
            admin = 1;
            system("cls");
            menuA = MenuAdmin();
            switch (menuA){
                case 1:
                    system("cls");
                    switch (gestaoUtilizador(Lista)){
                        case 1:
                            dados = pedeDados(Lista);
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
                    switch (gestaoProcesso()){
                        case 1:
                            //inserir
                            dadosP = pedeDadosP(id,NIniLista,UIniLista, RIniLista,PIniLista);
                            if (dadosP.tipoProcesso == 0) {
                                if(tamanhoP(NIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP);
                                }else{
                                    InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                                }
                            }else if (dadosP.tipoProcesso == 1) {
                                if(tamanhoP(UIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP); //nao guarda direito
                                }else{
                                    InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                                }
                            }
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);
                            break;
                        case 2:
                            //remover
                            removelem(UIniLista, UFimLista, NIniLista, NFimLista, RIniLista, RFimLista);
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
                            executarProcesso(&PIniLista, &PFimLista, &UIniLista, &UFimLista, &NIniLista, &NFimLista, dadosP);
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);

                            break;
                        case 5:
                            imprimeElementosDaListaP(RIniLista, id, admin);
                            executarProcessoRejeitado(&RIniLista, &RFimLista, &UIniLista, &UFimLista, &NIniLista, &NFimLista, dadosP);
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);
                            break;
                        case 6:
                            pesquisarProcesso(NIniLista, RIniLista, UIniLista, PIniLista);
                            system("pause");
                            break;
                    }
                    break;
                case 3:
                    switch (menuEstatisticas()){
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
                    break;
            }
        } while (menuA!=0);
    }
    else if( Login == 2 ){
        printf("Convidado");
        //Processos
        do {
            admin = 0;
            menuC = menuConvidado();
            switch (menuC) {
                case 1:
                    switch (gestaoProcesso(admin)) {
                        case 1:
                            //inserir
                            dadosP = pedeDadosP(id,NIniLista,UIniLista, RIniLista,PIniLista);
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
                    break;
            }
        } while (menuC != 0);
    }
    printf("\nA fechar o programa..");
    sleep(1);
    return -5;
}