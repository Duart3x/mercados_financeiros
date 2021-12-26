#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"

#ifndef EXCHANGERATES_H
#define EXCHANGERATES_H


#define CURRENCIES_SIZE 41

typedef struct exchangeRate
{
    DATE conversionDate;
    double currencies[CURRENCIES_SIZE];
} EXCHANGERATE;

typedef enum currency{
    USD,JPY,BGN,CYP,CZK,DKK,EEK,GBP,HUF,LTL,LVL,MTL,PLN,ROL,RON,SEK,SIT,SKK,CHF,ISK,NOK,HRK,RUB,TRL,TRY,AUD,BRL,CAD,CNY,HKD,IDR,ILS,INR,KRW,MXN,MYR,NZD,PHP,SGD,THB,ZAR
} CURRENCY;


static const char CURRENCIES[CURRENCIES_SIZE][4] = {"USD", "JPY", "BGN", "CYP", "CZK", "DKK", "EEK", "GBP", "HUF", "LTL", "LVL", "MTL", "PLN", "ROL", "RON", "SEK", "SIT", "SKK", "CHF", "ISK", "NOK", "HRK", "RUB", "TRL", "TRY", "AUD", "BRL", "CAD", "CNY", "HKD", "IDR", "ILS", "INR", "KRW", "MXN", "MYR", "NZD", "PHP", "SGD", "THB", "ZAR"};


EXCHANGERATE* readExchangeRatesFile(FILE* f, int* numRows);
EXCHANGERATE getExchangeRateByDate(EXCHANGERATE *exchangeRates, int numRows, DATE date);
EXCHANGERATE *sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int from,int to,char** sortedCurrencies);
EXCHANGERATE *sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int from,int to, char*** sortedCurrencyNamesByDay);
EXCHANGERATE sortExchangeRateByCurrencyCode(EXCHANGERATE exchangeRate,char** sortedCurrencies);
char** sortCurrencies();
char **sortCurrenciesQuickSort(char **currencies, int left, int right);
char** cloneCurrenciesArray();
void cloneCurrenciesArrayParam(char** result);
EXCHANGERATE* cloneExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows);
EXCHANGERATE* clonePartOfExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows, int start, int end);

#endif