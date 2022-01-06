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
    DATE obsDate;
    char name[20];
    double openValue;
    double closeValue;
    double higherValue;
    double lowerValue;
    int volume;
    MARKETTYPE marketType;
    CURRENCY currency;
} GOOD;


void newGoodQuestionaire();
void addGoodToFile(GOOD good);
bool checkIfGoodExistsAndUpdate(GOOD good);
void goodTransactionsMenu();
GOOD *readGoodTransactionsFile();

#endif