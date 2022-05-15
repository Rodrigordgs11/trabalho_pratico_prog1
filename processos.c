//
// Created by rodri on 15/05/2022.
//

#include "processos.h"



/* LISTAS */

void imprimeElementosDaLista(PELEMENTO *iniLista) {
    PELEMENTO *aux=NULL;
    if (iniLista==NULL) {printf ("lista vazia\n");}
    else {
        aux = iniLista;
        while (aux!=NULL){
            printf ("%d - %s", aux->info.ProcessID,
                    aux->info.nomeUtilizador);
            aux = aux->next;
        }
    }
}


int insertEndList(PELEMENTO **iniListU, INFO novoProcesso){
    PELEMENTO *new = NULL, *aux=NULL;
    new = (PELEMENTO *) calloc(1, sizeof(INFO));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = novoProcesso;
    new->next = NULL;
    if(*iniListU == NULL) *iniListU = new;
    else{
        aux =*iniListU;
        while(aux->next != NULL) aux=aux->next;
        aux->next=new;
    }
    return 0;
}

int removeInicioLista(PELEMENTO **iniLista){
    PELEMENTO *aux=NULL;
    if (*iniLista == NULL) {
        printf ("Lista vazia\n");
        return -1;
    }
    aux=*iniLista;
    *iniLista=aux->next;
    free(aux);
    return 0;
}

int getSizeIt(PELEMENTO *iniLista){
    PELEMENTO *aux1=NULL;
    int totElem=0;
    aux1 = iniLista;
    while(aux1!= NULL){
        totElem++;
        aux1 = aux1->next;
    }
    return totElem;
}




/*
        //DUPLAMENTE LIGADAS
int InserirInicioLista (ELEMENTO **iniLista, ELEMENTO **fimLista,INFO newInfo){
    ELEMENTO *novo=NULL;
    novo=(ELEMENTO *)malloc(sizeof(ELEMENTO));
    if (novo==NULL) {
        printf(“Out of memory\n”); return -1;
    }
    novo->node = newInfo;
    novo->anterior= NULL;
    novo->proximo= NULL;
    if (*iniLista==NULL) {
        *iniLista=novo;
        *fimLista=novo;
    }
    else {
        novo->proximo = *iniLista;
        (*iniLista)->anterior=novo;
        *iniLista=novo;
    }
    return 0;
}
*/

void inserirUser(PELEMENTO *List, INFO dados){
    insertEndList(&List, dados);
    printf("Introduza o seu nome");
    scanf("%s", &List->info.nomeUtilizador);
    printf("Introduza o número do processo");
    scanf("%d", &List->info.ProcessID);
}


