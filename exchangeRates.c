#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#include "utils.h"
#include "interface.h"
#include "exchangeRates.h"

EXCHANGERATE *readExchangeRatesFile(FILE *f, int *numRows)
{
    EXCHANGERATE *exchangeRate;
    int nCamposLidos;
    int linhasFicheiro = 0;
    int n = 0;

    linhasFicheiro = getNumberOfLinesInFile(f);

    exchangeRate = (EXCHANGERATE *)malloc(linhasFicheiro * sizeof(EXCHANGERATE));

    while (!feof(f))
    {
        char **V = Read_Split_Line_File(f, CURRENCIES_SIZE + 1, &nCamposLidos, ",");

        for (int i = 0; i < nCamposLidos; i++)
        {
            if (i == 0)
            {
                char *date = strtok(V[i], "-");
                exchangeRate[n].conversionDate.year = atoi(date);

                date = strtok(NULL, "-");
                exchangeRate[n].conversionDate.month = atoi(date);

                date = strtok(NULL, "-");
                exchangeRate[n].conversionDate.day = atoi(date);
            }
            else
            {
                if (strcmp(V[i], "N/A") == 0)
                    exchangeRate[n].currencies[i - 1] = -1;
                else
                    exchangeRate[n].currencies[i - 1] = atof(replaceChar(V[i], '.', ','));
            }
        }

        for (int i = 0; i < nCamposLidos; i++)
            free(V[i]);
        free(V);
        n++;
    }
    fclose(f);
    *numRows = n;

    return exchangeRate;
}

EXCHANGERATE getExchangeRateByDate(EXCHANGERATE *exchangeRates, int numRows, DATE date)
{
    EXCHANGERATE exchangeRate;
    int middle = numRows / 2;

    if (compareDates(exchangeRates[middle].conversionDate, date) == 0)
        return exchangeRates[middle];
    else if (compareDates(exchangeRates[middle].conversionDate, date) == -1)
    {
        if (numRows == 1)
        {
            if (compareDates(exchangeRates[middle].conversionDate, date) == 0)
                return exchangeRates[middle];
            else
                return (EXCHANGERATE){};
        }
        else
            return getExchangeRateByDate(exchangeRates, middle, date);
    }
    else
    {
        if (numRows == 1)
            if (compareDates(exchangeRates[middle].conversionDate, date) == 0)
                return exchangeRates[middle];
            else
                return (EXCHANGERATE){};
        else
            return getExchangeRateByDate(exchangeRates + middle, numRows - middle, date);
    }
}

EXCHANGERATE *sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int from, int to, char **sortedCurrencies)
{
    EXCHANGERATE *result = malloc((to - from) * sizeof(EXCHANGERATE));
    int i = 0;

    sortCurrenciesQuickSort(sortedCurrencies, 0, CURRENCIES_SIZE - 1);

    for (i = 0; i < to - from; i++)
    {
        result[i] = sortExchangeRateByCurrencyCode(exchangeRates[from + i], sortedCurrencies);
    }

    return result;
}

EXCHANGERATE sortExchangeRateByCurrencyCode(EXCHANGERATE exchangeRate, char **sortedCurrencies)
{
    EXCHANGERATE result;
    if (!sortedCurrencies)
        sortCurrenciesQuickSort(sortedCurrencies, 0, CURRENCIES_SIZE - 1);

    int positions[CURRENCIES_SIZE];
    int i = 0, j = 0;

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            if (strcmp(sortedCurrencies[i], CURRENCIES[j]) == 0)
            {
                positions[j] = i;
                break;
            }
        }
    }

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        result.conversionDate.year = exchangeRate.conversionDate.year;
        result.conversionDate.month = exchangeRate.conversionDate.month;
        result.conversionDate.day = exchangeRate.conversionDate.day;

        result.currencies[positions[i]] = exchangeRate.currencies[i];
    }

    return result;
}

