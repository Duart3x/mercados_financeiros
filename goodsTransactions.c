#include<stdio.h>
#include"utils.h"
#include"goodsTransactions.h"
#include<ctype.h>

void newGoodQuestionaire() {
    GOOD good;
    BOOLEAN isValid = true;

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

        if(contaisNumber(good.name) == true) {
            printf("Identificador só pode conter letras.\n");
            isValid = false;
            return;
        }

        good.name = strToUpper(good.name);
    } while (!isValid);
    

    
}