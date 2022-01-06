#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include"interface.h"
#include"goodsTransactions.h"
#include"exchangeRates.h"

#define BUFFER_SIZE 40

void newGoodQuestionaire() {
    GOOD good;
    bool isValid = true;
    int i = 0;

    printf("*** Registo de novo bem ***\n");

    char buffer[BUFFER_SIZE];
    do
    {
        system("cls");
        isValid = true;

        printf("\nIdentificacao da data de observacao (dd/MM/aaaa): ");
        fgets(buffer, sizeof(buffer), stdin);
        fflush(stdin);

        if(strlen(buffer) - 1 == 0 || strlen(buffer) - 1 > 10 || strlen(buffer) - 1 < 10) {
            if(!handleError("Data Inválida")) return;

            isValid = false;
        }
        else if(strlen(buffer) - 1 == 10) {
            char *aux;
            aux = strtok(buffer, "/");

            while(aux != NULL) {
                if(i == 0) {
                    if(strlen(aux) == 2) {
                        good.obsDate.day = atoi(aux);
                    } else {
                        if(!handleError("Data Inválida")) return;

                        isValid = false;
                        break;
                    }
                } 
                else if(i == 1) {
                    if(strlen(aux) == 2) {
                        good.obsDate.month = atoi(aux);
                    } else {
                        if(!handleError("Data Inválida")) return;

                        isValid = false;
                        break;
                    }
                } 
                else if(i == 2) {
                    if(strlen(aux) - 1 == 4) {
                        good.obsDate.year = atoi(aux);
                    } else {
                        if(!handleError("Data Inválida")) return;

                        isValid = false;
                        break;
                    }
                } 
                
                aux = strtok(NULL, "/");
                i++;
            }

            free(aux);
        }
        else {
            isValid = false;
        }

        if(isValid) {
            if(good.obsDate.day < 1 || good.obsDate.day > 31)
            {
                if(!handleError("Data Inválida")) return;

                isValid = false;
            }
            else if(good.obsDate.month < 1 || good.obsDate.month > 12)
            {
                if(!handleError("Data Inválida")) return;

                isValid = false;
            }
            else if(good.obsDate.year < 999 || good.obsDate.year > 9999)
            {
                if(!handleError("Data Inválida")) return;

                isValid = false;
            }
        }

        printf("%d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
    } while (!isValid);

    memset(buffer, 0, BUFFER_SIZE);
    i = 0;

    do
    {
        system("cls");
        isValid = true;

        printf("Identificacao do bem: ");
        fgets(buffer, sizeof(buffer), stdin);
        fflush(stdin);
        

        if(strlen(buffer) - 1 == 0) {
            if(!handleError("Identificador do bem nao pode ser vazio.")) return;

            isValid = false;
        } else if(contaisNumber(buffer) == true) {
            if(!handleError("Identificador só pode conter letras.")) return;

            isValid = false;
        } else if(strlen(buffer) - 1 > 20) {
            if(!handleError("Identificador do bem nao pode ter mais de 20 caracteres.")) return;

            isValid = false;
        }

        strcpy(good.name, buffer);

        if(isValid) strcpy(good.name, strToUpper(good.name));
    } while (!isValid);

    memset(buffer, 0, BUFFER_SIZE);
    
    do
    {
        system("cls");
        isValid = true;

        char* opcoes[MARKET_TYPES_NUMBER];

        for (i = 0; i < MARKET_TYPES_NUMBER; i++)
        {
            opcoes[i] = (char*)marketTypeStrings[i];
        }
        
        int op = drawMenu(opcoes, MARKET_TYPES_NUMBER, "Selecione o tipo de mercado");

        if(op == -1) return;
        
        good.marketType = op - 1;     
    } while (!isValid);
    
    do
    {
        system("cls");
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

    printf("\n*** Dados do bem ***\n");
    printf("Data de observacao: %d/%d/%d\n", good.obsDate.day, good.obsDate.month, good.obsDate.year);
    printf("Nome do bem: %s\n", good.name);
    printf("Tipo de mercado: %s\n", marketTypeStrings[good.marketType]);
    printf("Valor de abertura: %.3f\n", good.openValue);
    printf("Valor de fecho: %.3f\n", good.closeValue);
    printf("Menor valor observado: %.3f\n", good.lowerValue);
    printf("Maior valor observado: %.3f\n", good.higherValue);
    printf("Unidade de moeda: %s\n", CURRENCIES[good.currency]);
    printf("Volume total transacionado: %d\n\n", good.volume);

    printf("Deseja confirmar os dados? (S/N): ");
    fgets(buffer, sizeof(buffer), stdin);
    fflush(stdin);
    
    //Fazer as validações do buffer e verificar se é S ou N
    if(buffer[0] == 'S' || buffer[0] == 's')
    {
        //Se for S, adicionar o good ao ficheiro
        memset(buffer, 0, BUFFER_SIZE);
        addGoodToFile(good);
    }
    else
    {
        //Se for N, voltar ao menu inicial
        memset(buffer, 0, BUFFER_SIZE);
        return;
    }
}

bool checkIfGoodExistsAndUpdate(GOOD good)
{
    printf("\n*** Verificar se o bem existe ***\n");
    FILE *auxFile = fopen("./files/goodTransaction.bin", "rb");
    GOOD *auxGood = readGoodTransactionsFile();
    int auxGoodSize = getNumberOfLinesInFile(auxFile);
    fclose(auxFile);

    int i = 0;
    for (i = 0; i <= auxGoodSize; i++)
    {
        if(strcmp(auxGood[i].name, good.name) == 0 && auxGood[i].marketType == good.marketType && auxGood[i].obsDate.day == good.obsDate.day && auxGood[i].obsDate.month == good.obsDate.month && auxGood[i].obsDate.year == good.obsDate.year)
        {
            printf("\n*** O bem ja existe ***\n");
            FILE *auxFile = fopen("./files/goodTransaction.bin", "wb");

            auxGood[i].currency = good.currency;
            auxGood[i].marketType = good.marketType;
            auxGood[i].openValue = good.openValue;
            auxGood[i].closeValue = good.closeValue;
            auxGood[i].lowerValue = good.lowerValue;
            auxGood[i].higherValue = good.higherValue;
            auxGood[i].volume = good.volume;

            fwrite(auxGood, sizeof(GOOD), auxGoodSize, auxFile); 
            fclose(auxFile);
            return true;
        }
    }
    
    return false;
}

void addGoodToFile(GOOD good)
{
    if(checkIfGoodExistsAndUpdate(good) == false)
    {
        FILE *file = fopen("./files/goodTransaction.bin", "ab");

        if(file == NULL)
        {
            setTextRed();
            printf("Erro a guardar os dados do bem tente novamente.\n");
            resetText();
            printf("\nClique em qualquer tecla para voltar ao menu.");
            getch();
            return;
        }
        
        fwrite(&good, sizeof(GOOD), 1, file);
        fclose(file);
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

GOOD *readGoodTransactionsFile() {
    FILE *file = fopen("./files/goodTransaction.bin", "rb");
    GOOD *goods = (GOOD*)malloc(sizeof(GOOD));
    int i = 0;

    if(file == NULL)
    {
        setTextRed();
        printf("Erro a guardar os dados do bem tente novamente.\n");
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

void goodTransactionsMenu() {
    system("cls");

    char *opcoes[] = {"Registar Novo", "Listar Bens Transacionados", "Voltar..."};
    int op = drawMenu(opcoes, 3, "Bens Transacionados");

    switch (op)
    {
        case 1:
            newGoodQuestionaire();
            break;

        case 2:
            // listGoodTransactions();
            break;
        
        default:
            break;
    }
}