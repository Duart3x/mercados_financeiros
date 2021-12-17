#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"
#include"exchangeRates.h"
#include"interface.h"


int main(){
    
    EXCHANGERATE *exchangeRate;
    int linhasLidas;

    FILE* fp = openFile("files/exchangeRates.txt", "r");
    if(fp == NULL)
        return 1;

    exchangeRate = readExchangeRatesFile(fp, &linhasLidas);
    // drawExchangeRatesTable(exchangeRate, linhasLidas);

    free(exchangeRate);
    return 0;
}