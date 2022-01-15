#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include"interface.h"
#include"goodsTransactions.h"
#include"exchangeRates.h"

#define BUFFER_SIZE 40

void newGoodQuestionaire(GOOD *goodTransactions, int *goodTransactionsRows) {
    GOOD good;
    bool isValid = true;
    int i = 0;
    int length = 0;

    char buffer[BUFFER_SIZE];
    do
    {
        system("cls");

        isValid = true;
        printf("\033[4mRegisto de novo bem\033[0m\n");
        printf("\nData de observacao (dd/MM/aaaa): ");
        scanf("%s", buffer);
        fflush(stdin);

        length = strlen(buffer);
        int test = strcspn(buffer, "/");

        if(length == 0) {
            isValid = !handleError("Data Invalida");
        }
        else if(strcspn(buffer, "/") == length)
        {
            isValid = !handleError("Data Invalida");
        }
        else {
            char *aux;
            aux = strtok(buffer, "/");

            while(aux != NULL) {
                if(i == 0) {
                    if(strlen(aux) <= 2) {
                        good.obsDate.day = atoi(aux);
                    } else {
                        isValid = !handleError("Data Invalida");

                        
                        break;
                    }
                } 
                else if(i == 1) {
                    if(strlen(aux) <= 2) {
                        good.obsDate.month = atoi(aux);
                    } else {
                        isValid = !handleError("Data Invalida");

                        
                        break;
                    }
                } 
                else if(i == 2) {
                    if(strlen(aux)  == 4) {
                        good.obsDate.year = atoi(aux);
                    } else {
                        isValid = !handleError("Data Invalida");

                        
                        break;
                    }
                } 
                
                aux = strtok(NULL, "/");
                i++;
            }

        }

        if(isValid) {
            if(good.obsDate.day < 1 || good.obsDate.day > 31)
            {
                isValid = !handleError("Data Invalida");

                
            }
            else if(good.obsDate.month < 1 || good.obsDate.month > 12)
            {
                isValid = !handleError("Data Invalida");

                
            }
            else if(good.obsDate.year < 999 || good.obsDate.year > 9999)
            {
                isValid = !handleError("Data Invalida");

                
            }
        }
        if(isValid)
            printf("%d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
    } while (!isValid);


    i = 0;

    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);

        isValid = true;

        printf("Identificacao do bem: ");
        scanf("%s", buffer);
        fflush(stdin);
        

        if(strlen(buffer) == 0) {
            if(!handleError("Identificador do bem nao pode ser vazio.")) return;

            isValid = false;
        } else if(contaisNumber(buffer) == true) {
            if(!handleError("Identificador só pode conter letras.")) return;

            isValid = false;
        } else if(strlen(buffer) > 20) {
            if(!handleError("Identificador do bem nao pode ter mais de 20 caracteres.")) return;

            isValid = false;
        }

        strcpy(good.name, buffer);

        if(isValid) strcpy(good.name, strToUpper(good.name));
    } while (!isValid);


    do
    {
        system("cls");
        isValid = true;

        char* opcoes[MARKET_TYPES_NUMBER];

        for (i = 0; i < MARKET_TYPES_NUMBER; i++)
        {
            opcoes[i] = (char*)MARKET_TYPE_STRINGS[i];
        }
        
        int op = drawMenu(opcoes, MARKET_TYPES_NUMBER, "Selecione o tipo de mercado");

        if(op == -1) return;
        
        good.marketType = op - 1;     
    } while (!isValid);
    
    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
        printf("Nome do bem: %s\n", good.name);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
        isValid = true;

        double value;

        printf("Valor de abertura: ");
        scanf("%lf", &value);
        fflush(stdin);

        if(value < 0) {
            if(!handleError("Valor de abertura nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.openValue = value;
    } while (!isValid);

    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
        printf("Nome do bem: %s\n", good.name);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
        printf("Valor de abertura: %.3f\n", good.openValue);
        isValid = true;

        double value;

        printf("Valor de Fecho: ");
        scanf("%lf", &value);
        fflush(stdin);

        if(value < 0) {
            if(!handleError("Valor de fecho nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.closeValue = value;
    } while (!isValid);

    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
        printf("Nome do bem: %s\n", good.name);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
        printf("Valor de abertura: %.3f\n", good.openValue);
        printf("Valor de fecho: %.3f\n", good.closeValue);
        isValid = true;

        double value;

        printf("Menor valor observado: ");
        scanf("%lf", &value);
        fflush(stdin);

        if(value < 0) {
            if(!handleError("Menor valor observado nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.lowerValue = value;
    } while (!isValid);

    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
        printf("Nome do bem: %s\n", good.name);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
        printf("Valor de abertura: %.3f\n", good.openValue);
        printf("Valor de fecho: %.3f\n", good.closeValue);
        printf("Menor valor observado: %.3f\n", good.lowerValue);
        isValid = true;

        double value;

        printf("Maior valor observado: ");
        scanf("%lf", &value);
        fflush(stdin);

        if(value < 0) {
            if(!handleError("Maior valor observado nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.higherValue = value;
    } while (!isValid);

    do
    {
        system("cls");
        isValid = true;

        char* opcoes[CURRENCIES_SIZE];

        for (i = 0; i < CURRENCIES_SIZE; i++)
        {
            opcoes[i] = (char*)CURRENCIES[i];
        }
        
        int op = drawMenu(opcoes, CURRENCIES_SIZE, "Selecione a unidade de moeda");

        if(op == -1) return;
        
        good.currency = op -1;     
    } while (!isValid);

    do
    {
        system("cls");
        printf("\033[4mRegisto de novo bem\033[0m\n\n");
        printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
        printf("Nome do bem: %s\n", good.name);
        printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
        printf("Valor de abertura: %.3f\n", good.openValue);
        printf("Valor de fecho: %.3f\n", good.closeValue);
        printf("Menor valor observado: %.3f\n", good.lowerValue);
        printf("Maior valor observado: %.3f\n", good.higherValue);
        printf("Unidade de moeda: %s\n", CURRENCIES[good.currency]);
        isValid = true;

        int vol;

        printf("Indique o volume total transacionado: ");
        scanf("%d", &vol);
        fflush(stdin);

        if(vol < 0) {
            if(!handleError("Volume total transacionado nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.volume = vol;
    } while (!isValid);

    system("cls");

    printf("\033[4mRegisto de novo bem\033[0m\n\n");
    printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
    printf("Nome do bem: %s\n", good.name);
    printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
    printf("Valor de abertura: %.3f\n", good.openValue);
    printf("Valor de fecho: %.3f\n", good.closeValue);
    printf("Menor valor observado: %.3f\n", good.lowerValue);
    printf("Maior valor observado: %.3f\n", good.higherValue);
    printf("Unidade de moeda: %s\n", CURRENCIES[good.currency]);
    printf("Volume total transacionado: %d\n\n", good.volume);

    printf("Deseja confirmar os dados? (S/N): ");
    fgets(buffer, sizeof(buffer), stdin);
    fflush(stdin);
    
    //Fazer as validacces do buffer e verificar se é S ou N
    if(buffer[0] == 'S' || buffer[0] == 's')
    {
        //Se for S, adicionar o good ao ficheiro
        memset(buffer, 0, BUFFER_SIZE);
        addGoodToFile(good, goodTransactions, goodTransactionsRows);
    }
    else
    {
        //Se for N, voltar ao menu inicial
        memset(buffer, 0, BUFFER_SIZE);
        return;
    }
}

bool checkIfGoodExistsAndUpdate(GOOD *goodTransactions, int goodTransactionsRows, GOOD good)
{
    int i = 0;
    for (i = 0; i <= goodTransactionsRows; i++)
    {
        if(strcmp(goodTransactions[i].name, good.name) == 0 && goodTransactions[i].marketType == good.marketType && goodTransactions[i].obsDate.day == good.obsDate.day && goodTransactions[i].obsDate.month == good.obsDate.month && goodTransactions[i].obsDate.year == good.obsDate.year)
        {
            goodTransactions[i].currency = good.currency;
            goodTransactions[i].marketType = good.marketType;
            goodTransactions[i].openValue = good.openValue;
            goodTransactions[i].closeValue = good.closeValue;
            goodTransactions[i].lowerValue = good.lowerValue;
            goodTransactions[i].higherValue = good.higherValue;
            goodTransactions[i].volume = good.volume;
            return true;
        }
    }
    
    return false;
}

void saveGoodsToFile(GOOD *goodTransactions, int *goodTransactionsRows)
{
    FILE *file = fopen("./files/goodTransaction.dat", "wb");

    fwrite(goodTransactions, sizeof(GOOD), *goodTransactionsRows, file);
    fclose(file);
}

void addGoodToFile(GOOD good, GOOD *goodTransactions, int *goodTransactionsRows)
{
    if(checkIfGoodExistsAndUpdate(goodTransactions, *goodTransactionsRows, good) == false)
    {
        *goodTransactionsRows = *goodTransactionsRows + 1;

        goodTransactions = realloc(goodTransactions, (*goodTransactionsRows) * sizeof(GOOD));


        goodTransactions[*goodTransactionsRows-1] = good;

        /*goodTransactions[*goodTransactionsRows-1].currency = good.currency;
        goodTransactions[*goodTransactionsRows-1].marketType = good.marketType;
        goodTransactions[*goodTransactionsRows-1].openValue = good.openValue;
        goodTransactions[*goodTransactionsRows-1].closeValue = good.closeValue;
        goodTransactions[*goodTransactionsRows-1].lowerValue = good.lowerValue;
        goodTransactions[*goodTransactionsRows-1].higherValue = good.higherValue;
        goodTransactions[*goodTransactionsRows-1].volume = good.volume;
        
        goodTransactions[*goodTransactionsRows].obsDate.day = good.obsDate.day;
        goodTransactions[*goodTransactionsRows].obsDate.month = good.obsDate.month;
        goodTransactions[*goodTransactionsRows].obsDate.year = good.obsDate.year;
        strcpy(goodTransactions[*goodTransactionsRows-1].name, good.name);
        */

        printColoredText("Dados do bem guardados com sucesso.\n", GREEN);
        printf("Clica em qualquer tecla para voltar ao menu.");
        getch();
    }
    else {
        printColoredText("Dados do bem atualizados com sucesso.\n", GREEN);
        printf("Clica em qualquer tecla para voltar ao menu.");
        getch();
    }

}

GOOD *readGoodsTransactionsFile(int *numRows) {
    FILE *file = fopen("./files/goodTransaction.dat", "rb");
    GOOD *goods = (GOOD*)malloc(1*sizeof(GOOD));
    int i = 0;

    if(file == NULL)
    {
        setTextRed();
        printf("Erro ao abrir o ficheiro.\n");
        resetText();
        printf("\nClique em qualquer tecla para voltar ao menu.");
        getch();
        return NULL;
    }

    rewind(file);

    while(fread(&goods[i], sizeof(GOOD), 1, file))
    {
        i++;
        goods = (GOOD*)realloc(goods, (i+1) * sizeof(GOOD));
    }

    fclose(file);
    *numRows = i;
    return goods;
}

GOOD *readGoodsTransactionsHistoryFile(FILE *f, int *numRows)
{
    GOOD *goodsHistory;
    int nCamposLidos = 0;
    int linhasFicheiro = 0;
    int n = 0;

    linhasFicheiro = getNumberOfLinesInFile(f);

    goodsHistory = (GOOD *)malloc(linhasFicheiro * sizeof(GOOD));


    while (!feof(f))
    {
        char **V = Read_Split_Line_File(f, 9, &nCamposLidos, ";");

        if(nCamposLidos == 0)
            continue;

        char *date = strtok(V[0], "/");
        goodsHistory[n].obsDate.day = atoi(date);

        date = strtok(NULL, "/");
        goodsHistory[n].obsDate.month = atoi(date);

        date = strtok(NULL, "/");
        goodsHistory[n].obsDate.year = atoi(date);
        
        strcpy(goodsHistory[n].name,V[1]);
        goodsHistory[n].openValue = atof(V[2]);
        goodsHistory[n].closeValue = atof(V[3]);
        goodsHistory[n].higherValue = atof(V[4]);
        goodsHistory[n].lowerValue = atof(V[5]);
        goodsHistory[n].volume = atoi(V[6]);
        goodsHistory[n].marketType = atoi(V[7]);
        goodsHistory[n].currency = atoi(V[8]);


        for (int i = 0; i < nCamposLidos; i++)
            free(V[i]);
        free(V);
        n++;
    }
    fclose(f);
    *numRows = n;

    return goodsHistory;
}

typedef struct goodIdentifier 
{
    char name[50];
    MARKETTYPE marketType;
} GOODIDENTIFIER;


void listGoodsIndentifiers(GOOD *goodTransactions, int goodTransactionsRows)
{
    int i = 0, j = 0, count = 1;
    bool exists = false;

    GOODIDENTIFIER* goodIdentifiers = (GOODIDENTIFIER*)malloc(1 * sizeof(GOODIDENTIFIER));

    strcpy(goodIdentifiers[0].name, goodTransactions[0].name);
    goodIdentifiers[0].marketType = goodTransactions[0].marketType;
    


    for (i = 0; i < goodTransactionsRows; i++)
    {
        j=0;
        for (j = 0; j < count; j++)
        {
            if(strcmp(goodIdentifiers[j].name, goodTransactions[i].name) == 0) {
                exists = true;
                break;
            }
                
        }
        j=0;

        if(exists == false)
        {
            count++;
            
            goodIdentifiers = (GOODIDENTIFIER*)realloc(goodIdentifiers, (count) * sizeof(GOODIDENTIFIER));
            
            //insert new good identifier in array sorted by name
            strcpy(goodIdentifiers[count-1].name, goodTransactions[i].name);
            goodIdentifiers[count-1].marketType = goodTransactions[i].marketType;

        }

        exists = false;
    }

    i = 0;

    //sort array by name

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count-1; j++)
        {
            if(strcmp(goodIdentifiers[j].name, goodIdentifiers[j+1].name) > 0)
            {
                GOODIDENTIFIER aux;
                aux = goodIdentifiers[j];
                goodIdentifiers[j] = goodIdentifiers[j+1];
                goodIdentifiers[j+1] = aux;
            }
        }
    }

    system("cls");

    printf("\n  \033[4mBens disponiveis (Ordenados por ordem crescente do nome)\033[0m\n");

    for (i = 0; i < count; i++)
    {
        printf("  %s: %s\n", goodIdentifiers[i].name, MARKET_TYPE_STRINGS[goodIdentifiers[i].marketType]);
    }

    free(goodIdentifiers);  
}

void goodTransactionsMenu(GOOD *goodTransactions, int *goodTransactionsRows) {
    system("cls");

    char *opcoes[] = {"Registar Novo", "Listar Bens Transacionados", "Voltar..."};
    int op = drawMenu(opcoes, 3, "Bens Transacionados");

    switch (op)
    {
        case 1:
            newGoodQuestionaire(goodTransactions, goodTransactionsRows);
            break;

        case 2:
            // listGoodTransactions();
            break;
        
        default:
            break;
    }
}


void FiveGoodsWithMoretransaccions(GOOD *goodTransactions, int *goodTransactionsRows){

    GOOD interval;
    bool quitQuestions=false,isvalid=false;
    int count=0;
    int i =0;
    DATE inicio,fim;
    char strDatainicio[15];
    char strDatafim[15];

    
    do
    {
        system("cls");
        printf("Identificacao da data de inicio (dd/MM/aaaa): ");
        fflush(stdin);
        scanf("%s",strDatainicio);
        fflush(stdin);
        printf("Identificacao da data de fim (dd/MM/aaaa): ");
        scanf("%s",strDatafim);
        fflush(stdin);
        inicio=isDateValid(strDatainicio);
        fim=isDateValid(strDatafim);
        if (inicio.year==0 && fim.year==0)
        {
            quitQuestions=!handleError("Data Invalida");
        }
    } while (quitQuestions==true);

    /*do
    {   
           count++; 
           i++;
    } while (compareDates(inicio,goodTransactions[i].obsDate)!=0);
    printf("%d",count);*/

    

}