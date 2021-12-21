#include<stdio.h>
#include"utils.h"
#include"goodsTransactions.h"
#include<ctype.h>

void newGoodQuestionaire() {
    GOOD good;
    bool isValid = true;

    printf("*** Registo de novo bem ***\n");

    do
    {
        system("cls");

        printf("Identificacao do bem: ");
        scanf("%s", good.name);

        if(good.name[0] == '\0') {
            printf("Identificador do bem nao pode ser vazio.\n");
            isValid = false;
            return;
        }

        if(isalpha(good.name) == 0) {
            printf("Identificador só pode conter letras.\n");
            isValid = false;
            return;
        }

        good.name = toupper(good.name);
        isValid
    } while (!isValid);
    

    
}