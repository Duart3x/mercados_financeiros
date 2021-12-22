#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "utils.h"
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
        char **V = Read_Split_Line_File(f, 42, &nCamposLidos, ",");

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
                    exchangeRate[n].currencies[i - 1] = atof(V[i]);
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
            return exchangeRates[middle];
        else
            return getExchangeRateByDate(exchangeRates, middle, date);
    }
    else
    {
        if (numRows == 1)
            return exchangeRates[middle];
        else
            return getExchangeRateByDate(exchangeRates + middle, numRows - middle, date);
    }
}

EXCHANGERATE *sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int numRows, char** sortedCurrencies)
{
    EXCHANGERATE *result = malloc(numRows * sizeof(EXCHANGERATE));
    sortedCurrencies = sortCurrenciesQuickSort(cloneCurrenciesArray(), 0, CURRENCIES_SIZE - 1);
    int positions[CURRENCIES_SIZE];
    int i= 0, j= 0;

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

    
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            result[i].conversionDate.year = exchangeRates[i].conversionDate.year;
            result[i].conversionDate.month = exchangeRates[i].conversionDate.month;
            result[i].conversionDate.day = exchangeRates[i].conversionDate.day;

            result[i].currencies[positions[j]] = exchangeRates[i].currencies[j];
        }
    }

    return result;
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
    char temp[4];


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
                char *aux = currencies[i];
                currencies[i] = currencies[j];
                currencies[j] = aux;
                i++;
                j--;
            }
        } while (i <= j);

        sortCurrenciesQuickSort(currencies, left, j);
        sortCurrenciesQuickSort(currencies, i, right);
    }

    return currencies;
}

char** cloneCurrenciesArray()
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


EXCHANGERATE *sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int numRows)
{
}