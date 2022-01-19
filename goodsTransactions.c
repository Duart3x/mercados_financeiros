#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include"interface.h"
#include"goodsTransactions.h"
#include"exchangeRates.h"

#define BUFFER_SIZE 40

GOOD* newGoodQuestionaire(GOOD *goodTransactions, int *goodTransactionsRows) {
    GOOD good;
    bool isValid = false;
    int i = 0;
    int length = 0;
    bool repeat = false;
    bool quitMenu = false;
    char buffer[BUFFER_SIZE];

    do
    {
        quitMenu = false;
        isValid = false;
        repeat = false;

        while (!isValid && !quitMenu){
            system("cls");

            isValid = true;
            printf("\033[4mRegisto de novo bem\033[0m\n");
            printf("\nData de observacao (dd/MM/aaaa): ");
            scanf("%s", buffer);
            fflush(stdin);

            length = strlen(buffer);

            if(length == 0) {
                quitMenu = !handleError("Data Invalida");
                isValid=false;
            }
            else if(strcspn(buffer, "/") == length)
            {
                quitMenu = !handleError("Data Invalida");
                isValid=false;
            }
            else {
                char *aux;
                aux = strtok(buffer, "/");
                i=0;
                while(aux != NULL) {
                    if(i == 0) {
                        if(strlen(aux) <= 2) {
                            good.obsDate.day = atoi(aux);
                        } else {
                            quitMenu = !handleError("Data Invalida");

                            isValid=false;
                            
                            break;
                        }
                    } 
                    else if(i == 1) {
                        if(strlen(aux) <= 2) {
                            good.obsDate.month = atoi(aux);
                        } else {
                            quitMenu = !handleError("Data Invalida");

                            isValid=false;
                            break;
                        }
                    } 
                    else if(i == 2) {
                        if(strlen(aux)  == 4) {
                            good.obsDate.year = atoi(aux);
                        } else {
                            quitMenu = !handleError("Data Invalida");

                            isValid=false;
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
                    quitMenu = !handleError("Data Invalida");

                    isValid=false;
                }
                else if(good.obsDate.month < 1 || good.obsDate.month > 12)
                {
                    quitMenu = !handleError("Data Invalida");

                    isValid=false;
                }
                else if(good.obsDate.year < 999 || good.obsDate.year > 9999)
                {
                    quitMenu = !handleError("Data Invalida");

                    isValid=false;
                }
            }
        }
        i = 0;
        isValid = false;
        while (!isValid && !quitMenu){
            system("cls");
            printf("\033[4mRegisto de novo bem\033[0m\n\n");
            printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);

            isValid = true;

            printf("Identificacao do bem: ");
            scanf("%s", buffer);
            fflush(stdin);
            

            if(strlen(buffer) == 0) {
                quitMenu = !handleError("Identificador do bem nao pode ser vazio.");
                isValid=false;

                isValid = false;
            } else if(contaisNumber(buffer) == true) {
                quitMenu = !handleError("Identificador só pode conter letras.");

                isValid = false;
            } else if(strlen(buffer) > 20) {
                quitMenu = !handleError("Identificador do bem nao pode ter mais de 20 caracteres.");

                isValid = false;
            }

            strcpy(good.name, buffer);

            if(isValid) strcpy(good.name, strToUpper(good.name));
        }
        isValid = false;
        while (!isValid && !quitMenu) {
            system("cls");
            isValid = true;

            char* opcoes[MARKET_TYPES_NUMBER];

            for (i = 0; i < MARKET_TYPES_NUMBER; i++)
            {
                opcoes[i] = (char*)MARKET_TYPE_STRINGS[i];
            }
            
            int op = drawMenu(opcoes, MARKET_TYPES_NUMBER, "Selecione o tipo de mercado");

            if(op == -1) return goodTransactions;
            
            good.marketType = op - 1;     
        } 
        isValid = false;     
        while (!isValid && !quitMenu) {
            system("cls");
            printf("\033[4mRegisto de novo bem\033[0m\n\n");
            printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
            printf("Nome do bem: %s\n", good.name);
            printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
            isValid = true;

            double value;

            printf("Valor de abertura: ");
            scanf("%s", buffer);
            fflush(stdin);

            if (!isNumber(buffer))
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            else
            {
                value = atof(replaceChar(buffer, '.', ','));
            }

            if(value < 0)
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            
            
            if(isValid) good.openValue = value;
        } 
        isValid = false;
        while (!isValid && !quitMenu){
            system("cls");
            printf("\033[4mRegisto de novo bem\033[0m\n\n");
            printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
            printf("Nome do bem: %s\n", good.name);
            printf("Tipo de mercado: %s\n", MARKET_TYPE_STRINGS[good.marketType]);
            printf("Valor de abertura: %.3f\n", good.openValue);
            isValid = true;

            double value;

            printf("Valor de Fecho: ");
            scanf("%s", buffer);
            fflush(stdin);

            if (!isNumber(buffer))
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            else
            {
                value = atof(replaceChar(buffer, '.', ','));
            }

            if(value < 0) 
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }

            if(isValid) good.closeValue = value;
        } 
        isValid = false;
        while (!isValid && !quitMenu){
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
            scanf("%s", buffer);
            fflush(stdin);

            if (!isNumber(buffer))
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            else
            {
                value = atof(replaceChar(buffer, '.', ','));
            }

            if(value < 0) 
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }

            if(isValid) good.lowerValue = value;
        }
        isValid = false;
        while (!isValid && !quitMenu){
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
            scanf("%s", buffer);
            fflush(stdin);

            if (!isNumber(buffer))
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            else
            {
                value = atof(replaceChar(buffer, '.', ','));
            }

            if(value < 0) 
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }

            if(isValid) good.higherValue = value;
        }
        isValid = false;
        while (!isValid && !quitMenu){
            system("cls");
            isValid = true;

            char* opcoes[CURRENCIES_SIZE];

            for (i = 0; i < CURRENCIES_SIZE; i++)
            {
                opcoes[i] = (char*)CURRENCIES[i];
            }
            
            int op = drawCurrenciesMenu("Selecione a unidade da moeda", NULL, 0);

            if(op == -1) return goodTransactions;
            
            good.currency = op -1;     
        }
        isValid = false;
        while (!isValid && !quitMenu){
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

            printf("Volume total transacionado: ");
            scanf("%s", buffer);
            fflush(stdin);

            if (!isNumber(buffer))
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }
            else
            {
                vol = atoi(buffer);
            }

            if(vol < 0) 
            {
                quitMenu = !handleError("Valor introduzido invalido");
                isValid=false;
            }

            if(isValid) good.volume = vol;
        }

        if (quitMenu)
            return goodTransactions;

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
        scanf("%s", buffer);
        fflush(stdin);
        
        //Fazer as validacces do buffer e verificar se é S ou N
        if(buffer[0] != 'N' || buffer[0] != 'n')
            goodTransactions = addGoodToArray(good, goodTransactions, goodTransactionsRows);
        
        int sn = 0;
        char *opcao[] = {"Sim", "Nao"};

        sn = drawMenu(opcao, 2, "Deseja adicionar um novo bem?");

        if (sn == 1)
        {
            repeat = true;
        }
        else
        {
            repeat = false;
        }

    } while (repeat);

    return goodTransactions;

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

