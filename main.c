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

    char *listarmoedas[] = {"Listar Moedas que Suportam Conversces de Valores",
                            "Converter um Montante entre duas Moedas Distintas",
                            "Registar Valor histórico diario de um bem transacionado",
                            "Listar identificadores de bens transacionaveis",
                            "Valor Mínimo, Medio, Desvio Padrao e Maximo de fecho de um bem transacionavel",
                            "Maior variacao positiva entre o preco de abertura e de fecho de um bem transacionavel num intervalo de datas",
                            "Bem transacionavel que obteve o melhor desempenho num intervalo de datas",
                            "5 bens transacionaveis com o maior volume de transacces num intervalo de datas",
                            "Exportar para um ficheiro texto as taxas de conversao aplicaveis a uma moeda num intervalo de datas",
                            "\033[31mSAIR\033[0m"};
    bool exitMenu = false;
    bool askToContinue = true;
    do
    {
        askToContinue = true;
        op = drawMenu(listarmoedas, 10, "Menu");
        switch (op)
        {
            case 1:
                menuWithExchangeRatesPagination(exchangeRates, numRows);
                askToContinue = false;
                break;
            case 2:
                chooseCurrenciesToConvert(exchangeRates, numRows);
                askToContinue = false;
                break;
            case 3:
                newGoodQuestionaire(goodTransactions, &numGoodTransactionsRows);
                break;
            case 4:
                askFileToUse(numGoodTransactionsRows, numGoodsRows) == 1 ? listGoodsIndentifiers(goodsHistory, numGoodsRows) : listGoodsIndentifiers(goodTransactions, numGoodTransactionsRows);
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

            case 10:
            case -1:
                exitMenu = true;
                break;
        }
        if(!exitMenu && askToContinue)
        {
            printf("\n\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            system("cls");
        }
    }while(!exitMenu);

    char* sNOptions[] = {"Sim","Nao"};

    op = drawMenu(sNOptions, 2, "Deseja guardar as alteracoes feitas?");

    if(op == 1)
        saveGoodsToFile(goodTransactions, &numGoodTransactionsRows);


    //newGoodQuestionaire();

    /*GOOD good = (GOOD){.name = "ETH", .openValue = 3.0, .closeValue = 4.0, .higherValue = 3.0, .lowerValue = 4.0, .volume = 552, .marketType = 0, .currency = 0, .obsDate = (DATE){.day = 1, .month = 1, .year = 2022}};

    //addGoodToFile(good,goodTransactions, &numGoodTransactionsRows);
    //saveGoodsToFile(goodTransactions, &numGoodTransactionsRows);*/

    //listGoodsIndentifiers(goodsHistory, numGoodsRows);
    // newGoodQuestionaire(goodTransactions, &numGoodTransactionsRows);

    free(exchangeRates);
    free(goodsHistory);
    free(goodTransactions);

    system("cls");
    printf("\n  Obrigado por utilizar o programa!\n");

    printf("\n  \033[7mPressione uma tecla para fechar a consola...\033[0m");
    getch();

    return 0;
}