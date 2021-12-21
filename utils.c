#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"utils.h"

char **Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores)
{
	*n_campos_lidos = 0;
    char *LT = (char *)malloc(sizeof(char)*MAX_LINHA_FICHEIRO);

	if (!f) return NULL;
	if (fgets(LT , MAX_LINHA_FICHEIRO , f) != NULL)	// fgets l� uma linha do ficheiro de texto para a string LT
	{
		// "partir" a linha lida, usando os separadores definidos
		char **Res = (char **)malloc(n_campos_max*sizeof(char *));  // aloca��o de um array com n_campos_max ponteiros para STRING
		char *pch = strtok (LT, separadores);
		int cont = 0;
		while (pch != NULL)
		{
			Res[cont] = (char *)malloc((strlen(pch)+1)*sizeof(char)); // aloca��o do espa�o necess�rio para guardar a string correspondente ao campo
			strcpy(Res[cont++], pch);
			pch = strtok (NULL, separadores);
		}
		*n_campos_lidos = cont;
		return Res;
	}
	return NULL;
};


int getNumberOfLinesInFile(FILE *f)
{
    int n_linhas = 0;
    char *LT = (char *)malloc(sizeof(char)*MAX_LINHA_FICHEIRO);
    while (fgets(LT , MAX_LINHA_FICHEIRO , f) != NULL)
    {
        n_linhas++;
    }
    rewind(f);
    return n_linhas;
}


FILE *openFile(char *fileName, char *mode)
{
    FILE *f = fopen(fileName, mode);
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro: %s\n", fileName);
        return NULL;
    }
    return f;
}

/**
 * @brief Compara duas datas
 * @param d1
 * @param d2
 * 
 * @return 1 se d1 > d2 | 0 se d1 == d2 | -1 se d1 < d2  
 * 
 * 
 * 
*/
int compareDates(DATE d1, DATE d2)
{
    if (d1.year < d2.year)
       return -1;

    else if (d1.year > d2.year)
       return 1;

    if (d1.year == d2.year)
    {
         if (d1.month<d2.month)
              return -1;
         else if (d1.month>d2.month)
              return 1;
         else if (d1.day<d2.day)
              return -1;
         else if(d1.day>d2.day)
              return 1;
         else
              return 0;
    }
}

char* replaceChar(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

BOOLEAN contaisNumber(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
            return true;
    }
    return false;
}

char* strToUpper(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}