GOOD* addGoodToArray(GOOD good, GOOD *goodTransactions, int *goodTransactionsRows)
{
    GOOD* newList = (GOOD*)malloc(sizeof(GOOD) * (*goodTransactionsRows + 1));
    if(checkIfGoodExistsAndUpdate(goodTransactions, *goodTransactionsRows, good) == false)
    {
        *goodTransactionsRows = *goodTransactionsRows + 1;

        newList = (GOOD*) realloc(goodTransactions, (*goodTransactionsRows)  * sizeof(GOOD));

        goodTransactions = newList;

        goodTransactions[*goodTransactionsRows-1] = good;

        printColoredText("\rDados do bem guardados com sucesso.\n", GREEN);
    }
    else {
        printColoredText("\rDados do bem atualizados com sucesso.\n", GREEN);
    }

    return goodTransactions;
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

    GOOD good;

    while(fread(&good, sizeof(GOOD), 1, file))
    {
        i++;
        goods = (GOOD*)realloc(goods, (i+1) * sizeof(GOOD));
        goods[i-1] = good;
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

typedef struct goodIdentifiersArray {
    GOODIDENTIFIER* identifiers;
    int count;
} GOODIDENTIFIERSARRAY;

GOODIDENTIFIERSARRAY getGoodsIdentifiers(GOOD *goodTransactions, int goodTransactionsRows) {
    int i = 0, j = 0, count = 1;
    bool exists = false;

    GOODIDENTIFIERSARRAY goodIdentifiers;
    goodIdentifiers.identifiers = (GOODIDENTIFIER*)malloc(1 * sizeof(GOODIDENTIFIER));

    strcpy(goodIdentifiers.identifiers[0].name, goodTransactions[0].name);
    goodIdentifiers.identifiers[0].marketType = goodTransactions[0].marketType;

    for (i = 0; i < goodTransactionsRows; i++)
    {
        j=0;
        for (j = 0; j < count; j++)
        {
            if(strcmp(goodIdentifiers.identifiers[j].name, goodTransactions[i].name) == 0) {
                exists = true;
                break;
            }
                
        }
        j=0;

        if(exists == false)
        {
            count++;
            
            goodIdentifiers.identifiers = (GOODIDENTIFIER*)realloc(goodIdentifiers.identifiers, (count) * sizeof(GOODIDENTIFIER));
            
            //insert new good identifier in array sorted by name
            strcpy(goodIdentifiers.identifiers[count-1].name, goodTransactions[i].name);
            goodIdentifiers.identifiers[count-1].marketType = goodTransactions[i].marketType;

        }

        exists = false;
    }

    i = 0;

    //sort array by name

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count-1; j++)
        {
            if(strcmp(goodIdentifiers.identifiers[j].name, goodIdentifiers.identifiers[j+1].name) > 0)
            {
                GOODIDENTIFIER aux;
                aux = goodIdentifiers.identifiers[j];
                goodIdentifiers.identifiers[j] = goodIdentifiers.identifiers[j+1];
                goodIdentifiers.identifiers[j+1] = aux;
            }
        }
    }

    goodIdentifiers.count = count;

    return goodIdentifiers;
}


