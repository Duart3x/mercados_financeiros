#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "utils.h"
#include "exchangeRates.h"
#include "interface.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_ENTER 13

void drawExchangeRates(EXCHANGERATE *exchangeRates, int numRows)
{
    printf("\n\n");
    for (int i = 0; i < numRows; i++)
    {
        drawExchangeRate(exchangeRates[i], NULL);
    }
}

void drawExchangeRate(EXCHANGERATE exchangeRate, char **currenciesText)
{
    int middle = ceil(CURRENCIES_SIZE / 2.0);
    printf("\n[%02d-%02d-%02d]\n", exchangeRate.conversionDate.day, exchangeRate.conversionDate.month, exchangeRate.conversionDate.year);

    float value1, value2;
    char *strVal1 = malloc(sizeof(char) * 4);
    char *strVal2 = malloc(sizeof(char) * 4);

    strVal1 = NULL;
    strVal2 = NULL;
    bool wasNull = false;
    if(currenciesText == NULL)
    {
        wasNull = true;
        currenciesText = cloneCurrenciesArray();
    }
        

    for (int j = 0; j < ceil(CURRENCIES_SIZE / 2.0); j++)
    {
        value1 = exchangeRate.currencies[j];
        value2 = exchangeRate.currencies[j + middle];

        if (value1 == -1)
            strVal1 = "N/A";
        if (value2 == -1)
            strVal2 = "N/A";

        if (j + middle > CURRENCIES_SIZE - 1)
        {
            if (strVal1 != NULL)
                printf("\t%s = %s\n", currenciesText[j], strVal1);
            else
                printf("\t%s = %.02lf\n", currenciesText[j], value1);
        }
        else
        {
            if (strVal1 != NULL && strVal2 != NULL)
                printf("\t%s = %s \t %s = %s\n", currenciesText[j], strVal1, currenciesText[j + middle], strVal2);
            else if (strVal1 != NULL)
                printf("\t%s = %s \t %s = %.02lf \n", currenciesText[j], strVal1, currenciesText[j + middle], value2);
            else if (strVal2 != NULL)
                printf("\t%s = %.02lf \t %s = %s\n", currenciesText[j], value1, currenciesText[j + middle], strVal2);
            else
                printf("\t%s = %.02lf \t %s = %.02lf\n", currenciesText[j], value1, currenciesText[j + middle], value2);
        }

        strVal1 = NULL;
        strVal2 = NULL;
    }

    if(wasNull == true)
        free(currenciesText);

    free(strVal1);
    free(strVal2);
}

void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char **sortedCurrencies)
{
    int i;
    printf("\n");

    for (i = paginaAtual * linhasPorPagina; i < (paginaAtual * linhasPorPagina) + linhasPorPagina; i++)
    {
        if (i < numRows)
        {
            printf("-----------------------------------------------------\n");
            drawExchangeRate(exchangeRates[i], sortedCurrencies);
        }
    }
    
}

void drawExchangeRatesPaginationSortedByValue(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char*** sortedCurrencyNamesByDay)
{
    int i;
    printf("\n");

    for (i = paginaAtual * linhasPorPagina; i < (paginaAtual * linhasPorPagina) + linhasPorPagina; i++)
    {
        if (i < numRows)
        {
            printf("-----------------------------------------------------\n");
            drawExchangeRate(exchangeRates[i], sortedCurrencyNamesByDay[i]);
        }
    }
    
}

