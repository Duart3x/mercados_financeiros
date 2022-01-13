#include "exchangeRates.h"
#include "utils.h"

#ifndef INTERFACE_H
#define INTERFACE_H
#define COLORS_SIZE 17
typedef enum colors
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_YELLOW,
    LIGHT_BLUE,
    LIGHT_MAGENTA,
    LIGHT_CYAN,
    WHITE,
    RESET
} COLORS;

static const char COLOR_CODES[COLORS_SIZE][5] = {"[30m", "[31m", "[32m", "[33m", "[34m", "[35m", "[36m", "[37m", "[90m", "[91m", "[92m", "[93m", "[94m", "[95m", "[96m", "[97m", "[0m"};

void drawExchangeRatesTable(EXCHANGERATE *exchangeRate, int numRows);
void drawExchangeRates(EXCHANGERATE *exchangeRates, int numRows);
void drawExchangeRate(EXCHANGERATE exchangeRate, char **sortedCurrencies);
void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char **sortedCurrencies);
void drawExchangeRatesPaginationSortedByValue(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina, char ***sortedCurrencyNamesByDay);
void menuWithExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows);
int drawMenu(char *opcoes[], int numOpcoes, char *title);
bool handleError(char *msg);
int askFileToUse(int numGoodTransactionsRows,int numGoodsRows);
void setTextRed();
void resetText();
void printColoredText(char* msg, COLORS color);


#endif