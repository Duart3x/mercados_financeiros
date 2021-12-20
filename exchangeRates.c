#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"
#include"exchangeRates.h"

EXCHANGERATE* readExchangeRatesFile(FILE* f, int* linhasLidas)
{
    EXCHANGERATE *exchangeRate;
    int nCamposLidos;
    int linhasFicheiro = 0;
    int n = 0;

    linhasFicheiro = getNumberOfLinesInFile(f);
    
    exchangeRate = (EXCHANGERATE *)malloc(linhasFicheiro*sizeof(EXCHANGERATE));
    
    while(!feof(f) )
	{
		char **V = Read_Split_Line_File(f, 42, &nCamposLidos, ",");
        
		for (int i = 0; i < nCamposLidos; i++)
        {
            if(i == 0)
            {
                char* date = strtok(V[i], "-");                
                exchangeRate[n].conversionDate.year = atoi(date);
                
                date = strtok(NULL, "-");
                exchangeRate[n].conversionDate.month = atoi(date);
                
                date = strtok(NULL, "-");                
                exchangeRate[n].conversionDate.day = atoi(date);
            }			    
            else
            {
                if(strcmp(V[i],"N/A") == 0)
                    exchangeRate[n].currencies[i-1] = -1;
                else
                    exchangeRate[n].currencies[i-1] = atof(V[i]);
            }
        }


		for (int i = 0; i < nCamposLidos; i++)
			free (V[i]);
		free (V);
        n++;
	}
	fclose(f);	
    *linhasLidas = n;

    return exchangeRate;
}

EXCHANGERATE getExchangeRateByDate(EXCHANGERATE *exchangeRates, int linhasLidas, DATE date)
{
    EXCHANGERATE exchangeRate;
    int middle = linhasLidas/2;

    if(compareDates(exchangeRates[middle].conversionDate,date) == 0)
        return exchangeRates[middle];
    else if(compareDates(exchangeRates[middle].conversionDate,date) == -1)
    {
        if(linhasLidas == 1)
            return exchangeRates[middle];
        else
            return getExchangeRateByDate(exchangeRates, middle, date);
    }
    else
    {
        if(linhasLidas == 1)
            return exchangeRates[middle];
        else
            return getExchangeRateByDate(exchangeRates+middle, linhasLidas-middle, date);
    }
}

