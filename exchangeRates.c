#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "utils.h"
#include"interface.h"
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
        char **V = Read_Split_Line_File(f, CURRENCIES_SIZE+1, &nCamposLidos, ",");

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
            if(compareDates(exchangeRates[middle].conversionDate, date) == 0)
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
            if(compareDates(exchangeRates[middle].conversionDate, date) == 0)
                return exchangeRates[middle];
            else
                return (EXCHANGERATE){};
        else
            return getExchangeRateByDate(exchangeRates + middle, numRows - middle, date);
    }
}

EXCHANGERATE *sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int from,int to,char** sortedCurrencies)
{
    EXCHANGERATE *result = malloc((to - from) * sizeof(EXCHANGERATE));
    int i = 0;

    sortCurrenciesQuickSort(sortedCurrencies, 0, CURRENCIES_SIZE - 1);

    for (i = 0; i < to-from; i++)
    {
        result[i] = sortExchangeRateByCurrencyCode(exchangeRates[from + i],sortedCurrencies);
    }

    return result;
}

EXCHANGERATE sortExchangeRateByCurrencyCode(EXCHANGERATE exchangeRate,char** sortedCurrencies)
{
    EXCHANGERATE result;
    if(!sortedCurrencies)
        sortCurrenciesQuickSort(sortedCurrencies, 0, CURRENCIES_SIZE - 1);
    
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

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        result.conversionDate.year = exchangeRate.conversionDate.year;
        result.conversionDate.month = exchangeRate.conversionDate.month;
        result.conversionDate.day = exchangeRate.conversionDate.day;

        result.currencies[positions[i]] = exchangeRate.currencies[i];
    }

    return result;
}

EXCHANGERATE *sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int from,int to, char*** sortedCurrencyNamesByDay)
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
    char* tempCurrencyName = malloc(4 * sizeof(char*));
    int k = 0;

    for (i = 0; i < (to-from); i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            strcpy(sortedCurrencyNamesByDay[i][j],CURRENCIES[j]);
        }
    }

    i = 0;
    j = 0;

    for (i = 0; i < (to-from); i++)
    {
        for (j = 0; j < CURRENCIES_SIZE; j++)
        {
            for (k = j+1; k < CURRENCIES_SIZE; k++)
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

EXCHANGERATE sortExchangeRatesByValueInEurosQuickSort(EXCHANGERATE exchangeRate, char** sortedCurrencyNamesByDay)
{
    EXCHANGERATE result;
    int i = 0, j = 0;
    double temp = 0;
    int k = 0;

    for (i = 0; i < CURRENCIES_SIZE; i++)
    {
        for (j = i+1; j < CURRENCIES_SIZE; j++)
        {
            if (exchangeRate.currencies[i] < exchangeRate.currencies[j])
            {
                temp = exchangeRate.currencies[i];
                exchangeRate.currencies[i] = exchangeRate.currencies[j];
                exchangeRate.currencies[j] = temp;
                strcpy(sortedCurrencyNamesByDay[i],CURRENCIES[j]);
            }
        }
    }


    return result;

}

double convertCurrenciesOnSpecificDay(EXCHANGERATE *exchangeRates, int numRows,DATE rateDate, CURRENCY from, double fromValue, CURRENCY to)
{    
    EXCHANGERATE rate = getExchangeRateByDate( exchangeRates,numRows,rateDate);
    if(rate.conversionDate.year == 0)
    {
        handleError("Nao foi possivel encontrar a cotacao do dia.");
        return -1;
    }
        
    double fromcurrencie = rate.currencies[from];
    double tocurrencie =rate.currencies[to];

    double Eur = fromValue/fromcurrencie;
    double convertedValue= Eur * tocurrencie;

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
    char temp[4];
    char* aux = malloc(4 * sizeof(char));


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

void cloneCurrenciesArrayParam(char** result)
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

EXCHANGERATE* cloneExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows)
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

EXCHANGERATE* clonePartOfExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows, int start, int end)
{
    EXCHANGERATE *result = (EXCHANGERATE *)malloc((end-start) * sizeof(EXCHANGERATE));
    if (!result)
        return NULL;
    int i = 0;

    for (i = 0; i < end-start; i++)
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

void chooseCurrenciesToConvert(){
    int currencyfrom=0, currencyto=0 ;
    int i=0;
     
        system("cls");
        char* opcoes[CURRENCIES_SIZE];

        for (i = 0; i < CURRENCIES_SIZE; i++)
        {
            opcoes[i] = CURRENCIES[i];
        }
        
        int op = drawMenu(opcoes, CURRENCIES_SIZE, "Selecione a unidade de moeda que pretende converter");

        if(op == -1) return;

        currencyfrom=op-1;

        int op2=drawMenu(opcoes, CURRENCIES_SIZE, "Selecione a unidade de moeda para qual vai converter");

        if(op2 == -1) return;
        currencyto=op2-1;

        
}