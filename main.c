#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include "utils.h"
#include "exchangeRates.h"
#include "goodsTransactions.h"
#include "interface.h"

int main()
{
    char *res = setlocale(LC_ALL, "portuguese");
    if (res == NULL)
        puts("setlocale failed");

    printf("ã ô í è ª º");

    EXCHANGERATE *exchangeRates;
    EXCHANGERATE findExchange;
    char **sortedCurrencies;

    int numRows;
    int op;

    FILE *fp = openFile("files/exchangeRates.txt", "r");
    if (fp == NULL)
        return 1;

    exchangeRates = readExchangeRatesFile(fp, &numRows);
    // drawExchangeRates(exchangeRates, numRows);

    // findExchange = getExchangeRateByDate(exchangeRates, numRows, (DATE){.day = 10, .month = 7, .year = 2003});

    //drawExchangeRate(findExchange);

    //menuWithExchangeRatesPagination(exchangeRates, numRows);

    printColoredText("O Duarte é chato", GREEN);

    // double resultado = convertCurrenciesOnSpecificDay(exchangeRates, numRows, (DATE){.day = 1, .month = 12, .year = 2022}, USD, 20, AUD);

    /*char *opcoes[] = {"Sair", "Listar", "Buscar", "Ordenar"};
    op = drawMenu(opcoes, 4, "Menu");
    printf("%d fdp", op);*/

    // newGoodQuestionaire();

    free(exchangeRates);
    return 0;
}