void listGoodsIndentifiers(GOOD *goodTransactions, int goodTransactionsRows)
{
    int i = 0;
    GOODIDENTIFIERSARRAY goodIdentifiers = getGoodsIdentifiers(goodTransactions, goodTransactionsRows);

    system("cls");

    printf("\n  \033[4mBens disponiveis (Ordenados por ordem crescente do nome)\033[0m\n");

    for (i = 0; i < goodIdentifiers.count; i++)
    {
        printf("  %s: %s\n", goodIdentifiers.identifiers[i].name, MARKET_TYPE_STRINGS[goodIdentifiers.identifiers[i].marketType]);
    }

    free(goodIdentifiers.identifiers);  
}

void fiveGoodsWithMoreTransactions(GOOD *goodTransactions, int *goodTransactionsRows){

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

void closeValueStatistics(GOOD *goodTransactions, int goodTransactionsRows) {
    DATE initialDate, endDate;

    bool isValid = true, quitMenu = false;
    char strInitialDate[10];
    char strEndDate[10];
    GOOD *goodInStudie;

    int identifierOption = 0, i = 0, goodInStudieCount = 0;
    GOODIDENTIFIERSARRAY goodIdentifiers = getGoodsIdentifiers(goodTransactions, goodTransactionsRows);

    do
    {
        system("cls");
        isValid = true;
        printf("\033[4mIndique um intervalo de datas a estudar\033[0m\n\n");
        printf("Data inicial (dd/MM/aaaa): ");
        scanf("%s",strInitialDate);
        fflush(stdin);
        initialDate=isDateValid(strInitialDate);

        if (initialDate.year==0)
        {
            quitMenu = !handleError("Data inicial invalida");
            isValid = false;
        }
    } while (!isValid && !quitMenu);
    isValid = false;
    while (!isValid && !quitMenu)
    {
        system("cls");
        isValid = true;
        printf("\033[4mIndique um intervalo de datas a estudar\033[0m\n\n");
        printf("De %d/%d/%d a : ", initialDate.day, initialDate.month, initialDate.year);
        scanf("%s",strEndDate);
        fflush(stdin);
        endDate=isDateValid(strEndDate);

        if (endDate.year==0)
        {
            quitMenu = !handleError("Data final invalida");
            isValid = false;
        }
    }
    isValid = false;
    while (!isValid && !quitMenu)
    {
        system("cls");
        isValid = true;
        int i = 0;
        
        char** opcoes = (char**)malloc(goodIdentifiers.count * sizeof(char*));

        for (i = 0; i < goodIdentifiers.count; i++)
        {
            opcoes[i] = (char*)goodIdentifiers.identifiers[i].name;
        }
        
        int op = drawMenu(opcoes, goodIdentifiers.count, "Selecione a moeda que pretende consultar");

        if(op == -1) quitMenu = true;
        else identifierOption = op;
    }

    if(!quitMenu) {
        //? Procura na lista de bens transacionados pelo bem selecionado no intervalo de datas selecionado
        for (i = 0; i < goodTransactionsRows; i++)
        {
            if(strcmp(goodTransactions[i].name, goodIdentifiers.identifiers[identifierOption - 1].name) == 0 && compareDates(goodTransactions[i].obsDate, initialDate) >= 0 && compareDates(goodTransactions[i].obsDate, endDate) <= 0)
            {
                if(goodInStudieCount == 0) goodInStudie = (GOOD*)malloc(sizeof(GOOD));
                else goodInStudie = (GOOD*)realloc(goodInStudie, (goodInStudieCount + 1) * sizeof(GOOD)); //! Testar isto! Pode não funcionar!!!

                goodInStudie[goodInStudieCount] = goodTransactions[i];
                goodInStudieCount++;
            }
        }

        i = 0;
        
        if(goodInStudieCount > 0)
        {
            //? Procura o valor minimo, maximo e media de fecho
            float min = goodInStudie[0].closeValue, max = goodInStudie[0].closeValue, media = 0, desvio = 0;
            for (i = 0; i < goodInStudieCount; i++)
            {
                if(goodInStudie[i].closeValue < min) min = goodInStudie[i].closeValue;
                if(goodInStudie[i].closeValue > max) max = goodInStudie[i].closeValue;

                media += goodInStudie[i].closeValue;
            }
            media /= goodInStudieCount;

            i = 0;
            
            //? Calcula o desvio padrao de fecho
            for (i = 0; i < goodInStudieCount; i++)
            {
                desvio += pow(goodInStudie[i].closeValue - media, 2);
            }
            desvio = sqrt(desvio / goodInStudieCount);

            system("cls");
            printf("\n\n\033[4mResultados\033[0m\n");
            printf("\033[32m%d/%d/%d - %d/%d/%d (%s)\033[0m\n\n", initialDate.day, initialDate.month, initialDate.year, endDate.day, endDate.month, endDate.year, goodIdentifiers.identifiers[identifierOption - 1].name);
            printf("Valor minimo: %.2f\n", min);
            printf("Valor maximo: %.2f\n", max);
            printf("Valor medio: %.2f\n", media);
            printf("Desvio padrao: %.2f\n", desvio);
        }
        else handleError("O bem não foi transacionado neste intervalo de datas");

        free(goodInStudie);
        free(goodIdentifiers.identifiers);
    }
}