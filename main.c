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
    GOOD *goodsHistory;
    GOOD *goodTransactions;

    EXCHANGERATE findExchange;
    char **sortedCurrencies;

    int numRows;
    int numGoodsRows;
    int numGoodTransactionsRows;

    int op;

    FILE *fp = openFile("files/exchangeRates.txt", "r");
    FILE *fGoodsHistory = openFile("files/goodsHistory.txt", "r");

    if (fp == NULL || fGoodsHistory == NULL)
        return 1;

    exchangeRates = readExchangeRatesFile(fp, &numRows);
    goodsHistory = readGoodsTransactionsHistoryFile(fGoodsHistory, &numGoodsRows);
    goodTransactions = readGoodsTransactionsFile(&numGoodTransactionsRows);

    /*for (int i = 0; i < 5000; i++)
    {
        printf("\n");
        printf("[%d-%d-%d] | [%s]\n", goodsHistory[i].obsDate.day, goodsHistory[i].obsDate.month, goodsHistory[i].obsDate.year,CURRENCIES[goodsHistory[i].currency]);
        printf("Bem: %s\n", goodsHistory[i].name);
        printf("Valor de abertura: %.3f\n", goodsHistory[i].openValue);
        printf("Valor de fechamento: %.3f\n", goodsHistory[i].closeValue);
        printf("Valor mais alto: %.3f\n", goodsHistory[i].higherValue);
        printf("Valor mais baixo: %.3f\n", goodsHistory[i].lowerValue);
        printf("Volume: %d\n", goodsHistory[i].volume);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[goodsHistory[i].marketType]);
        printf("-------------------------------------------------------------------------------------\n");
    }    */

    // drawExchangeRates(exchangeRates, numRows);

    // findExchange = getExchangeRateByDate(exchangeRates, numRows, (DATE){.day = 10, .month = 7, .year = 2003});

    //drawExchangeRate(findExchange);

    //menuWithExchangeRatesPagination(exchangeRates, numRows);

    // double resultado = convertCurrenciesOnSpecificDay(exchangeRates, numRows, (DATE){.day = 1, .month = 12, .year = 2022}, USD, 20, AUD);

   /* char *listarmoedas[] = {"Listar Moedas que Suportam Conversões de Valores",
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
        break;
    case 2:
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
    }*/

    GOOD good = (GOOD){.name = "Bem", .openValue = 1.0, .closeValue = 2.0, .higherValue = 3.0, .lowerValue = 4.0, .volume = 5, .marketType = 0, .currency = 0, .obsDate = (DATE){.day = 1, .month = 1, .year = 2020}};

    addGoodToFile(good,goodTransactions, &numGoodTransactionsRows);
    //newGoodQuestionaire(goodTransactions, &numGoodTransactionsRows);

    free(exchangeRates);
    free(goodsHistory);
    free(goodTransactions);

    return 0;
}