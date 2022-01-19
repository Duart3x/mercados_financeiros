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
    int middle = ceil(CURRENCIES_SIZE / 3.0);
    printf("\n[%02d-%02d-%04d]\n", exchangeRate.conversionDate.day, exchangeRate.conversionDate.month, exchangeRate.conversionDate.year);

    float value1, value2, value3;
    char *strVal1 = malloc(sizeof(char) * 4);
    char *strVal2 = malloc(sizeof(char) * 4);
    char *strVal3 = malloc(sizeof(char) * 4);

    strVal1 = NULL;
    strVal2 = NULL;
    strVal3 = NULL;

    bool wasNull = false;
    if (currenciesText == NULL)
    {
        wasNull = true;
        currenciesText = cloneCurrenciesArray();
    }

    for (int j = 0; j < ceil(CURRENCIES_SIZE / 3.0); j++)
    {
        value1 = exchangeRate.currencies[j];
        value2 = exchangeRate.currencies[j + middle];
        value3 = exchangeRate.currencies[j + middle * 2];

        if (value1 == -1)
            strVal1 = "N/A";
        if (value2 == -1)
            strVal2 = "N/A";
        if (value3 == -1)
            strVal3 = "N/A";

        if (j + middle > CURRENCIES_SIZE - 1)
        {

            if (strVal1 != NULL)
                printf("\t%s = %s\n", currenciesText[j], strVal1);
            else
                printf("\t%s = %.02lf\n", currenciesText[j], value1);
        }
        else
        {
            if (strVal1 != NULL && strVal2 != NULL && strVal3 != NULL)
                printf("\t%s = %s\t%s = %s\t%s = %s\n", currenciesText[j], strVal1, currenciesText[j + middle], strVal2, currenciesText[j + middle * 2], strVal3);
            else if (strVal1 != NULL && strVal2 != NULL && strVal3 == NULL)
                printf("\t%s = %s\t%s = %s\t%s = %.02lf\n", currenciesText[j], strVal1, currenciesText[j + middle], strVal2, currenciesText[j + middle * 2], value3);
            else if (strVal1 != NULL && strVal2 == NULL && strVal3 != NULL)
                printf("\t%s = %s\t%s = %.02lf\t%s = %s\n", currenciesText[j], strVal1, currenciesText[j + middle], value2, currenciesText[j + middle * 2], strVal3);
            else if (strVal1 == NULL && strVal2 != NULL && strVal3 != NULL)
                printf("\t%s = %.02lf\t%s = %s\t%s = %s\n", currenciesText[j], value1, currenciesText[j + middle], strVal2, currenciesText[j + middle * 2], strVal3);
            else if (strVal1 != NULL && strVal2 == NULL && strVal3 == NULL)
                printf("\t%s = %s\t%s = %.02lf\t%s = %.02lf\n", currenciesText[j], strVal1, currenciesText[j + middle], value2, currenciesText[j + middle * 2], value3);
            else if (strVal1 == NULL && strVal2 != NULL && strVal3 == NULL)
                printf("\t%s = %.02lf\t%s = %s\t%s = %.02lf\n", currenciesText[j], value1, currenciesText[j + middle], strVal2, currenciesText[j + middle * 2], value3);
            else if (strVal1 == NULL && strVal2 == NULL && strVal3 != NULL)
                printf("\t%s = %.02lf\t%s = %.02lf\t%s = %s\n", currenciesText[j], value1, currenciesText[j + middle], value2, currenciesText[j + middle * 2], strVal3);
            else
                printf("\t%s = %.02lf\t%s = %.02lf\t%s = %.02lf\n", currenciesText[j], value1, currenciesText[j + middle], value2, currenciesText[j + middle * 2], value3);
        }

        strVal1 = NULL;
        strVal2 = NULL;
        strVal3 = NULL;
    }

    if (wasNull == true)
        free(currenciesText);

    free(strVal1);
    free(strVal2);
    free(strVal3);
}

void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char **sortedCurrencies)
{
    int i;
    printf("\n");

    for (i = 0; i < linhasPorPagina; i++)
    {
        if (i < numRows)
        {
            printf("-----------------------------------------------------\n");
            drawExchangeRate(exchangeRates[i], sortedCurrencies);
        }
    }
}

