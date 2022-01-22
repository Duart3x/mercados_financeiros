#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>

#include "utils.h"
#include "exchangeRates.h"
#include "goodsTransactions.h"
#include "interface.h"

int main()
{
    char *res = setlocale(LC_ALL, "Portuguese");
    if (res == NULL)
        puts("setlocale failed");

    printf("a ô í è ª º");

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

    char *listarmoedas[] = {"Listar moedas",
                            "Listar taxas de conversao aplicadas a uma moeda, numa determinada data",
                            "Converter um Montante entre duas Moedas Distintas",
                            "Registar um novo bem",
                            "Listar identificadores de bens transacionaveis",
                            "Valor Minimo, Medio, Desvio Padrao e Maximo de fecho de um bem",
                            "Maior variacao positiva entre o preco de um bem num intervalo de datas",
                            "Bem transacionavel que obteve o melhor desempenho num intervalo de datas",
                            "5 bens transacionaveis com o maior volume de transacoes num intervalo de datas",
                            "Exportar para um ficheiro taxas de conversao num intervalo de datas",
                            "\033[31mSAIR\033[0m"};
    bool exitMenu = false;
    bool askToContinue = true;
    int file = -1;
    do
    {
        askToContinue = true;
        op = drawMenu(listarmoedas, 11, "Menu");
        switch (op)
        {
        case 1:
            menuWithExchangeRatesPagination(exchangeRates, numRows);
            askToContinue = false;
            break;
        case 2:
            printExchangeRateByDateAndCurrency(exchangeRates, numRows);
            askToContinue = false;
            break;

        case 3:
            chooseCurrenciesToConvert(exchangeRates, numRows);
            askToContinue = false;
            break;
        case 4:
            goodTransactions = newGoodQuestionaire(goodTransactions, &numGoodTransactionsRows);
            askToContinue = false;
            break;
        case 5:
            file = askFileToUse(numGoodTransactionsRows, numGoodsRows);
            if (file == 1)
                listGoodsIndentifiers(goodsHistory, numGoodsRows);
            else if (file == 2)
                listGoodsIndentifiers(goodTransactions, numGoodTransactionsRows);
            else
                askToContinue = false;

            break;
        case 6:
            file = askFileToUse(numGoodTransactionsRows, numGoodsRows);
            if (file == 1)
                closeValueStatistics(goodsHistory, numGoodsRows);
            else if (file == 2)
                closeValueStatistics(goodTransactions, numGoodTransactionsRows);

            askToContinue = false;
            break;
        case 7:
            file = askFileToUse(numGoodTransactionsRows, numGoodsRows);
            if (file == 1)
                maxPriceVariation(goodsHistory, numGoodsRows);
            else if (file == 2)
                maxPriceVariation(goodTransactions, numGoodTransactionsRows);
            else
                askToContinue = false;
            break;
        case 8:
            file = askFileToUse(numGoodTransactionsRows, numGoodsRows);
            if (file == 1)
                bestPerformanceGood(goodsHistory, numGoodsRows);
            else if (file == 2)
                bestPerformanceGood(goodTransactions, numGoodTransactionsRows);

            askToContinue = false;
            break;
        case 9:
            file = askFileToUse(numGoodTransactionsRows, numGoodsRows);
            if (file == 1)
                fiveGoodsWithMoreTransactions(goodsHistory, numGoodsRows);
            else if (file == 2)
                fiveGoodsWithMoreTransactions(goodTransactions, numGoodTransactionsRows);
            else
                askToContinue = false;
            break;
        case 10:
            exportExchangeRatesToFile(exchangeRates, numRows);
            askToContinue = false;
            break;

        case 11:
        case -1:
            exitMenu = true;
            break;
        }
        if (!exitMenu && askToContinue)
        {
            printf("\n\n");
            printf("  \033[7mPressione qualquer tecla para continuar...\033[0m");
            getch();
            system("cls");
        }
    } while (!exitMenu);

    char *sNOptions[] = {"Sim", "Nao"};

    op = drawMenu(sNOptions, 2, "Deseja guardar as alteracoes feitas?");

    if (op == 1)
        saveGoodsToFile(goodTransactions, &numGoodTransactionsRows);

    free(exchangeRates);
    free(goodsHistory);
    free(goodTransactions);

    system("cls");
    printf("\n  Obrigado por utilizar o programa!\n\n  \033[4mTrabalho realizado por\033[0m:\n  - Duarte Santos\t22593\n  - Simao Teixeira\t22590\n  - Jose Almeida\t22982\n  - Maria Simoes\t22993\n");

    printf("\n  \033[7mPressione uma tecla para fechar a consola...\033[0m");
    getch();

    return 0;
}