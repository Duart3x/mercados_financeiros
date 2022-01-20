#include<stdio.h>
#include"utils.h"
#include"exchangeRates.h"

#ifndef GOODSTRANSACTIONS_H
#define GOODSTRANSACTIONS_H

#define MARKET_TYPES_NUMBER 5
typedef enum marketType{
    CRIPTO,STOCKS,BONDS,COMMODITIES,OTHER
} MARKETTYPE;

static const char MARKET_TYPE_STRINGS[MARKET_TYPES_NUMBER][20] = {
    "Cripto","Acoes","Titulos","Mercadorias","Outros"
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

typedef struct goodIdentifier 
{
    char name[50];
    CURRENCY currency;
    MARKETTYPE marketType;
} GOODIDENTIFIER;

typedef struct goodIdentifiersArray {
    GOODIDENTIFIER* identifiers;
    int count;
} GOODIDENTIFIERSARRAY;

typedef struct goodsInStudie {
    GOOD *goods;
    int count;
} GOODSINSTUDIE;


GOOD* newGoodQuestionaire(GOOD *goodTransactions, int *goodTransactionsRows);
GOOD * addGoodToArray(GOOD good, GOOD *goodTransactions, int *goodTransactionsRows);
void saveGoodsToFile(GOOD *goodTransactions, int *goodTransactionsRows);
bool checkIfGoodExistsAndUpdate(GOOD *goodTransactions, int goodTransactionsRows, GOOD good);
GOOD *readGoodsTransactionsFile(int *numRows);
GOOD *readGoodsTransactionsHistoryFile(FILE *f, int *numRows);
void listGoodsIndentifiers(GOOD *goodTransactions, int goodTransactionsRows);
void closeValueStatistics(GOOD *goodTransactions, int goodTransactionsRows);
void fiveGoodsWithMoreTransactions(GOOD *goodTransactions, int *goodTransactionsRows);
GOODSINSTUDIE getGoodBetweenDates(GOOD *goodTransactions, int goodTransactionsRows, DATE initial, DATE end);
GOODSINSTUDIE getSpecificGoodBetweenDates(GOOD *goodTransactions, int goodTransactionsRows, DATE initial, DATE end, GOODIDENTIFIERSARRAY goodIdentifiers, int identifierOption);

#endif