//
// Created by rodri on 23/05/2022.
//

#include "user.h"

int verificaLogin(UElemento *iniListaU, int *id, char nome[50], char pp[50]){
    UElemento *utilizadores = NULL;
    for(utilizadores = iniListaU; utilizadores != NULL; utilizadores=utilizadores->next){
        if( (strcmp(utilizadores->info.nomeUtilizador, nome) == 0) && (strcmp(utilizadores->info.pp, pp) == 0)  && utilizadores->info.tipoDeUtilizador == 1){
            *id = utilizadores->info.id;
            return 1;
        }
        if((strcmp(utilizadores->info.nomeUtilizador, nome) == 0) && (strcmp(utilizadores->info.pp, pp) == 0)  && utilizadores->info.tipoDeUtilizador == 0){
            *id = utilizadores->info.id;
            return 2;
        }
    }
    return -1;
}

int login(UElemento **iniListaU, int *id){
    printf("\n** LOGIN **\n\n");
    char nome[50];
    char pp[50];
    printf("Introduza o nome: ");
    scanf("%s", &nome);
    printf("Introduza a pp: ");
    scanf("%s", &pp);
    int verifica = verificaLogin(*iniListaU, id, nome, pp);
    if (verifica == -1) {
        printf("Login falhado");
        sleep(3);
    }
    if (verifica == 1) {
        printf("login com sucesso - admin");
        sleep(3);
    }
    if (verifica == 2) {
        printf("login com sucesso - Convidado");
        sleep(3);
    }
    return verifica;
}

int InserirFimLista(UElemento **iniListaU, UTILIZADOR novoUtilizador){
    UElemento *novo = NULL, *aux=NULL;
    novo = (UElemento *) calloc(1, sizeof(UTILIZADOR));
    if(novo == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    novo->info = novoUtilizador;
    novo->next = NULL;
    if(*iniListaU == NULL) *iniListaU = novo;
    else{
        aux =*iniListaU;
        while(aux->next != NULL) aux=aux->next;
        aux->next=novo;
    }
    return 0;
}

int lerUtilizador(UElemento **iniListaU){
    UTILIZADOR auxU;
    FILE *fp = fopen("utilizadores.dat", "rb");
    while (fread(&auxU, sizeof(UTILIZADOR), 1, fp)) {
        InserirFimLista(iniListaU, auxU);
    }
    fclose(fp);
    return 0;
}

int tamanhoLista(UElemento *iniListaU){
    UElemento *aux1=NULL;
    int totElem=0;
    aux1 = iniListaU;
    while(aux1!= NULL){
        totElem++;
        aux1 = aux1->next;
    }
    return totElem;
}

int escreveFicheiroU(UElemento *iniListaU){
    FILE *fp = NULL;
    UElemento *aux = iniListaU;
    fp = fopen("utilizadores.dat", "wb");
    if (fp == NULL) {
        printf("Erro a abrir o ficheiro \n");
        return -1;
    }
    while(aux!=NULL){
        fwrite(&aux->info, sizeof(UTILIZADOR), 1, fp);
        aux=aux->next;
    }
    fclose(fp);
    return 0;
}

void imprimeListaU(UElemento *iniListaU) {
    UElemento *aux=NULL;
    if (iniListaU==NULL){
        printf("lista vazia\n");
        return;
    }
    for (aux=iniListaU; aux!=NULL ;aux = aux->next){
        printf ("\nId: %d - Nome: %s - Palavra Passe: %s - Tipo de User: %d\n",  aux->info.id, aux->info.nomeUtilizador,
                aux->info.pp, aux->info.tipoDeUtilizador);
    }
}

//admin

void alterarUser(UElemento *iniListaU, UTILIZADOR dados){
    UElemento *aux=NULL;
    int id, flag = 0, resEditUser;
    imprimeListaU(iniListaU);
    printf("Introduza o id do utilizador que pretende alterar");
    scanf("%d", &id);
    printf("\n ... A procurar ...\n");
    sleep(2);
    for (aux=iniListaU; aux!=NULL ;aux = aux->next) {
        if (id == aux->info.id){
            flag = 1;
            printf("\n Utilizador Encontrado --- [ %d ]", aux->info.id);
            printf("\n 1) Nome: %s",aux->info.nomeUtilizador );
            printf("\n 2) Palavra Passe: %s", aux->info.pp);
            printf("\n 3) Tipo de utilizador: %d", aux->info.tipoDeUtilizador);
        }
    }
    if (flag == 1 ){
        printf("\nEscolha o campo a alterar (1 - 8): ");
        scanf("%d", &resEditUser);
        system("cls");
        switch(resEditUser){
            case 1 :
                printf("\nNome: ");
                scanf("%s", &dados.nomeUtilizador);
                system("cls");
                break;
            case 2 :
                printf("\nPalavra Passe: ");
                scanf("%s", dados.pp);
                system("cls");
                break;
            case 3:
                printf("\nTipo de Utilizador - Administrador(1) ou Convidado(0): ");
                scanf("%d", dados.tipoDeUtilizador);
                system("cls");
                break;
        }
    }else{
        printf("\n -- Utilizador Não Encontrado --");}
}

//convidado
void perfilUser(UElemento *iniListaU, UTILIZADOR dados, int id){
    int flag, resEditUser;
    UElemento *aux = NULL;
    for (aux=iniListaU; aux!=NULL ;aux = aux->next) {
        if (id == aux->info.id){
            printf("\n Utilizador --- [ %d ]", aux->info.id);
            printf("\n 1) Nome: %s", aux->info.nomeUtilizador );
            printf("\n 2) Palavra Passe: %s", aux->info.pp);
            printf("\n 3) Tipo de utilizador: %d", aux->info.tipoDeUtilizador);
        }
    }
    printf("\nPretende alterar dados? Sim(1) ou Não(0)");
    scanf("%d", &flag);
    if (flag == 1){
        printf("\nEscolha o campo a alterar (1 - 8): ");
        scanf("%d", &resEditUser);
        system("cls");
        switch(resEditUser){
            case 1 :
                printf("\nNome: ");
                scanf("%s", &dados.nomeUtilizador);
                system("cls");
                break;
            case 2 :
                printf("\nPalavra Passe: ");
                scanf("%s", &dados.pp);
                system("cls");
                break;
            case 3:
                printf("\nTipo de Utilizador - Administrador(1) ou Convidado(0): ");
                scanf("%d", &dados.tipoDeUtilizador);
                system("cls");
                break;
        }
    }
}

/* MENUS */