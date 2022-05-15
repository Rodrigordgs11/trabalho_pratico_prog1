#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processos.h"
#include "user.h"

int menuPrincipal(){
    int resmenuPrincipal;
    printf("MENU PRINCIPAL\n\n");
    printf("1 - Administrador\n");
    printf("2 - Convidado\n");
    printf("0 - Sair\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &resmenuPrincipal);
    fgetc(stdin);
    return resmenuPrincipal;
}

int administrador(){
    int resAdminstrador;
    printf("AREA DE ADMINISTRADOR\n\n");
    printf("1 - Login\n");
    printf("0 - Sair\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &resAdminstrador);
    fgetc(stdin);
    return resAdminstrador;
}

int LoginAdmin(){
    int processId; char pp[50];
    printf("LOGIN ADMINISTRADOR\n");
    printf("Introduza o seu ProcessID");
    scanf("%d", &processId);
    printf("Introduza a palavra passe");
    scanf("%s", &pp);
    printf("Escolha a opcao desejada: ");
    /* VERIFICAÇÃO */
    //return ;/* 1 Valido, 0 - Invalido */

}

int Admin(){
    int processId; char pp[50];
    printf("Introduza o seu ProcessID");
    scanf("%d", &processId);
    printf("Introduza o seu ProcessID");
    scanf("%d", pp);
    printf("Escolha a opcao desejada: ");
    /* VERIFICAÇÃO */

    return 1;
}



int convidado(){
    int resConvidado;
    printf("1 - Administrador");
    printf("2 - Convidado");
    printf("0 - Sair");
    scanf("%d", &resConvidado);
}

int menu() {
    int resMenu;
    printf("1 - Gestao de processos\n");
    printf("2 - \n");
    printf("3 - \n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &resMenu);
    return resMenu;
}

int gestaoProcesso(){
    int resProcesso;
    system("cls");
    printf("GESTAO DE PROCESSOS\n");
    printf("1 - Inserir Processo\n");
    printf("2 - Remover Processo\n");
    printf("3 - Imprimir Processo\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d",&resProcesso);
    return resProcesso;
}

int main() {
    UElemento *List = NULL;
    INFO dados;

    switch(menuPrincipal()){
        case 1:
            system("cls");
            switch (administrador()){
                case 1:
                    system("cls");
                    switch (Admin()){
                        case 1:
                           gestaoProcesso();
                        break;
                    }
                break;
            }
        case 2:
            switch (convidado()) {

            }
        break;
    }
        switch (menu()) {
            case 1:
                switch (gestaoProcesso()) {
                    case 1:
                        printf("111");
                        break;
                }
                break;
            case 2:

                break;
            case 3:
                break;
        }
    return 0;
}