void menuWithExchangeRatesPagination(EXCHANGERATE *exchangeRatesOriginal, int numRows)
{
    int paginaAtual = 0;
    int linhasPorPagina = 5;
    int opcao = 0;
    int sortedBy = 0; // 0 = NOT SORTED, 1 = SORTED BY CURRENCY, 2 = SORTED BY VALUE
    char **sortedCurrencies = cloneCurrenciesArray();
    char*** sortedCurrencyNamesByDay = malloc(sizeof(char**) * numRows);
    for (int i = 0; i < numRows; i++)
    {
        sortedCurrencyNamesByDay[i] = malloc(sizeof(char*) * CURRENCIES_SIZE);

        for (int j = 0; j < CURRENCIES_SIZE; j++)
        {
            sortedCurrencyNamesByDay[i][j] = malloc(sizeof(char) * 4);
        }
    }
    
    int i = 0;

    EXCHANGERATE* exchangeRates = cloneExchangeRatesArray(exchangeRatesOriginal, numRows);


    do
    {
        if(sortedBy == 2)
            drawExchangeRatesPaginationSortedByValue(exchangeRates, numRows, paginaAtual, linhasPorPagina, sortedCurrencyNamesByDay);
        else
            drawExchangeRatesPagination(exchangeRates, numRows, paginaAtual, linhasPorPagina, sortedCurrencies);
        printf("\nPagina %04d de %d\n", paginaAtual, (int)ceil((double)numRows / linhasPorPagina) - 1);
        printf("%d registos por pagina\n", linhasPorPagina);

        printf("\n\n");
        printf("1 - Página anterior\n");
        printf("2 - Proxima pagina\n");
        printf("3 - Escolher numero de pagina\n");
        printf("4 - Escolher numero de registos por pagina\n");
        printf("5 - Ordernar por ordem crescente do codigo da moeda\n");
        printf("6 - Ordernar por ordem decrescente do valor em euros\n");
        printf("7 - Voltar a ordem original\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            paginaAtual--;
            break;
        case 2:
            paginaAtual++;
            break;
        case 3:
            printf("\n");
            printf("Pagina: ");
            scanf("%d", &paginaAtual);
            break;
        case 4:
            printf("\n");
            printf("Numero de registos por pagina: ");
            scanf("%d", &linhasPorPagina);
            break;
        case 5:
            cloneCurrenciesArrayParam(sortedCurrencies);
            exchangeRates = cloneExchangeRatesArray(exchangeRatesOriginal, numRows);
            exchangeRates = sortExchangeRatesByCurrencyCode(exchangeRates, numRows, sortedCurrencies);
            sortedBy = 1;
            break;
        case 6:
            exchangeRates = cloneExchangeRatesArray(exchangeRatesOriginal, numRows);
            exchangeRates = sortExchangeRatesByValueInEuros(exchangeRates, numRows, sortedCurrencyNamesByDay);
            sortedBy = 2;
            break;
        case 7:
            cloneCurrenciesArrayParam(sortedCurrencies);
            exchangeRates = cloneExchangeRatesArray(exchangeRatesOriginal, numRows);
            sortedBy = 0;
            break;
        case 0:
            break;
        default:
            printf("\n");
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    free(sortedCurrencies);
    free(sortedCurrencyNamesByDay);
    free(exchangeRates);
}

int drawMenu(char *opcoes[], int numOpcoes, char *title)
{
    int key = 0;
    int option = 1;
    int i;

    do
    {
        system("cls");

        printf("\n  ********\t%s\t********\n", title);
        printf("  *                            *\n");
        for (i = 0; i < numOpcoes; i++)
        {
            printf("    %s %s\n", (option == i + 1) ? "-> [x]" : "   [ ]", opcoes[i]);
        }
        printf("  *                            *\n");
        printf("  ******************************\n");
        printf("Use as setas para selecionar uma opção. ENTER para confimar. ESC para sair.\n");
        key = getch();

        /*printf("\n   ******** Menu Principal ********\n");
        printf("   *                              *\n");
        printf("   * %s Opcao 1                   *\n", (option == 1) ? "->": "  ");
        printf("   * %s Opcao 2                   *\n", (option == 2) ? "->": "  ");
        printf("   *                              *\n");
        printf("   ********************************\n");*/

        if (key == KEY_ESC)
            return -1;

        if (key == KEY_UP)
        {
            if (option > 1)
                option--;
            else
                option = 1;
        }

        if (key == KEY_DOWN)
        {
            if (option < numOpcoes)
                option++;
            else
                option = numOpcoes;
        }

    } while (key != KEY_ENTER);

    return option;
}

/**
 * @brief Mostra um erro a vermelho na consola e espera que o utilizador clique ENTER para continuar ou ESC para cancelar a ação que estaria a fazer.
 * @param msg
 * 
 * @return false se o utilizador clicou ESC, true se clicou ENTER ou qq outra tecla
*/
bool handleError(char *msg)
{
    int key = 0;

    setTextRed();
    printf("\n%s.\n", msg);
    resetText();
    printf("\nClica em qualquer [ENTER] para continuar ou [ESC] para cancelar.");
    key = getch();

    if (key == KEY_ESC)
        return false;
    else if (key == KEY_ENTER)
        return true;
}

void setTextRed()
{
    printf("\033[1;31m");
}

void resetText()
{
    printf("\033[0m");
}
