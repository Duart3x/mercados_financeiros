#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"

#ifndef EXCHANGERATES_H
#define EXCHANGERATES_H


#define EXCHANGES_SIZE 41

typedef struct exchangeRate
{
    DATE conversionDate;
    double currencies[EXCHANGES_SIZE];
} EXCHANGERATE;

typedef enum currency{
    USD,JPY,BGN,CYP,CZK,DKK,EEK,GBP,HUF,LTL,LVL,MTL,PLN,ROL,RON,SEK,SIT,SKK,CHF,ISK,NOK,HRK,RUB,TRL,TRY,AUD,BRL,CAD,CNY,HKD,IDR,ILS,INR,KRW,MXN,MYR,NZD,PHP,SGD,THB,ZAR
} CURRENCY;


static const char EXCHANGES[EXCHANGES_SIZE][4] = {"USD", "JPY", "BGN", "CYP", "CZK", "DKK", "EEK", "GBP", "HUF", "LTL", "LVL", "MTL", "PLN", "ROL", "RON", "SEK", "SIT", "SKK", "CHF", "ISK", "NOK", "HRK", "RUB", "TRL", "TRY", "AUD", "BRL", "CAD", "CNY", "HKD", "IDR", "ILS", "INR", "KRW", "MXN", "MYR", "NZD", "PHP", "SGD", "THB", "ZAR"};


EXCHANGERATE* readExchangeRatesFile(FILE* f, int* linhasLidas);
EXCHANGERATE getExchangeRateByDate(EXCHANGERATE *exchangeRates, int linhasLidas, DATE date);
EXCHANGERATE* sortExchangeRatesByCurrencyCode(EXCHANGERATE *exchangeRates, int linhasLidas);
EXCHANGERATE* sortExchangeRatesByValueInEuros(EXCHANGERATE *exchangeRates, int linhasLidas);

#endif