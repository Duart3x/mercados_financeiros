#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include<locale.h>
#include"utils.h"
#include"exchangeRates.h"
#include"interface.h"



int main(){

    setlocale(LC_ALL, "Portuguese");

    EXCHANGERATE *exchangeRate;
    EXCHANGERATE findExchange;

    int linhasLidas;
    int op;

    FILE* fp = openFile("files/exchangeRates.txt", "r");
    if(fp == NULL)
        return 1;

    exchangeRate = readExchangeRatesFile(fp, &linhasLidas);
    // drawExchangeRates(exchangeRate, linhasLidas);

    // findExchange = getExchangeRateByDate(exchangeRate, linhasLidas, (DATE){.day = 10, .month = 7, .year = 2003});

    //drawExchangeRate(findExchange);


    menuWithExchangeRatesPagination(exchangeRate, linhasLidas);

    /*char *opcoes[] = {"Sair", "Listar", "Buscar", "Ordenar"};
    op = drawMenu(opcoes, 4, "Menu");
    printf("%d fdp", op);*/
    

    free(exchangeRate);
    return 0;
}