EXCHANGERATE *sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int from, int to, char ***sortedCurrencyNamesByDay)
{
    EXCHANGERATE *result = exchangeRates;

    if (!result)
    {
        handleError("Nao foi possivel ordernar o array.");
        return exchangeRates;
    }

    int i = 0;
    int j = 0;
    double temp = 0;
    char *tempCurrencyName = malloc(4 * sizeof(char *));
    int k = 0;

    for (i = 0; i < (to - from); i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            strcpy(sortedCurrencyNamesByDay[i][j], CURRENCIES[j]);
        }
    }

    i = 0;
    j = 0;

    for (i = 0; i < (to - from); i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            for (k = j + 1; k < CURRENCIES_SIZE; k++)
            {
                if (result[i].currencies[j] < result[i].currencies[k])
                {
                    temp = result[i].currencies[j];
                    result[i].currencies[j] = result[i].currencies[k];
                    result[i].currencies[k] = temp;
                    strcpy(tempCurrencyName, sortedCurrencyNamesByDay[i][j]);
                    strcpy(sortedCurrencyNamesByDay[i][j], sortedCurrencyNamesByDay[i][k]);
                    strcpy(sortedCurrencyNamesByDay[i][k], tempCurrencyName);
                }
            }
        }

        result[i].conversionDate.year = exchangeRates[i].conversionDate.year;
        result[i].conversionDate.month = exchangeRates[i].conversionDate.month;
        result[i].conversionDate.day = exchangeRates[i].conversionDate.day;
    }

    return result;
}

EXCHANGERATE sortExchangeRatesByValueInEurosQuickSort(EXCHANGERATE exchangeRate, char **sortedCurrencyNamesByDay)
{
    EXCHANGERATE result;
    int i = 0, j = 0;
    double temp = 0;
    int k = 0;

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        for (j = i + 1; j < CURRENCIES_SIZE; j++)
        {
            if (exchangeRate.currencies[i] < exchangeRate.currencies[j])
            {
                temp = exchangeRate.currencies[i];
                exchangeRate.currencies[i] = exchangeRate.currencies[j];
                exchangeRate.currencies[j] = temp;
                strcpy(sortedCurrencyNamesByDay[i], CURRENCIES[j]);
            }
        }
    }

    return result;
}
/**
 * @brief 
 * 
 * @param exchangeRates 
 * @param numRows 
 * @param rateDate 
 * @param from 
 * @param fromValue 
 * @param to 
 * @return -1 se nao existir taxa de conversao de moeda origem | -2 se nao existir taxa de conversao de moeda pretendida | -3 se nao existir conversões na data especificada 
 */
double convertCurrenciesOnSpecificDay(EXCHANGERATE *exchangeRates, int numRows, DATE rateDate, CURRENCY from, double fromValue, CURRENCY to)
{
    EXCHANGERATE rate = getExchangeRateByDate(exchangeRates, numRows, rateDate);
    if (rate.conversionDate.year == 0)
        return -3;

    double fromcurrencie = rate.currencies[from];
    double tocurrencie = rate.currencies[to];

    if (fromcurrencie == -1)
        return -1;
    else if (tocurrencie == -1)
        return -2;

    double Eur = fromValue / fromcurrencie;
    double convertedValue = Eur * tocurrencie;

    return convertedValue;
}

// Buble Sort
char **sortCurrencies()
{
    char **result = cloneCurrenciesArray();
    int i = 0;
    int j = 0;

    // sort CURRENCIES array alphabetically A-Z and save it in result
    char temp[4];
    i = 0;
    j = 0;
    for (i = 0; i <= CURRENCIES_SIZE; i++)
        for (j = i + 1; j <= CURRENCIES_SIZE - 1; j++)
        {
            if (strcmp(result[i], result[j]) > 0)
            {
                strcpy(temp, result[i]);
                strcpy(result[i], result[j]);
                strcpy(result[j], temp);
            }
        }

    return result;
}

