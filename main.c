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

    printColoredText("O Duarte é chato a Maria é mais", GREEN);

    // double resultado = convertCurrenciesOnSpecificDay(exchangeRates, numRows, (DATE){.day = 1, .month = 12, .year = 2022}, USD, 20, AUD);

    char *listarmoedas[] = {"Listar Moedas que Suportam Conversões de Valores",
     "Converter um Montante entre duas Moedas Distintas",
     "Registar Valor histórico diário de um bem transacionado",
     "Listar identificadores de bens transacionáveis",
     "Valor Mínimo, Médio, Desvio Padrão e Máximo de fecho de um bem transacionável",
     "Maior variação positiva entre o preço de abertura e de fecho de um bem transacionável num intervalo de datas",
     "Bem transacionável que obteve o melhor desempenho num intervalo de datas",
     "5 bens transacionáveis com o maior volume de transações num intervalo de datas",
     "Exportar para um ficheiro texto as taxas de conversão aplicáveis a uma moeda num intervalo de datas"};
    op = drawMenu(listarmoedas, 9, "Menu");
    printf("%d fdp", op);
    switch (op)
    {
    case 1:
        /* code */
        break;
    case 2:
        chooseCurrenciesToConvert();

        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
        
    
    default:
        break;
    }

    //newGoodQuestionaire();

    free(exchangeRates);
    return 0;
}