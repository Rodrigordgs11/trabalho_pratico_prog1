#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "processos.h"
#include <windows.h>


int main(){
    SetConsoleOutputCP(CP_UTF8); //carateres especiais

    UElemento *Lista = NULL;        //lista ligada utilizador
    PELEMENTO *NIniLista = NULL, *NFimLista = NULL;     //lista duplamente ligada processos Normais
    PELEMENTO *UIniLista = NULL, *UFimLista = NULL;     //lista duplamente ligada processos Urgentes
    PELEMENTO *PIniLista = NULL, *PFimLista = NULL;     //lista duplamente ligada processos Processados
    PELEMENTO *RIniLista = NULL, *RFimLista = NULL;     //lista duplamente ligada processos Recusados
    UTILIZADOR dados;   //estruturas de dados Utilizador
    PROCESSO dadosP;    //estruturas de dados Processos
    Estatisticas estatisticas;    //estrutura de dados estatisticas

    int id;     //variável id do utilizador
    int admin, Login, menuA, menuC;

    lerUtilizador(&Lista);      //ler ficheiro utilizadores.dat
    lerProcessos(&NIniLista,&NFimLista, 0);     //ler ficheiro processo.dat, lista Normal
    lerProcessos(&UIniLista,&UFimLista, 1);     //ler ficheiro processo.dat, lista urgente
    lerProcessos(&RIniLista,&RFimLista, 3);     //ler ficheiro processo.dat, lista recusado
    lerProcessos(&PIniLista,&PFimLista, 2);     //ler ficheiro processo.dat, lista processado

    lerEstatisticas(&estatisticas);

    FILE *fp = fopen("utilizadores.dat", "rb");  //utilizador default se ficheiro for NULL (se não existir)
    if (fp == NULL){
        printf("Dados Default\n");
        dados = pedeDados(Lista);
        dados.id = tamanhoLista(Lista) + 1;
        InserirFimLista(&Lista, dados);
        escreveFicheiroU(Lista);
    }

    Login = login(&Lista, &id);     // az login e verifica se o nome e a pass é igual a algum id da lista e retorna 1 ou 2 ou -1
    if( Login == -1 ){          //se o return da função login for -1 - login falhado
        printf("lOGIN FALHADO");
        exit(-5);
    }
    else if (Login  == 1 ){     //se o return da função login for 1 - login com sucesso
        do{
            admin = 1;      //variável admin, se for 1 é admin senão é convidado
            system("cls");
            menuA = MenuAdmin();
            switch (menuA){
                case 1:
                    system("cls");
                    switch (gestaoUtilizador(Lista)){
                        case 1:
                            dados = pedeDados(Lista);       //pede dados para inserir utilizador
                            InserirFimLista(&Lista, dados);     //insere na lista
                            escreveFicheiroU(Lista);        //escreve no ficheiro
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
                                    estatisticas.numeroTotalRejeitados++;
                                    gravaEstatisticas(&estatisticas);
                                }else{
                                    InserirInicioListaP(&NIniLista, &NFimLista, dadosP);
                                }
                            }else if (dadosP.tipoProcesso == 1) {
                                if(tamanhoP(UIniLista) >= 3){
                                    dadosP.tipoProcesso = 3;
                                    InserirInicioListaP(&RIniLista, &RFimLista, dadosP); //nao guarda direito
                                    estatisticas.numeroTotalRejeitados++;
                                    gravaEstatisticas(&estatisticas);
                                }else{
                                    InserirInicioListaP(&UIniLista, &UFimLista, dadosP);
                                }
                            }
                            escreveFicheiroP(NIniLista, UIniLista, RIniLista, PIniLista);
                            break;
                        case 2:
                            //remover
                            removelem(&UIniLista, &UFimLista, &NIniLista, &NFimLista, &RIniLista, &RFimLista);
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
                            executarProcesso(&estatisticas, &PIniLista, &PFimLista, &UIniLista, &UFimLista, &NIniLista, &NFimLista, dadosP);
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
                        case 7:
                            rankingProcessos(UIniLista, NIniLista);
                            system("pause");
                            break;
                    }
                    break;
                case 3:
                    switch (menuEstatisticas()){
                        case 1:
                            imprimeProcessosJaProcessados(estatisticas);
                            system("pause");
                            break;
                        case 2:
                            printf("Número de processos urgentes: %d\n", tamanhoP(UIniLista));
                            printf("Número de processos normais: %d\n", tamanhoP(NIniLista));
                            system("pause");
                            system("cls");
                            break;
                        case 3:
                            printf("Número de processos rejeitados: %d", estatisticas.numeroTotalRejeitados);
                            system("pause");
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