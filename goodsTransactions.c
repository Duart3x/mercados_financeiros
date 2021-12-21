#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include"interface.h"
#include"goodsTransactions.h"

void newGoodQuestionaire() {
    GOOD good;
    bool isValid = true;

    printf("*** Registo de novo bem ***\n");

    char buffer[100];
    do
    {
        system("cls");

        printf("Identificacao do bem: ");
        fgets(buffer, sizeof(buffer), stdin);

        good.name = (char *) malloc(strlen(buffer) + 1);
        strcpy(good.name, buffer);

        if(strlen(good.name) - 1 == 0) {
            handleError("Identificador do bem nao pode ser vazio.");
            isValid = false;
            return;
        }

        if(contaisNumber(good.name) == true) {
            handleError("Identificador só pode conter letras.");
            isValid = false;
            return;
        }

        good.name = strToUpper(good.name);
        printf("\nNome do bem: %s\n", good.name);

        free(good.name);

    } while (!isValid);
    

    
}