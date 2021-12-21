#include<stdio.h>
#include"utils.h"
#include"exchangeRates.h"

#ifndef GOODSTRANSACTIONS_H
#define GOODSTRANSACTIONS_H

typedef enum marketType{
    cripto,stocks,bonds,commodities,other
} MARKETTYPE;

typedef struct Good{
    DATE obsDate;
    MARKETTYPE marketType;
    char* name;
    double openValue;
    double closeValue;
    double higherValue;
    double lowerValue;
    CURRENCY currency;
    int volume;
} GOOD;


void newGoodQuestionaire();

#endif