// replicate sortCurrencies() but with the Quick Sort algorithm
char **sortCurrenciesQuickSort(char **currencies, int left, int right)
{
    int i = 0;
    int j = 0;
    char temp[80];
    char *aux = malloc(80 * sizeof(char));

    if (left < right)
    {
        i = left;
        j = right;
        strcpy(temp, currencies[(left + right) / 2]);

        do
        {
            while (strcmp(currencies[i], temp) < 0)
                i++;
            while (strcmp(currencies[j], temp) > 0)
                j--;

            if (i <= j)
            {
                strcpy(aux, currencies[i]);
                strcpy(currencies[i], currencies[j]);
                strcpy(currencies[j], aux);
                i++;
                j--;
            }
        } while (i <= j);

        sortCurrenciesQuickSort(currencies, left, j);
        sortCurrenciesQuickSort(currencies, i, right);
    }

    return currencies;
}

char **cloneCurrenciesArray()
{
    char **result = (char **)malloc(CURRENCIES_SIZE * sizeof(char *));
    if (!result)
        return NULL;
    int i = 0;

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        result[i] = malloc(4 * sizeof(char));
        strcpy(result[i], CURRENCIES[i]);
        if (!result[i])
        {
            free(result);
            return NULL;
        }
    }

    return result;
}

void cloneCurrenciesArrayParam(char **result)
{
    int i = 0;

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        strcpy(result[i], CURRENCIES[i]);
        if (!result[i])
        {
            free(result);
        }
    }
}

EXCHANGERATE *cloneExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows)
{
    EXCHANGERATE *result = (EXCHANGERATE *)malloc(numRows * sizeof(EXCHANGERATE));
    if (!result)
        return NULL;
    int i = 0;

    for (i = 0; i < numRows; i++)
    {
        result[i].conversionDate.year = exchangeRates[i].conversionDate.year;
        result[i].conversionDate.month = exchangeRates[i].conversionDate.month;
        result[i].conversionDate.day = exchangeRates[i].conversionDate.day;

        for (int j = 0; j < CURRENCIES_SIZE; j++)
        {
            result[i].currencies[j] = exchangeRates[i].currencies[j];
        }
    }

    return result;
}

EXCHANGERATE *clonePartOfExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows, int start, int end)
{
    EXCHANGERATE *result = (EXCHANGERATE *)malloc((end - start) * sizeof(EXCHANGERATE));
    if (!result)
        return NULL;
    int i = 0;

    for (i = 0; i < end - start; i++)
    {
        result[i].conversionDate.year = exchangeRates[start + i].conversionDate.year;
        result[i].conversionDate.month = exchangeRates[start + i].conversionDate.month;
        result[i].conversionDate.day = exchangeRates[start + i].conversionDate.day;

        for (int j = 0; j < CURRENCIES_SIZE; j++)
        {
            result[i].currencies[j] = exchangeRates[start + i].currencies[j];
        }
    }

    return result;
}

