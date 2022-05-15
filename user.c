//
// Created by rodri on 15/05/2022.
//

#include "user.h"

//
// Created by rodri on 02/05/2022.
//


/* LISTAS */

void imprimeElementosDaLista(UElemento *iniLista) {
    UElemento *aux=NULL;
    if (iniLista==NULL) {printf ("lista vazia\n");}
    else {
        aux = iniLista;
        while (aux!=NULL){
            printf ("%d - %s", aux->info.nomeUtilizador,
                    aux->info.nomeUtilizador);
            aux = aux->next;
        }
    }
}


int insertEndList(UElemento **iniListU, UTILIZADOR newUser){
    UElemento *new = NULL, *aux=NULL;
    new = (UElemento *) calloc(1, sizeof(UTILIZADOR));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = newUser;
    new->next = NULL;
    if(*iniListU == NULL) *iniListU = new;
    else{
        aux =*iniListU;
        while(aux->next != NULL) aux=aux->next;
        aux->next=new;
    }
    return 0;
}

int removeInicioLista(UElemento **iniLista){
    UElemento *aux=NULL;
    if (*iniLista == NULL) {
        printf ("Lista vazia\n");
        return -1;
    }
    aux=*iniLista;
    *iniLista=aux->next;
    free(aux);
    return 0;
}

int getSizeIt(UElemento *iniLista){
    UElemento *aux1=NULL;
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

void inserirUser(UElemento *ListU, UTILIZADOR dados){
    int tipo;
    insertEndList(&ListU, dados);
    printf("Introduza o seu nome");
    scanf("%s", &ListU->info.nomeUtilizador);
    printf("Introduza a password");
    scanf("%s", &ListU->info.pp);
    do {
        printf("Administrador(1) ou Utilizador(0)");
        scanf("%d", &ListU->info.tipoDeUtilizador);
        tipo = ListU->info.tipoDeUtilizador;
    } while (tipo != 1 || tipo !=0);
}

/*
int verifyLogin(ELEM_USER iniList, char name[100], char pass[100], intuid){
    ELEM_USER *users = NULL;
    for(users = iniList; users != NULL; users=users->next){
        if((strcmp(users->info.user, name) == 0) && (strcmp(users->info.pass, pass)) == 0 && users->info.type == 1){
            *uid = users->info.id;
            return 1;
        }
        if((strcmp(users->info.user, name) == 0) && (strcmp(users->info.pass, pass)) == 0 && users->info.type == 0){
            *uid = users->info.id;
            return 0;
        }
    }
    return -1;
}

 */

