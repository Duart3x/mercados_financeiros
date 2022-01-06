#include<stdio.h>
#include"utils.h"
#include"exchangeRates.h"

#ifndef GOODSTRANSACTIONS_H
#define GOODSTRANSACTIONS_H

#define MARKET_TYPES_NUMBER 5
typedef enum marketType{
    cripto,stocks,bonds,commodities,other
} MARKETTYPE;

static const char marketTypeStrings[MARKET_TYPES_NUMBER][15] = {
    "cripto","stocks","bonds","commodities","other"
};

typedef struct Good{
    char name[20];
    DATE obsDate;
    MARKETTYPE marketType;
    double openValue;
    double closeValue;
    double higherValue;
    double lowerValue;
    CURRENCY currency;
    int volume;
} GOOD;


void newGoodQuestionaire();
void addGoodToFile(GOOD good);
bool checkIfGoodExists(GOOD good);
void goodTransactionsMenu();

#endif