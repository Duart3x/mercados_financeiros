#include"exchangeRates.h"

#ifndef INTERFACE_H
#define INTERFACE_H

void drawExchangeRatesTable(EXCHANGERATE *exchangeRate, int linhasLidas);
void drawExchangeRates(EXCHANGERATE *exchangeRates, int linhasLidas);
void drawExchangeRate(EXCHANGERATE exchangeRate);
void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int linhasLidas, int paginaAtual, int linhasPorPagina);
void menuWithExchangeRatesPagination(EXCHANGERATE *exchangeRates, int linhasLidas);
int drawMenu(char *opcoes[], int numOpcoes, char *title);

#endif