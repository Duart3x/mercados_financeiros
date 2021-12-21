#include"exchangeRates.h"
#include"utils.h"

#ifndef INTERFACE_H
#define INTERFACE_H

void drawExchangeRatesTable(EXCHANGERATE *exchangeRate, int numRows);
void drawExchangeRates(EXCHANGERATE *exchangeRates, int numRows);
void drawExchangeRate(EXCHANGERATE exchangeRate);
void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows, int paginaAtual, int linhasPorPagina);
void menuWithExchangeRatesPagination(EXCHANGERATE *exchangeRates, int numRows);
int drawMenu(char *opcoes[], int numOpcoes, char *title);
bool handleError(char *msg);
void setTextRed();
void resetText();

#endif