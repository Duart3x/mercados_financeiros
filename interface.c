#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"
#include"exchangeRates.h"

void drawExchangeRatesTable(EXCHANGERATE *exchangeRate, int linhasLidas)
{
    /**
     * Draw table with | and - characters
     * put a header row with: Data | USD | JPY | BGN | CYP | CZK | DKK | EEK | GBP | HUF | LTL | LVL | MTL | PLN | ROL | RON | SEK | SIT | SKK | CHF | ISK | NOK | HRK | RUB | TRL | TRY | AUD | BRL | CAD | CNY | HKD | IDR | ILS | INR | KRW | MXN | MYR | NZD | PHP | SGD | THB | ZAR
     * put fill the rest of the table with the exchangeRate values
    */
   
   /* int i;
    printf("\n");
    printf("| Data       |");
    for(i = 0; i < EXCHANGES_SIZE; i++)
        printf("  %s   |", EXCHANGES[i]);
    printf("\n");
    printf("|");
    for(i = 0; i < 28; i++)
        printf("---------");
    printf("|\n");

    for(i = 0; i < linhasLidas; i++)
    {
        printf("| %02d-%02d-%02d |", exchangeRate[i].conversionDate.day, exchangeRate[i].conversionDate.month, exchangeRate[i].conversionDate.year);
        for(int j = 0; j < EXCHANGES_SIZE; j++)
            printf(" %.2lf   |", exchangeRate[i].currencies[j]);
        printf("\n");
    }
*/
    printf("\n\n");
    for (int i = 0; i < linhasLidas; i++)
    {
        printf("\n[%02d-%02d-%02d]\n", exchangeRate[i].conversionDate.day, exchangeRate[i].conversionDate.month, exchangeRate[i].conversionDate.year);
        for (int j = 0; j < EXCHANGES_SIZE; j++)
        {
            printf("\t%s = %.02f\n", EXCHANGES[j], exchangeRate[i].currencies[j]);
        }
    }
}