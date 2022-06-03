//
// Created by rodri on 24/05/2022.
//

#include "processos.h"

/* LISTAS */

//DUPLAMENTE LIGADAS

PROCESSO pedeDadosP(int id, PELEMENTO *iniListaN, PELEMENTO *iniListaU, PELEMENTO *iniListaR, PELEMENTO *iniListaP){        //pede dados para a estrutuda de dados do Processo
    time_t rawtime;
    time( &rawtime );
    PROCESSO dados;
    int tipoDeProcessoP, tamLista;
    tamLista = tamanhoP(iniListaN) + tamanhoP(iniListaR) +
               tamanhoP(iniListaU) + tamanhoP(iniListaP);
    dados.ProcessID = tamLista + 1;
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

void removelem(PELEMENTO **iniListaU, PELEMENTO **fimListaU,PELEMENTO **iniListaN, PELEMENTO **fimListaN,PELEMENTO **iniListaR, PELEMENTO **fimListaR){
    PELEMENTO *aux= NULL;
    int num, sizeU, sizeN, sizeR, Usize, Nsize, Rsize;
    printf("Introduza o número de processo que pretende apagar: ");
    scanf("%d", &num);
    sizeU = tamanhoP(*iniListaU);
    for (aux = *iniListaU; aux!=NULL ;aux = aux->next){
        if(num == aux->info.ProcessID){
            removeElem(iniListaU,fimListaU, aux->info.ProcessID);
        }
    }
    Usize = tamanhoP(*iniListaU);
    sizeN = tamanhoP(*iniListaN);
    for (aux = *iniListaN; aux!=NULL ;aux = aux->next){
        if(num == aux->info.ProcessID){
            removeElem(iniListaN,fimListaN, aux->info.ProcessID);
        }
    }
    Nsize = tamanhoP(*iniListaN);
    sizeR = tamanhoP(*iniListaR);
    for (aux = *iniListaR; aux!=NULL ;aux = aux->next){
        if(num == aux->info.ProcessID){
            removeElem(iniListaR,fimListaR, aux->info.ProcessID);
        }
    }
    Rsize = tamanhoP(*iniListaR);

    if(sizeR != Rsize || sizeU != Usize || sizeN != Nsize){
        printf("Remoção com sucesso!!\n");
        system("pause");
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

void imprimeElementosDaListaP(PELEMENTO *iniListaP, int id, int admin){
    PELEMENTO *aux= iniListaP;
    while (aux!=NULL){
        if(admin == 1) printf("PID: %d, Nome: %s,Descrição: %s\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.descricao);
        else if(aux->info.dono == id) printf("PID: %d, Nome: %s,Descrição: %s\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.descricao);
        aux = aux->next;
    }
}

void relatorioPorNome(PROCESSO dados){
    FILE *fp = NULL;
    fp = fopen("relatorioProcessos.txt", "w");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro");
    }
    fprintf(fp, "Pid: %d, Nome: %s, Descrição: %s", dados.ProcessID, dados.nomeUtilizador, dados.descricao);
    fclose(fp);
}

PROCESSO retornaFim(PELEMENTO *fimLista){
    PELEMENTO *aux = fimLista;
    return fimLista->info;
}

PROCESSO retornaInicio(PELEMENTO *iniLista){
    PELEMENTO *aux = iniLista;
    if (aux != NULL){
        return aux->info;
    }

}

void escreveFicheirotxt(PROCESSO dadosP){
    FILE *fp = fopen("Processados.txt", "a");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro");
    }
    fprintf(fp,"Pid: %d, Nome: %s, Descrição: %s, Data de criação: %d/%d/%d - %d:%d:%d, Data de execução: %d/%d/%d - %d:%d:%d\n",dadosP.ProcessID, dadosP.nomeUtilizador, dadosP.descricao, dadosP.tempCriado.tm_mday, dadosP.tempCriado.tm_mon+1, dadosP.tempCriado.tm_year+1900, dadosP.tempCriado.tm_hour, dadosP.tempCriado.tm_min, dadosP.tempCriado.tm_sec,
            dadosP.tempExecutado.tm_mday, dadosP.tempExecutado.tm_mon+1, dadosP.tempExecutado.tm_year+1900, dadosP.tempExecutado.tm_hour, dadosP.tempExecutado.tm_min, dadosP.tempExecutado.tm_sec);
    fclose(fp);
}

void executarProcesso(Estatisticas *estatisticas,PELEMENTO **iniListaP,PELEMENTO **fimListaP,PELEMENTO **iniListaU,PELEMENTO **fimListaU,PELEMENTO **iniListaN,PELEMENTO **fimListaN,PROCESSO dadosP){
    //executar - remover no fim e inserir
    lerEstatisticas(estatisticas);
    time_t ramtime;
    time(&ramtime);
    int res, lastSize, afterSize;
    printf("Pretende executar um processo? Sim(1) ou Não(0)");
    scanf("%d", &res);
    if (res == 1 && tamanhoP(*iniListaU) > 0){
        dadosP = retornaFim(*fimListaU);
        removeElem(iniListaU, fimListaU, dadosP.ProcessID);
        dadosP.tipoProcesso = 2;
        dadosP.tempExecutado = *localtime(&ramtime);
        lastSize = tamanhoP(*iniListaP);
        InserirFimListaP(iniListaP, fimListaP, dadosP);
        afterSize = tamanhoP(*iniListaP);
        if (lastSize < afterSize){
            escreveFicheirotxt(dadosP);
            estatisticas->numerosProcessosProcessadosU++;
            gravaEstatisticas(estatisticas);
        }
    }else if(res == 1 && tamanhoP(*iniListaN) > 0){
        dadosP = retornaFim(*fimListaN);
        removeElem(iniListaN, fimListaN, dadosP.ProcessID);
        dadosP.tipoProcesso = 2;
        dadosP.tempExecutado = *localtime(&ramtime);
        lastSize = tamanhoP(*iniListaP);
        InserirFimListaP(iniListaP, fimListaP, dadosP);
        afterSize = tamanhoP(*iniListaP);
        if (lastSize < afterSize){
            escreveFicheirotxt(dadosP);
            estatisticas->numerosProcessosProcessadosN++;
            gravaEstatisticas(estatisticas);
        }
    }
}

void executarProcessoRejeitado(PELEMENTO **iniListaR,PELEMENTO **fimListaR,PELEMENTO **iniListaU,PELEMENTO **fimListaU,PELEMENTO **iniListaN,PELEMENTO **fimListaN,PROCESSO dadosP){
    PELEMENTO *aux = NULL;
    int res, processorej, restipo;
    printf("Deseja executar algum processo rejeitado? Sim(1) ou Não(0)");
    scanf("%d", &res);
    if(res == 1){
        printf("Introduza o número de processo rejeitado: ");
        scanf("%d", &processorej);
        for (aux= *iniListaR; aux!=NULL ;aux = aux->next){
            if (processorej == aux->info.ProcessID){
                printf("O processo é urgente(1) ou Normal(0)?");
                scanf("%d", &restipo);
                if (restipo == 1){
                    dadosP = retornaFim(*fimListaR);
                    removeElem(iniListaR, fimListaR,dadosP.ProcessID);
                    dadosP.tipoProcesso = 1;
                    InserirFimListaP(iniListaU, fimListaU, dadosP);
                }else if(restipo == 0){
                    dadosP = retornaFim(*fimListaR);
                    removeElem(iniListaR, fimListaR,dadosP.ProcessID);
                    dadosP.tipoProcesso = 1;
                    InserirFimListaP(iniListaN, fimListaN, dadosP);
                }
            }
        }
    }
}

void pesquisarProcesso(PELEMENTO *iniListaN, PELEMENTO *iniListaR, PELEMENTO *iniListaU, PELEMENTO *iniListaP){
    PELEMENTO *aux = NULL;
    int pid;
    printf("Introduza o número de processo: ");
    scanf("%d", &pid);
    for (aux=iniListaU; aux!=NULL ;aux = aux->next) {
        if (pid == aux->info.ProcessID){
            printf("\n Processo Encontrado --- [ %d ]", aux->info.ProcessID);
            printf("\n 1) Nome: %s", aux->info.nomeUtilizador );
            printf("\n 2) Tipo de processo: %d", aux->info.tipoProcesso);
            printf("\n 3) Descrição: %s", aux->info.descricao);
            printf("\n 4) Data de criação: %d/%d/%d - %d:%d:%d\nData de execução: %d/%d/%d - %d:%d:%d\n", aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon+1, aux->info.tempCriado.tm_year+1900, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec,
                   aux->info.tempExecutado.tm_mday, aux->info.tempExecutado.tm_mon+1, aux->info.tempExecutado.tm_year+1900, aux->info.tempExecutado.tm_hour, aux->info.tempExecutado.tm_min, aux->info.tempExecutado.tm_sec);
        }
    }
    for (aux=iniListaN; aux!=NULL ;aux = aux->next) {
        if (pid == aux->info.ProcessID){
            printf("\n Processo Encontrado --- [ %d ]b", aux->info.ProcessID);
            printf("\n 1) Nome: %s", aux->info.nomeUtilizador );
            printf("\n 2) Tipo de processo: %d", aux->info.tipoProcesso);
            printf("\n 3) Descrição: %s", aux->info.descricao);
            printf("\n 4) Data de criação: %d/%d/%d - %d:%d:%d\nData de execução: %d/%d/%d - %d:%d:%d", aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon, aux->info.tempCriado.tm_year, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec, aux->info.tempExecutado
                    ,aux->info.tempExecutado.tm_mday, aux->info.tempExecutado.tm_mon, aux->info.tempExecutado.tm_year, aux->info.tempExecutado.tm_hour, aux->info.tempExecutado.tm_min, aux->info.tempExecutado.tm_sec);
        }
    }
    for (aux=iniListaR; aux!=NULL ;aux = aux->next) {
        if (pid == aux->info.ProcessID){
            printf("\n Processo Encontrado --- [ %d ]", aux->info.ProcessID);
            printf("\n 1) Nome: %s", aux->info.nomeUtilizador );
            printf("\n 2) Tipo de processo: %d", aux->info.tipoProcesso);
            printf("\n 3) Descrição: %s", aux->info.descricao);
            printf("\n 4) Data de criação: %d/%d/%d - %d:%d:%d\nData de execução: %d/%d/%d - %d:%d:%d\n", aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon+1, aux->info.tempCriado.tm_year+1900, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec,
                   aux->info.tempExecutado.tm_mday, aux->info.tempExecutado.tm_mon+1, aux->info.tempExecutado.tm_year+1900, aux->info.tempExecutado.tm_hour, aux->info.tempExecutado.tm_min, aux->info.tempExecutado.tm_sec);
        }
    }
    for (aux=iniListaP; aux!=NULL ;aux = aux->next) {
        if (pid == aux->info.ProcessID){
            printf("\n Processo Encontrado --- [ %d ]", aux->info.ProcessID);
            printf("\n 1) Nome: %s", aux->info.nomeUtilizador );
            printf("\n 2) Tipo de processo: %d", aux->info.tipoProcesso);
            printf("\n 3) Descrição: %s", aux->info.descricao);
            printf("\n 4) Data de criação: %d/%d/%d - %d:%d:%d\nData de execução: %d/%d/%d - %d:%d:%d\n", aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon+1, aux->info.tempCriado.tm_year+1900, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec,
                   aux->info.tempExecutado.tm_mday, aux->info.tempExecutado.tm_mon+1, aux->info.tempExecutado.tm_year+1900, aux->info.tempExecutado.tm_hour, aux->info.tempExecutado.tm_min, aux->info.tempExecutado.tm_sec);
        }
    }
}

void rankingProcessos(PELEMENTO *iniListaU, PELEMENTO *iniListaN){
    PROCESSO dadosU, dadosN;
    PELEMENTO *aux = NULL;
    int varIncrementada = 0;
    dadosU = retornaFim(iniListaU);
    dadosN = retornaFim(iniListaN);

    if(tamanhoP(iniListaU) == 0){
        varIncrementada = dadosN.ProcessID;
    }else if(tamanhoP(iniListaN)){
        varIncrementada = dadosU.ProcessID;
    }else if(tamanhoP(iniListaU) && tamanhoP(iniListaN)){
        printf("Não existe nenhum processo");
        return ;
    }
    if (dadosU.ProcessID > dadosN.ProcessID) varIncrementada = dadosN.ProcessID;
    else varIncrementada = dadosU.ProcessID;

    for (aux = iniListaU; aux != NULL;aux = aux->next){
        if (varIncrementada == aux->info.ProcessID){
            printf("%d - %s - Data de criação: %d/%d/%d - %d:%d:%d\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon+1, aux->info.tempCriado.tm_year+1900, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec);
            varIncrementada++;
        }
    }
    for (aux = iniListaN; aux != NULL;aux = aux->next){
        if (varIncrementada == aux->info.ProcessID){
            printf("%d - %s - Data de criação: %d/%d/%d - %d:%d:%d, Data de execução: %d/%d/%d - %d:%d:%d\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.tempCriado.tm_mday, aux->info.tempCriado.tm_mon+1, aux->info.tempCriado.tm_year+1900, aux->info.tempCriado.tm_hour, aux->info.tempCriado.tm_min, aux->info.tempCriado.tm_sec);
            varIncrementada++;
        }
    }
}

void numAtualProcessos(PELEMENTO *iniListaU, PELEMENTO *iniListaN, UElemento *ListaU){
    UElemento *auxU = NULL;
    PELEMENTO *aux = NULL;
    //quando o id do user for igual ao dono do processo printa
    char nome[50];
    int flag, id;
    system("cls");
    imprimeListaU(ListaU);
    printf("Introduza o nome do utilizador que prentende listar: ");
    scanf("%s", &nome);
    if(strlen(nome) < 2){
        do{
            printf("\nPor favor insira pelo menos 2 caracteres para procurar pelo nome: ");
            scanf("%s", &nome);
            fflush(stdin);
        }while (strlen(nome) < 2);
    }
    for (auxU = ListaU; auxU!=NULL ;auxU = auxU->next){
        if(strstr(nome, auxU->info.nomeUtilizador)){
            flag = 1;
        }
    }
    if (flag == 1){
        printf("Utilizadores que contem '%s'\n", nome);
        for (auxU = ListaU; auxU!=NULL ;auxU = auxU->next){
            if(strstr(nome, auxU->info.nomeUtilizador)){
                printf("Id: %d, Nome: %s, Tipo: %d\n", auxU->info.id, auxU->info.nomeUtilizador, auxU->info.tipoDeUtilizador);
            }
        }
        printf("Qual o Utilizador que quer escolher?: ");
        scanf("%d", &id);
        printf("** Lista urgente **\n");
        for (aux = iniListaU; aux!=NULL ;aux = aux->next){
            if(id == aux->info.dono){
                printf("Id: %d, Nome: %s, Tipo: %d\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.tipoProcesso);
            }
        }
        printf("** Lista Normal **\n");
        for (aux = iniListaN; aux!=NULL ;aux = aux->next){
            if(id == aux->info.dono){
                printf("Id: %d, Nome: %s, Tipo: %d\n", aux->info.ProcessID, aux->info.nomeUtilizador, aux->info.tipoProcesso);
            }
        }

    }
}

//menus

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
        printf("0 - Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &resProcesso);
    } while (resProcesso > 7 || resProcesso < 0);
    return resProcesso;
}