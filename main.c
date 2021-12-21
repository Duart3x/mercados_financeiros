#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include<locale.h>
#include"utils.h"
#include"exchangeRates.h"
#include"goodsTransactions.h"
#include"interface.h"



int main(){
    char* res = setlocale(LC_ALL, ".UTF8");
	if (res == NULL) puts("setlocale failed");

    EXCHANGERATE *exchangeRate;
    EXCHANGERATE findExchange;

    int numRows;
    int op;

    FILE* fp = openFile("files/exchangeRates.txt", "r");
    if(fp == NULL)
        return 1;

    exchangeRate = readExchangeRatesFile(fp, &numRows);
    // drawExchangeRates(exchangeRate, numRows);

    // findExchange = getExchangeRateByDate(exchangeRate, numRows, (DATE){.day = 10, .month = 7, .year = 2003});

    //drawExchangeRate(findExchange);


    //menuWithExchangeRatesPagination(exchangeRate, numRows);

    /*char *opcoes[] = {"Sair", "Listar", "Buscar", "Ordenar"};
    op = drawMenu(opcoes, 4, "Menu");
    printf("%d fdp", op);*/

    newGoodQuestionaire();
    

    free(exchangeRate);
    return 0;
}