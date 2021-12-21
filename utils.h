#include<stdio.h>


#ifndef UTILS_H
#define UTILS_H

#define MAX_LINHA_FICHEIRO 300

typedef struct date
{
    int day;
    int month;
    int year;
} DATE;

typedef enum boolean { false, true } bool;

char **Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);
int getNumberOfLinesInFile(FILE *f);
FILE *openFile(char *fileName, char *mode);
int compareDates(DATE d1, DATE d2);
char* replaceChar(char* str, char find, char replace);
bool contaisNumber(char *str);
char* strToUpper(char *str);


#endif