void chooseCurrenciesToConvert(EXCHANGERATE *exchangeRates, int numRows)
{
    int currencyFrom = 0, currencyTo = 0;
    char value[20];
    char strData[15];
    double fromValue, convertedValue;
    bool quitMenu = false, isValid = false, repeat = false;
    DATE data;
    int strLenData;
    int i = 0;

    int *selectedCurrencies = (int *)malloc(2 * sizeof(int));

    do
    {
        quitMenu = false;
        isValid = false;
        repeat = false;
        system("cls");
        //int op = drawMenu(opcoes, CURRENCIES_SIZE, "Selecione a unidade de moeda que pretende converter");
        int op = drawCurrenciesMenu("Selecione a moeda de origem", selectedCurrencies, 0);

        if (op == -1)
            return;

        currencyFrom = op - 1;
        selectedCurrencies[0] = op;

        //int op2=drawMenu(opcoes, CURRENCIES_SIZE, "Selecione a unidade de moeda para qual vai converter");

        int op2 = 0;
        do
        {
            op2 = drawCurrenciesMenu("Selecione a moeda pretendida", selectedCurrencies, 1);
            if (op2 == op)
            {
                quitMenu = !handleError("Nao pode selecionar a mesma moeda");
            }

        } while (op2 == op && !quitMenu);

        if (op2 == -1)
            return;
        currencyTo = op2 - 1;

        while (!quitMenu)
        {
            system("cls");
            printf("Moeda origem: %s\n", CURRENCIES[currencyFrom]);
            printf("Moeda pretendida: %s\n", CURRENCIES[currencyTo]);
            printf("Valor que prentende converter: ");
            fflush(stdin);
            scanf("%s", value);
            fflush(stdin);
            if (!isNumber(value))
            {
                quitMenu = !handleError("Valor introduzido invalido");
            }
            else
            {

                fromValue = atof(replaceChar(value, '.', ','));
                break;
            }
        }

        i = 0;
        while (!isValid && !quitMenu)
        {
            isValid = true;
            system("cls");
            printf("Valor a converter: %.02lf %s \n", fromValue, CURRENCIES[currencyFrom]);
            printf("Moeda pretendida: %s\n", CURRENCIES[currencyTo]);
            printf("Identificacao da data de observacao (dd/MM/aaaa): ");
            fflush(stdin);
            scanf("%s", strData);
            fflush(stdin);
            strLenData = strlen(strData);
            if (strLenData == 0 || strLenData > 10)
            {
                quitMenu = !handleError("Data Invalida");

                isValid = false;
            }
            else if(strcspn(strData, "/") == strLenData)
            {
                isValid = !handleError("Data Invalida");
            }
            else
            {

                char *aux;
                aux = strtok(strData, "/");
                i = 0;
                while (aux != NULL)
                {
                    if (i == 0)
                    {
                        if (strlen(aux) <= 2)
                        {
                            data.day = atoi(aux);
                        }
                        else
                        {
                            quitMenu = !handleError("Data Invalida");

                            isValid = false;
                            break;
                        }
                    }
                    else if (i == 1)
                    {
                        if (strlen(aux) <= 2)
                        {
                            data.month = atoi(aux);
                        }
                        else
                        {
                            quitMenu = !handleError("Data Invalida");

                            isValid = false;
                            break;
                        }
                    }
                    else if (i == 2)
                    {
                        if (strlen(aux) == 4)
                        {
                            data.year = atoi(aux);
                        }
                        else
                        {
                            quitMenu = !handleError("Data Invalida");

                            isValid = false;
                            break;
                        }
                    }

                    aux = strtok(NULL, "/");
                    i++;
                }
            
            }

            if (isValid)
            {
                if (data.day < 1 || data.day > 31)
                {
                    quitMenu = !handleError("Data Invalida");

                    isValid = false;
                }
                else if (data.month < 1 || data.month > 12)
                {
                    quitMenu = !handleError("Data Invalida");

                    isValid = false;
                }
                else if (data.year < 999 || data.year > 9999)
                {
                    quitMenu = !handleError("Data Invalida");

                    isValid = false;
                }
            }
        }
        if (quitMenu)
            return;

        convertedValue = convertCurrenciesOnSpecificDay(exchangeRates, numRows, data, currencyFrom, fromValue, currencyTo);
        if (convertedValue == -1)
        {
            quitMenu = !handleError("Nao existe taxa de conversao para a moeda de origem");
        }
        else if (convertedValue == -2)
        {
            quitMenu = !handleError("Nao existe taxa de conversao para a moeda pretendida");
        }
        else if (convertedValue == -3)
        {
            quitMenu = !handleError("Nao existe taxa de conversao na data especificada");
        }
        else
        {
            system("cls");
            printf("\n \033[4mConversao\033[0m\n %.02lf %s -> %.02lf %s\n", fromValue, CURRENCIES[currencyFrom], convertedValue, CURRENCIES[currencyTo]);
            printf("\n \033[4mTaxas de Conversao\033[0m\n");
            printf(" 1 %s = %.04f %s\n", CURRENCIES[currencyFrom], (convertedValue / fromValue), CURRENCIES[currencyTo]);
            printf(" 1 %s = %.04f %s\n", CURRENCIES[currencyTo], (fromValue / convertedValue), CURRENCIES[currencyFrom]);
            printf("\n \033[7mPressione qualquer tecla para continuar...\033[0m");
            getch();
        }

        int sn = 0;
        char *opcao[] = {"Sim", "Nao"};

        sn = drawMenu(opcao, 2, "Deseja fazer uma nova conversao?");

        if (sn == 1)
        {
            repeat = true;
        }
        else
        {
            repeat = false;
        }

    } while (repeat);
}
