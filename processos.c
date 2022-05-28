//
// Created by rodri on 24/05/2022.
//

#include "processos.h"

/*
  time_t rawtime;
  time(&rawtime);*/

/* LISTAS */

//DUPLAMENTE LIGADAS


int lerProcessos(PELEMENTO **IniLista, PELEMENTO **FimLista, int tipoDeProcesso){
    PROCESSO processo;
    FILE *fp = fopen("processo.dat", "rb");
    while (fread(&processo,sizeof(PROCESSO),1, fp)){
        if(processo.tipoProcesso == tipoDeProcesso){
            InserirInicioListaP(IniLista, FimLista, processo);
        }
    }
    fclose(fp);
    return 0;
}

int escreveFicheiroP(PELEMENTO *iniListaN, PELEMENTO *iniListaU, PELEMENTO *iniListaR, PELEMENTO *iniListaP){
    FILE *fp = NULL;
    PELEMENTO *aux = iniListaN;
    PELEMENTO *aux2 = iniListaU;
    PELEMENTO *aux3 = iniListaR;
    PELEMENTO *aux4 = iniListaP;
    PROCESSO processo;
    fp = fopen("processo.dat", "wb");
    if (fp == NULL) {
        printf("Erro a abrir o ficheiro \n");
        return -1;
    }
    while(aux!=NULL){fwrite(&aux->info, sizeof(PROCESSO), 1, fp); aux=aux->next;}
    while(aux2!=NULL){ fwrite(&aux2->info, sizeof(PROCESSO), 1, fp); aux2=aux2->next;}
    while(aux3!=NULL){ fwrite(&aux3->info, sizeof(PROCESSO), 1, fp); aux3=aux3->next;}
    while(aux4!=NULL){ fwrite(&aux4->info, sizeof(PROCESSO), 1, fp); aux4=aux4->next;}
    fclose(fp);
    return 0;
}

// queues
int InserirInicioListaP (PELEMENTO **iniLista, PELEMENTO **fimLista,PROCESSO newInfo){
    PELEMENTO *novo=NULL;
    novo=(PELEMENTO *)malloc(sizeof(PELEMENTO));
    if (novo==NULL) {
        printf("Out of memory\n"); return -1;
    }
    novo->info = newInfo;
    novo->before= NULL;
    novo->next= NULL;
    if (*iniLista==NULL) {
        *iniLista=novo;
        *fimLista=novo;
    }
    else {
        novo->next = *iniLista;
        (*iniLista)->before=novo;
        *iniLista=novo;
    }
    return 0;
}


// lista processos processados
int InserirFimListaP (PELEMENTO **iniLista, PELEMENTO **fimLista, PROCESSO newInfo){
    PELEMENTO *novo=NULL;
    novo=(PELEMENTO *)malloc(sizeof(PELEMENTO));
    if (novo==NULL) {
        printf("Out of memory\n"); return -1;
    }
    novo->info = newInfo;
    novo->before= NULL;
    novo->next= NULL;
    if (*fimLista==NULL) {
        *iniLista=novo;
        *fimLista=novo;
    }
    else {
        novo->before=*fimLista;
        (*fimLista)->next=novo;
        *fimLista=novo;
    }
    return 0;
}

void ListarInicio(PELEMENTO *iniLista){
    PELEMENTO *aux=iniLista;
    while (aux!=NULL) {
        printf("%d, %s\n", aux->info.ProcessID, aux->info.nomeUtilizador);
        aux = aux->next;
    }
}
void ListarFim (PELEMENTO *fimLista){
    PELEMENTO *aux=fimLista;
    while (aux!=NULL) {
        printf("%d, %s\n", aux->info.ProcessID, aux->info.nomeUtilizador);
        aux = aux->before;
    }
}

int removeElem(PELEMENTO **iniLista, PELEMENTO **fimLista, int num) {
    PELEMENTO *aux=*iniLista;

    while(aux!=NULL && aux->info.ProcessID != num) {
        aux = aux ->next;
    }
    if (aux ==NULL) return -1; // não existe elemento num ou a lista é vazia
    if (aux->before == NULL) { // vai remover o 1º elemento
        *iniLista= aux ->next;
        if (*iniLista!= NULL) {(*iniLista)->before=NULL;}
    }
    else {aux->before->next = aux->next; }
    if (aux->next == NULL) { // vai remover o ultimo elemento
        *fimLista= aux ->before;
        if (*fimLista!=NULL) {(*fimLista)->next=NULL;}
    }
    else {aux->next->before = aux->before;}
    free(aux); return 0;
}


int tamanhoP(PELEMENTO *iniListaP){
    PELEMENTO *aux1=NULL;
    int totElem=0;
    aux1 = iniListaP;
    while(aux1!= NULL){
        totElem++;
        aux1 = aux1->next;
    }
    return totElem;
}

void imprimeElementosDaListaP(PELEMENTO *iniListaP, int *id, int admin){
    PELEMENTO *aux= iniListaP;
    while (aux!=NULL) {
        if(admin == 0 && *id == aux->info.dono){
            printf("PID: %d, Nome: %s,Descrição: %s\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.descricao);
            aux = aux->next;
        }else if(admin == 1){
            printf("PID: %d, Nome: %s,Descrição: %s\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.descricao);
            aux = aux->next;
        }
    }
}

/* MENUS */

int menuConvidado(){
    int resConvidado;
    do {
        system("cls");
        printf("*** MENU CONVIDADOS ***\n");
        printf("1 - Processos\n");
        printf("2 - Perfil\n");
        printf("3 - Estatísticas\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resConvidado);
    } while (resConvidado > 3 || resConvidado < 0);
    return resConvidado;
}

int gestaoProcesso(int admin){
    int resProcesso;
    do {
        system("cls");
        printf("GESTÃO DE PROCESSOS\n");
        printf("1 - Inserir Processo\n");
        printf("2 - Remover Processo\n");
        printf("3 - Imprimir os meus Processos\n");
        if(admin == 1) printf("4 - Ver todos os Processos");
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resProcesso);
    } while (resProcesso > 4 || resProcesso < 0);
    return resProcesso;
}