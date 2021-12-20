#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"
#include"exchangeRates.h"
#include"interface.h"


void drawExchangeRatesTable(EXCHANGERATE *exchangeRates, int linhasLidas)
{
    /**
     * Draw table with | and - characters
     * put a header row with: Data | USD | JPY | BGN | CYP | CZK | DKK | EEK | GBP | HUF | LTL | LVL | MTL | PLN | ROL | RON | SEK | SIT | SKK | CHF | ISK | NOK | HRK | RUB | TRL | TRY | AUD | BRL | CAD | CNY | HKD | IDR | ILS | INR | KRW | MXN | MYR | NZD | PHP | SGD | THB | ZAR
     * put fill the rest of the table with the exchangeRate values
    */
   
    int i;
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
        printf("| %02d-%02d-%02d |", exchangeRates[i].conversionDate.day, exchangeRates[i].conversionDate.month, exchangeRates[i].conversionDate.year);
        for(int j = 0; j < EXCHANGES_SIZE; j++)
            printf(" %.2lf   |", exchangeRates[i].currencies[j]);
        printf("\n");
    }
}

void drawExchangeRates(EXCHANGERATE *exchangeRates, int linhasLidas)
{
    printf("\n\n");
    for (int i = 0; i < linhasLidas; i++)
    {
        drawExchangeRate(exchangeRates[i]);
    }
}

void drawExchangeRate(EXCHANGERATE exchangeRate)
{
    int middle = ceil(EXCHANGES_SIZE / 2.0);
    printf("\n[%02d-%02d-%02d]\n", exchangeRate.conversionDate.day, exchangeRate.conversionDate.month, exchangeRate.conversionDate.year);
    float value1, value2;
       
    for (int j = 0; j < ceil(EXCHANGES_SIZE / 2.0); j++)
    {
        value1 = exchangeRate.currencies[j];
        value2 = exchangeRate.currencies[j + middle];
        if(j + middle > EXCHANGES_SIZE - 1)
            printf("\t%s = %.02f\n", EXCHANGES[j], value1);
        else
            printf("\t%s = %.02f \t %s = %.02f \n", EXCHANGES[j], value1, EXCHANGES[j+middle], value2);
    }
}

void drawExchangeRatesPagination(EXCHANGERATE *exchangeRates, int linhasLidas, int paginaAtual, int linhasPorPagina)
{
    int i;
    printf("\n");

    for(i = paginaAtual * linhasPorPagina; i < (paginaAtual * linhasPorPagina) + linhasPorPagina; i++)
    {
        if(i < linhasLidas)
        {
            printf("-----------------------------------------------------\n");
            drawExchangeRate(exchangeRates[i]);
        }
    }
}

void menuWithExchangeRatesPagination(EXCHANGERATE *exchangeRates, int linhasLidas)
{
    int paginaAtual = 0;
    int linhasPorPagina = 5;
    int opcao;

    do
    {
        drawExchangeRatesPagination(exchangeRates, linhasLidas, paginaAtual, linhasPorPagina);
        printf("\nPágina %04d de %d\n", paginaAtual, (int)ceil((double)linhasLidas / linhasPorPagina)-1);
        printf("%d registos por página\n", linhasPorPagina);

        printf("\n\n");
        printf("1 - Próxima página\n");
        printf("2 - Página anterior\n");
        printf("3 - Escolher número de página\n");
        printf("4 - Escolher número de registos por página\n");
        printf("5 - Voltar ao menu principal\n");
        printf("\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                paginaAtual++;
                break;
            case 2:
                paginaAtual--;
                break;
            case 3:
                printf("\n");
                printf("Página: ");
                scanf("%d", &paginaAtual);
                break;
            case 4:
                printf("\n");
                printf("Número de registos por página: ");
                scanf("%d", &linhasPorPagina);
                break;
            case 5:
                break;
            default:
                printf("\n");
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 5);
    
}