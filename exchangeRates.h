#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"

#ifndef EXCHANGERATES_H
#define EXCHANGERATES_H


#define CURRENCIES_SIZE 42

typedef struct exchangeRate
{
    DATE conversionDate;
    double currencies[CURRENCIES_SIZE];
} EXCHANGERATE;


typedef enum currency{
    EUR,USD,JPY,BGN,CYP,CZK,DKK,EEK,GBP,HUF,LTL,LVL,MTL,PLN,ROL,RON,SEK,SIT,SKK,CHF,ISK,NOK,HRK,RUB,TRL,TRY,AUD,BRL,CAD,CNY,HKD,IDR,ILS,INR,KRW,MXN,MYR,NZD,PHP,SGD,THB,ZAR
} CURRENCY;


static const char CURRENCIES[CURRENCIES_SIZE][4] = {"EUR","USD", "JPY", "BGN", "CYP", "CZK", "DKK", "EEK", "GBP", "HUF", "LTL", "LVL", "MTL", "PLN", "ROL", "RON", "SEK", "SIT", "SKK", "CHF", "ISK", "NOK", "HRK", "RUB", "TRL", "TRY", "AUD", "BRL", "CAD", "CNY", "HKD", "IDR", "ILS", "INR", "KRW", "MXN", "MYR", "NZD", "PHP", "SGD", "THB", "ZAR"};


EXCHANGERATE* readExchangeRatesFile(FILE* f, int* numRows);
EXCHANGERATE getExchangeRateByDate(EXCHANGERATE *exchangeRates, int left,int right, DATE date);
EXCHANGERATE getExchangeRateIndexByDate(EXCHANGERATE *exchangeRates, int left,int right, DATE date,int* index);
EXCHANGERATE *sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int from,int to,char** sortedCurrencies);
EXCHANGERATE *sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int from,int to, char*** sortedCurrencyNamesByDay);
EXCHANGERATE sortExchangeRateByCurrencyCode(EXCHANGERATE exchangeRate,char** sortedCurrencies);
char** sortCurrencies();
char **sortCurrenciesQuickSort(char **currencies, int left, int right);
char** cloneCurrenciesArray();
void cloneCurrenciesArrayParam(char** result);
EXCHANGERATE* cloneExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows);
EXCHANGERATE* clonePartOfExchangeRatesArray(EXCHANGERATE *exchangeRates, int numRows, int start, int end);
double convertCurrenciesOnSpecificDay(EXCHANGERATE *exchangeRates, int numRows,DATE rateDate, CURRENCY from, double fromValue, CURRENCY to);
void chooseCurrenciesToConvert(EXCHANGERATE *exchangeRates, int numRows);
void exportExchangeRatesToFile(EXCHANGERATE* exchangeRates, int numRows);


#endif