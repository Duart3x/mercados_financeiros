#include<stdio.h>
#include"utils.h"
#include"exchangeRates.h"

#ifndef GOODSTRANSACTIONS_H
#define GOODSTRANSACTIONS_H

#define MARKET_TYPES_NUMBER 5
typedef enum marketType{
    CRIPTO,STOCKS,BONDS,COMMODITIES,OTHER
} MARKETTYPE;

static const char MARKET_TYPE_STRINGS[MARKET_TYPES_NUMBER][15] = {
    "Cripto","Stocks","Bonds","Commodities","Other"
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
GOOD *readGoodsTransactionsFile();
GOOD *readGoodsTransactionsHistoryFile(FILE *f, int *numRows);


#endif