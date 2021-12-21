#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include"utils.h"
#include"exchangeRates.h"
#include"interface.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_ENTER 13


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
    char *strVal1 = malloc(sizeof(char) * 4);
    char *strVal2 = malloc(sizeof(char) * 4);

    strVal1 = NULL;
    strVal2 = NULL;

    for (int j = 0; j < ceil(EXCHANGES_SIZE / 2.0); j++)
    {
        value1 = exchangeRate.currencies[j];
        value2 = exchangeRate.currencies[j + middle];

        if (value1 == -1)
            strVal1 = "N/A";
        if (value2 == -1)
            strVal2 = "N/A";

        if(j + middle > EXCHANGES_SIZE - 1)
        {
            if(strVal1 != NULL)
                printf("\t%s = %s\n", EXCHANGES[j], strVal1);
            else
                printf("\t%s = %.02lf\n", EXCHANGES[j], value1);
        }
        else
        {
            if(strVal1 != NULL && strVal2 != NULL)
                printf("\t%s = %s \t %s = %s\n", EXCHANGES[j], strVal1, EXCHANGES[j + middle], strVal2);
            else if(strVal1 != NULL)
                printf("\t%s = %s \t %s = %.02lf \n", EXCHANGES[j], strVal1, EXCHANGES[j + middle], value2);
            else if(strVal2 != NULL)
                printf("\t%s = %.02lf \t %s = %s\n", EXCHANGES[j], value1, EXCHANGES[j + middle], strVal2);
            else
                printf("\t%s = %.02lf \t %s = %.02lf\n", EXCHANGES[j], value1, EXCHANGES[j + middle], value2);
        }

        strVal1 = NULL;
        strVal2 = NULL;
            
    }
    free(strVal1);
    free(strVal2);
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
        printf("\nPagina %04d de %d\n", paginaAtual, (int)ceil((double)linhasLidas / linhasPorPagina)-1);
        printf("%d registos por pagina\n", linhasPorPagina);

        printf("\n\n");
        printf("1 - Pagina anterior\n");
        printf("2 - Proxima pagina\n");
        printf("3 - Escolher numero de pagina\n");
        printf("4 - Escolher numero de registos por pagina\n");
        printf("5 - Ordernar por ordem crescente do codigo da moeda\n");
        printf("6 - Ordernar por ordem decrescente do valor em euros\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                paginaAtual--;
                break;
            case 2:
                paginaAtual++;
                break;
            case 3:
                printf("\n");
                printf("Pagina: ");
                scanf("%d", &paginaAtual);
                break;
            case 4:
                printf("\n");
                printf("Numero de registos por pagina: ");
                scanf("%d", &linhasPorPagina);
                break;
            case 5:
                exchangeRates = sortExchangeRatesByCurrencyCode(exchangeRates, linhasLidas);
                break;
            case 6:
                exchangeRates = sortExchangeRatesByValueInEuros(exchangeRates, linhasLidas);
                break;
            case 0:
                break;
            default:
                printf("\n");
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);
    
}

int drawMenu(char *opcoes[], int numOpcoes, char *title)
{
    int key = 0;
    int option = 1;
    int i;

    do
    {   
        system("cls");

        printf("\n  ********\t%s\t********\n", title);
        printf("  *                            *\n");
        for (i = 0; i < numOpcoes; i++)
        {
            printf("    %s %s\n", (option == i + 1) ? "->": "  ", opcoes[i]);
        }
        printf("  *                            *\n");
        printf("  ******************************\n");
        key = getch();

        /*printf("\n   ******** Menu Principal ********\n");
        printf("   *                              *\n");
        printf("   * %s Opcao 1                   *\n", (option == 1) ? "->": "  ");
        printf("   * %s Opcao 2                   *\n", (option == 2) ? "->": "  ");
        printf("   *                              *\n");
        printf("   ********************************\n");*/

        if (key == KEY_ESC)
            return -1;

        if(key == KEY_UP)
        {
            if(option > 1)
                option--;
            else option = 1;
        }

        if(key == KEY_DOWN)
        {
            if(option < numOpcoes)
                option++;
            else option = numOpcoes;
        }

    } while(key != KEY_ENTER);

    return option;
}