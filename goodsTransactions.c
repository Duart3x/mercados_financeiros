#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include"interface.h"
#include"goodsTransactions.h"
#include"exchangeRates.h"

#define BUFFER_SIZE 72

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

        good.name = (char *) malloc(strlen(buffer) + 1);
        strcpy(good.name, buffer);

        if(strlen(good.name) - 1 == 0) {
            if(!handleError("Identificador do bem nao pode ser vazio.")) return;

            isValid = false;
        } else if(contaisNumber(good.name) == true) {
            if(!handleError("Identificador só pode conter letras.")) return;

            isValid = false;
        }

        if(isValid) good.name = strToUpper(good.name);

        free(good.name);
    } while (!isValid);

    memset(buffer, 0, BUFFER_SIZE);
    
    do
    {
        system("cls");
        isValid = true;

        char* opcoes[MARKET_TYPES_NUMBER];

        for (i = 0; i < MARKET_TYPES_NUMBER; i++)
        {
            opcoes[i] = marketTypeStrings[i];
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
            opcoes[i] = CURRENCIES[i];
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

        if(vol < 0) {
            if(!handleError("Volume total transacionado nao pode ser negativo!")) return;

            isValid = false;
        }

        if(isValid) good.volume = vol;
    } while (!isValid);

    system("cls");

    //print de todos os campos do good
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

    //Fazer as validações do buffer e verificar se é S ou N
    if(buffer[0] == 'S' || buffer[0] == 's')
    {
        //Se for S, adicionar o good ao ficheiro
        //addGoodToFile(good);
    }
    else
    {
        //Se for N, voltar ao menu
        return;
    }
}