void drawExchangeRatesPaginationSortedByValue(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char ***sortedCurrencyNamesByDay)
{
    int i;
    printf("\n");

    for (i = 0; i < linhasPorPagina; i++)
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
    int linhasPorPagina = 2;
    int opcao = 0;
    int sortedBy = 0; // 0 = NOT SORTED, 1 = SORTED BY CURRENCY, 2 = SORTED BY VALUE
    char **sortedCurrencies = cloneCurrenciesArray();
    char ***sortedCurrencyNamesByDay = malloc(sizeof(char ***) * numRows);
    for (int i = 0; i < numRows; i++)
    {
        sortedCurrencyNamesByDay[i] = malloc(sizeof(char **) * CURRENCIES_SIZE);

        for (int j = 0; j < CURRENCIES_SIZE; j++)
        {
            sortedCurrencyNamesByDay[i][j] = malloc(sizeof(char) * 4);
        }
    }

    int i = 0;

    EXCHANGERATE *exchangeRates = cloneExchangeRatesArray(exchangeRatesOriginal, numRows);

    do
    {
        system("cls");
        exchangeRates = clonePartOfExchangeRatesArray(exchangeRatesOriginal, numRows, paginaAtual * linhasPorPagina, (paginaAtual * linhasPorPagina) + linhasPorPagina);

        switch (sortedBy)
        {
        case 1:
            cloneCurrenciesArrayParam(sortedCurrencies);
            exchangeRates = sortExchangeRatesByCurrencyCode(exchangeRates, 0, linhasPorPagina, sortedCurrencies);
            break;
        case 2:
            exchangeRates = sortExchangeRatesByValueInEuros(exchangeRates, paginaAtual * linhasPorPagina, (paginaAtual * linhasPorPagina) + linhasPorPagina, sortedCurrencyNamesByDay);
            break;
        }
        if (sortedBy == 2)
            drawExchangeRatesPaginationSortedByValue(exchangeRates, numRows, paginaAtual, linhasPorPagina, sortedCurrencyNamesByDay);
        else
            drawExchangeRatesPagination(exchangeRates, numRows, paginaAtual, linhasPorPagina, sortedCurrencies);
        printf("\n  Pagina %04d de %d\n", paginaAtual, (int)ceil((double)numRows / linhasPorPagina) - 1);
        printf("  %d registos por pagina\n", linhasPorPagina);

        printf("\n\n");
        printf("  \033[4mPaginacao\033[0m                                      \033[4mOrdenacao\033[0m\n");
        printf("  1 - Pagina anterior                            5 - Ordernar por ordem crescente do codigo da moeda\n");
        printf("  2 - Proxima pagina                             6 - Ordernar por ordem decrescente do valor em euros\n");
        printf("  3 - Escolher numero de pagina                  7 - Ordem original\n");
        printf("  4 - Escolher numero de registos por pagina     \n\n");
        printf("  0 - Voltar ao menu principal\n");
        printf("\n");
        printf("  \033[4mOpcao\033[0m: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (paginaAtual > 0)
                paginaAtual--;
            break;
        case 2:
            if (paginaAtual < (int)ceil((double)numRows / linhasPorPagina) - 1)
                paginaAtual++;
            break;
        case 3:
            printf("\n");
            printf("  Pagina: ");
            scanf("%d", &paginaAtual);
            break;
        case 4:
            printf("\n");
            printf("  Numero de registos por pagina: ");
            scanf("%d", &linhasPorPagina);
            break;
        case 5:
            sortedBy = 1;
            break;
        case 6:
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
    int biggerOption = 0;
    int i = 0;

    biggerOption = strlen(title);

    for (i = 0; i < numOpcoes; i++)
    {
        if (strlen(opcoes[i]) > biggerOption)
            biggerOption = strlen(opcoes[i]);
    }

    if (biggerOption == strlen(title))
        biggerOption += 10;

    do
    {
        system("cls");

        //printf("\n  ********     %s     ********\n\n", title);
        printf("\n  ");
        i = 0;
        for (i = 0; i < ceil(abs(((biggerOption + 14) - (strlen(title) + 10))) / 2.0); i++)
        {
            printf("*");
        }
        printf("     %s     ", title);
        i = 0;
        for (i = 0; i < abs(((biggerOption + 14) - (strlen(title) + 10))) / 2; i++)
        {
            printf("*");
        }
        printf("\n\n");

        i = 0;
        for (i = 0; i < numOpcoes; i++)
        {
            printf("    %s %s\n", (option == i + 1) ? "   \033[37;1m[\033[31;1mx\033[0m]\033[37;1m\033[0m" : "   \033[30;1m[ ]\033[0m", opcoes[i]);
        }
        printf("\n  ");
        i = 0;
        for (i = 0; i < 14 + biggerOption; i++)
        {
            printf("*");
        }

        printf("\n  Use as setas para selecionar uma opcao. ENTER para confimar. ESC para sair.\n");
        key = getch();
        fflush(stdin);

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

int drawCurrenciesMenu(char *title, int *selectedCurrencies, int length)
{
    int key = 0;
    int option = 1;
    int i = 0;
    int middle = ceil(CURRENCIES_SIZE / 3.0);

    do
    {
        system("cls");

        printf("\n  ********     \033[4m%s\033[0m     ********\n\n", title);

        i = 0;
        for (i = 0; i < ceil(CURRENCIES_SIZE / 3.0); i++)
        {
            printf("    %s %s      %s %s      %s %s\n",
                   (option == i + 1) ? "   \033[37;1m[\033[31;1mx\033[0m]\033[37;1m\033[0m" : (checkIfArrayContainsElement(selectedCurrencies, length, i + 1) == true) ? "   \033[31;1m[O]\033[0m"
                                                                                                                                                                       : "   \033[30;1m[ ]\033[0m",
                   CURRENCIES[i],
                   (option == i + middle + 1) ? "   \033[37;1m[\033[31;1mx\033[0m]\033[37;1m\033[0m" : (checkIfArrayContainsElement(selectedCurrencies, length, i + middle + 1) == true) ? "   \033[31;1m[O]\033[0m"
                                                                                                                                                                                         : "   \033[30;1m[ ]\033[0m",
                   CURRENCIES[i + middle],
                   (option == i + middle + middle + 1) ? "   \033[37;1m[\033[31;1mx\033[0m]\033[37;1m\033[0m" : (checkIfArrayContainsElement(selectedCurrencies, length, i + middle + middle + 1) == true) ? "   \033[31;1m[O]\033[0m"
                                                                                                                                                                                                           : "   \033[30;1m[ ]\033[0m",
                   CURRENCIES[i + middle + middle]);
        }

        printf("\n  Use as setas para selecionar uma opcao. ENTER para confimar. ESC para sair.\n");
        key = getch();
        fflush(stdin);

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
            if (option < CURRENCIES_SIZE)
                option++;
            else
                option = CURRENCIES_SIZE;
        }

        if (key == KEY_LEFT)
        {
            if (option > middle)
                option -= middle;
            else
                option = 1;
        }

        if (key == KEY_RIGHT)
        {
            if (option < middle * 2)
                option += middle;
            else
                option = CURRENCIES_SIZE;
        }

    } while (key != KEY_ENTER);

    return option;
}

/**
 * 
 * @returns 1 se o utilizador quiser o ficheiro externo, 2 se o utilizador quiser o ficheiro interno
*/
int askFileToUse(int numGoodTransactionsRows, int numGoodsRows)
{

    char opcao1[40] = "Ficheiro Externo (";
    char *numGoodsRowsStr = malloc(sizeof(char) * 10);
    ;
    itoa(numGoodsRows, numGoodsRowsStr, 10);
    strcat(opcao1, numGoodsRowsStr);
    strcat(opcao1, " linhas)");

    char opcao2[40] = "Ficheiro Interno (";
    char *numGoodTransactionsRowsStr = malloc(sizeof(char) * 10);
    itoa(numGoodTransactionsRows, numGoodTransactionsRowsStr, 10);
    strcat(opcao2, numGoodTransactionsRowsStr);
    strcat(opcao2, " linhas)");

    char **opcoes = malloc(sizeof(char *) * 2);
    opcoes[0] = malloc(sizeof(char) * 40);
    opcoes[1] = malloc(sizeof(char) * 40);
    strcpy(opcoes[0], opcao1);
    strcpy(opcoes[1], opcao2);

    return drawMenu(opcoes, 2, "Qual ficheiro deseja abrir?");
}

/**
 * @brief Mostra um erro a vermelho na consola e espera que o utilizador clique ENTER para continuar ou ESC para cancelar a acao que estaria a fazer.
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

void printColoredText(char *msg, COLORS color)
{
    printf("\033%s %s \033%s", COLOR_CODES[color], msg, COLOR_CODES[RESET]);
}

void printExchangeRateByDateAndCurrency(EXCHANGERATE *exchangeRates, int numRows)
{
    bool quitMenu = false, repeat = false, isValid = false;
    char *SNOptions[] = {"Sim", "Nao"};
    int sn = 0;
    int moeda = -1;
    char dateStr[15];
    DATE date;
    EXCHANGERATE rate;
    double fromRate = 0, toRate = 0;

    do
    {
        quitMenu = false;
        isValid = false;
        repeat = false;
        system("cls");

        while (!isValid && !quitMenu)
        {
            isValid = true;
            system("cls");
            printf("\n  \033[4mConsultar Taxa de Cambio\033[0m\n");
            printf("  Data a consultar (dd/mm/yyyy): ");
            scanf("%s", dateStr);

            date = isDateValid(dateStr);

            if (date.year == 0)
            {
                quitMenu = !handleError("  Data inválida.");

                isValid = false;
            }
            else
            {
                rate = getExchangeRateByDate(exchangeRates, 0,numRows-1, date);

                if (rate.conversionDate.year == 0)
                {
                    quitMenu = !handleError("  Nao existem dados para a data introduzida.");

                    isValid = false;
                }
                else
                    isValid = true;
            }
        }

        if (quitMenu)
            return;

        isValid = false;

        while (!quitMenu && !isValid)
        {
            isValid = true;
            moeda = drawCurrenciesMenu("Moeda a Consultar", (int[]){}, 0);

            if (moeda == -1)
                return;

            moeda--;

            if (rate.currencies[moeda] == -1)
            {
                quitMenu = !handleError("  Nao existem dados para a moeda introduzida.");

                isValid = false;
            }
        }

        if (quitMenu)
            return;

        int middle = CURRENCIES_SIZE / 3.0;
        fromRate = 1 / rate.currencies[moeda];
        system("cls");
        printf("\n  \033[4mTaxa Cambio\033[0m:  [%02d-%02d-%04d]\n\n", rate.conversionDate.day, rate.conversionDate.month, rate.conversionDate.year);
        printf("  \033[4m1 %s\033[0m:\n", CURRENCIES[moeda]);

        float value1, value2, value3;
        char *strVal1 = malloc(sizeof(char) * 4);
        char *strVal2 = malloc(sizeof(char) * 4);
        char *strVal3 = malloc(sizeof(char) * 4);

        strVal1 = NULL;
        strVal2 = NULL;
        strVal3 = NULL;

        bool wasNull = false;

        for (int j = 0; j < ceil(CURRENCIES_SIZE / 3.0); j++)
        {
            value1 = rate.currencies[j] * fromRate;
            value2 = rate.currencies[j + middle] * fromRate;
            value3 = rate.currencies[j + middle * 2] * fromRate;

            if (value1 < 0)
                strVal1 = "N/A";
            if (value2 < 0)
                strVal2 = "N/A";
            if (value3 < 0)
                strVal3 = "N/A";

            if (j + middle > CURRENCIES_SIZE - 1)
            {

                if (strVal1 != NULL)
                    printf("\t%s = %s\n", CURRENCIES[j], strVal1);
                else
                    printf("\t%s = %.02lf\n", CURRENCIES[j], value1);
            }
            else
            {
                if (strVal1 != NULL && strVal2 != NULL && strVal3 != NULL)
                    printf("\t%s = %s\t%s = %s\t%s = %s\n", CURRENCIES[j], strVal1, CURRENCIES[j + middle], strVal2, CURRENCIES[j + middle * 2], strVal3);
                else if (strVal1 != NULL && strVal2 != NULL && strVal3 == NULL)
                    printf("\t%s = %s\t%s = %s\t%s = %.04lf\n", CURRENCIES[j], strVal1, CURRENCIES[j + middle], strVal2, CURRENCIES[j + middle * 2], value3);
                else if (strVal1 != NULL && strVal2 == NULL && strVal3 != NULL)
                    printf("\t%s = %s\t%s = %.04lf\t%s = %s\n", CURRENCIES[j], strVal1, CURRENCIES[j + middle], value2, CURRENCIES[j + middle * 2], strVal3);
                else if (strVal1 == NULL && strVal2 != NULL && strVal3 != NULL)
                    printf("\t%s = %.04lf\t%s = %s\t%s = %s\n", CURRENCIES[j], value1, CURRENCIES[j + middle], strVal2, CURRENCIES[j + middle * 2], strVal3);
                else if (strVal1 != NULL && strVal2 == NULL && strVal3 == NULL)
                    printf("\t%s = %s\t%s = %.04lf\t%s = %.04lf\n", CURRENCIES[j], strVal1, CURRENCIES[j + middle], value2, CURRENCIES[j + middle * 2], value3);
                else if (strVal1 == NULL && strVal2 != NULL && strVal3 == NULL)
                    printf("\t%s = %.04lf\t%s = %s\t%s = %.04lf\n", CURRENCIES[j], value1, CURRENCIES[j + middle], strVal2, CURRENCIES[j + middle * 2], value3);
                else if (strVal1 == NULL && strVal2 == NULL && strVal3 != NULL)
                    printf("\t%s = %.04lf\t%s = %.04lf\t%s = %s\n", CURRENCIES[j], value1, CURRENCIES[j + middle], value2, CURRENCIES[j + middle * 2], strVal3);
                else
                    printf("\t%s = %.04lf\t%s = %.04lf\t%s = %.04lf\n", CURRENCIES[j], value1, CURRENCIES[j + middle], value2, CURRENCIES[j + middle * 2], value3);
            }

            strVal1 = NULL;
            strVal2 = NULL;
            strVal3 = NULL;
        }

        free(strVal1);
        free(strVal2);
        free(strVal3);

        printf("\n \033[7mPressione qualquer tecla para continuar...\033[0m");
        getch();

        sn = drawMenu(SNOptions, 2, "Deseja tentar uma outra data?");

        if (sn == 1)
            repeat = true;
        else
            repeat = false;
    } while (repeat);
}